#include "monitor_protocol.h"
#include "manager_protocol.h"
#include "web_socket_server.h"
#include <log.h>

#include <QWebSocket>

#define MONITOR_PROTOCOL "monitor_protocol"
#define MANAGER_PROTOCOL "manager_protocol"

Web_socket_server::Web_socket_server(std::shared_ptr<Settings> setting, QObject *parent) :
    QObject(parent),
    _spWebSocketServer(std::make_unique<QWebSocketServer>("WSS Server", QWebSocketServer::NonSecureMode, this)),
    _spSettings(setting)
{
    QHostAddress addr(_spSettings->network().getAddr().c_str());
    quint16 port(static_cast<quint16>(_spSettings->network().getPort()));

    if(_spWebSocketServer->listen(addr, port))
    {
        Log::write(QString("Server listening on address \"" + _spWebSocketServer->serverUrl().toString()).toStdString());
        connect(_spWebSocketServer.get(), &QWebSocketServer::newConnection, this, &Web_socket_server::slotNewConnection);
        connect(_spWebSocketServer.get(), &QWebSocketServer::closed, this, &Web_socket_server::slotServerClose);
        connect(_spWebSocketServer.get(), &QWebSocketServer::serverError, this, &Web_socket_server::slotServerClose);
    }
    else
        Log::write("Невозможно запустить WS сервер!");
}

Web_socket_server::~Web_socket_server()
{
    Log::write(QString("Server stop").toStdString());
    std::cout << "Server stop\n";
    _spWebSocketServer->close();
}

void Web_socket_server::slotNewConnection()
{
    auto pSocket = _spWebSocketServer->nextPendingConnection();
    Log::write(QString(getIdentifier(pSocket) + " connected!").toStdString());
    std::cout << getIdentifier(pSocket).toStdString() << " connected!\n";
    pSocket->setParent(this);

    connect(pSocket, &QWebSocket::textMessageReceived, this, &Web_socket_server::slotGet_message);
    connect(pSocket, &QWebSocket::disconnected, this, &Web_socket_server::socketDisconnected);

    _clients.insert(pSocket);

    pSocket->sendTextMessage("protocol");
}

void Web_socket_server::slotGet_message(const QString &message)
{
    auto pSocket = qobject_cast<QWebSocket *>(sender());

    if(message.startsWith(MONITOR_PROTOCOL))
        Monitor_Protocol monitorProtocol(pSocket, _spSettings, message.toStdString());
    else if(message.startsWith(MANAGER_PROTOCOL))
    {
        Manager_Protocol managerProtocol(pSocket, _spSettings, message.toStdString());
        _auth_session[pSocket] = managerProtocol.getSession_id();
        std::cout << managerProtocol.getSession_id() << std::endl;

//        for(auto [key, value] :_auth_session)
//        {
//            std::cout << key->peerAddress().toString().toStdString()
//                      << ":" << QString::number(key->peerPort()).toStdString()
//                      << " session id= " << value << std::endl;
//        }
    }
}

void Web_socket_server::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    Log::write(QString(getIdentifier(pClient) + " disconnected!").toStdString());
    std::cout << getIdentifier(pClient).toStdString() << " disconnected!\n";
    _auth_session.erase(pClient);
    if(pClient)
    {
        _clients.erase(pClient);
        pClient->deleteLater();
    }
}

void Web_socket_server::slotServerClose()
{
    std::cout << "server stop\n";
}

void Web_socket_server::slotServerError(QWebSocketProtocol::CloseCode closeCode)
{
    qDebug() << closeCode;
}

QString Web_socket_server::getIdentifier(QWebSocket *peer)
{
    return QStringLiteral("%1:%2").arg(peer->peerAddress().toString(),
                                       QString::number(peer->peerPort()));
}
