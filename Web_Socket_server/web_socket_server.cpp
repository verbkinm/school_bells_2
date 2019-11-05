#include "web_socket_server.h"
#include "Log/log.h"

#include <QWebSocket>

#define MONITOR_PROTOCOL "monitor_protocol"
#define MANAGER_PROTOCOL "manager_protocol"

Web_socket_server::Web_socket_server(std::shared_ptr<Settings> setting,
                                     QHostAddress addr, quint16 port,
                                     QObject *parent) :
    QObject(parent),
    _spWebSocketServer(std::make_unique<QWebSocketServer>("WSS Server", QWebSocketServer::NonSecureMode, this)),
    _spSettings(setting)
{
    _spWebSocketServer->listen(addr, port);
    if(_spWebSocketServer->listen(addr, port))
    {
        Log::write(QString("Server listening on address \"" + _spWebSocketServer->serverUrl().toString()).toStdString());
        QTextStream(stdout) << "Server listening on address \"" << _spWebSocketServer->serverUrl().toString() + "\n";
        connect(_spWebSocketServer.get(), &QWebSocketServer::newConnection, this, &Web_socket_server::slotNewConnection);
    }
    else
        Log::write(_spWebSocketServer->errorString().toStdString());
}

Web_socket_server::~Web_socket_server()
{
    _spWebSocketServer->close();
}

void Web_socket_server::slotNewConnection()
{
    auto pSocket = _spWebSocketServer->nextPendingConnection();
    Log::write(QString(getIdentifier(pSocket) + " connected!").toStdString());
    QTextStream(stdout) << getIdentifier(pSocket) << " connected!\n";
    pSocket->setParent(this);

    connect(pSocket, &QWebSocket::textMessageReceived, this, &Web_socket_server::slotGet_message);
    connect(pSocket, &QWebSocket::disconnected, this, &Web_socket_server::socketDisconnected);

    m_clients << pSocket;

//    emit signalNew_connection(pSocket);
}

void Web_socket_server::slotGet_message(const QString &message)
{
    auto pSocket = qobject_cast<QWebSocket *>(sender());

    if(message == MONITOR_PROTOCOL)
        ;
//        emit signalGet_message_from_monitor(pSocket);
    if(message == MANAGER_PROTOCOL)
        ;
}

void Web_socket_server::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    Log::write(QString(getIdentifier(pClient) + " disconnected!").toStdString());
    QTextStream(stdout) << getIdentifier(pClient) << " disconnected!\n";
    if(pClient)
    {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}

void Web_socket_server::fill_shift_in_sending_data(std::string &message) const
{
    for(size_t shift_number = 0; shift_number < _spSettings.get()->shedule_of_day()._shifts.size(); ++shift_number)
    {
        const Shift &shift = _spSettings.get()->shedule_of_day()._shifts.at(shift_number);
        if(!shift.isEnable())
            continue;
        message += std::to_string(shift_number);
        message += "," + std::to_string(shift.getStart_number_of_lesson());
        fill_lesson_in_sending_data(shift, message);
        message += ";";
    }
}

void Web_socket_server::fill_lesson_in_sending_data(const Shift &shift, std::string &message) const
{
    for(auto &lesson : shift._lessons)
    {
        if(lesson.isEnable())
        {
            message += "," + lesson.getTime_begin_str();
            message += "," + lesson.getTime_end_str();
        }
        else
        {
            message += ", -- : --";
            message += ", -- : --";
        }
    }
}

QString Web_socket_server::getIdentifier(QWebSocket *peer)
{
    return QStringLiteral("%1:%2").arg(peer->peerAddress().toString(),
                                       QString::number(peer->peerPort()));
}

void Web_socket_server::slotSendData(QWebSocket *web_socket)
{
    web_socket->sendTextMessage("protocol");
}

void Web_socket_server::slotSendData_to_monitor(QWebSocket *web_socket)
{
    std::string message = "monitor_protocol_data,";
    fill_shift_in_sending_data(message);
    web_socket->sendTextMessage(message.c_str());
}
