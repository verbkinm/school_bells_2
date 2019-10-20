#include "web_socket_server.h"
#include "Log/log.h"

#include <QWebSocket>

#define MONITOR_PROTOCOL "monitor_protocol"
#define MANAGER_PROTOCOL "manager_protocol"

static QString getIdentifier(QWebSocket *peer)
{
    return QStringLiteral("%1:%2").arg(peer->peerAddress().toString(),
                                       QString::number(peer->peerPort()));
}

Web_socket_server::Web_socket_server(QHostAddress addr, quint16 port, QObject *parent) :
    QObject(parent),
    m_pWebSocketServer(new QWebSocketServer(QStringLiteral("Chat Server"),
                       QWebSocketServer::NonSecureMode, this))
{
    if (m_pWebSocketServer->listen(addr, port))
    {
        Log::write(QString("Server listening on address \"" + m_pWebSocketServer->serverUrl().toString()).toStdString());
        QTextStream(stdout) << "Server listening on address \"" << m_pWebSocketServer->serverUrl().toString() + "\n";
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection, this, &Web_socket_server::onNewConnection);
    }
}

Web_socket_server::~Web_socket_server()
{
    m_pWebSocketServer->close();
}

void Web_socket_server::onNewConnection()
{
    auto pSocket = m_pWebSocketServer->nextPendingConnection();
    Log::write(QString(getIdentifier(pSocket) + " connected!").toStdString());
    QTextStream(stdout) << getIdentifier(pSocket) << " connected!\n";
    pSocket->setParent(this);

    connect(pSocket, &QWebSocket::textMessageReceived, this, &Web_socket_server::slotGet_message);
    connect(pSocket, &QWebSocket::disconnected, this, &Web_socket_server::socketDisconnected);

    m_clients << pSocket;

    emit signalNew_connection(pSocket);
}

void Web_socket_server::slotSend_message(QWebSocket *web_socket, const QString &message)
{
    web_socket->sendTextMessage(message);
}

void Web_socket_server::slotGet_message(const QString &message)
{
    auto pSocket = qobject_cast<QWebSocket *>(sender());

    if(message == MONITOR_PROTOCOL)
        emit signalGet_message_from_monitor(pSocket);
    if(message == MANAGER_PROTOCOL)
        ;
}

void Web_socket_server::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    Log::write(QString(getIdentifier(pClient) + " disconnected!").toStdString());
    QTextStream(stdout) << getIdentifier(pClient) << " disconnected!\n";
    if (pClient)
    {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}
