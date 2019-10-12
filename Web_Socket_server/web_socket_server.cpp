#include "web_socket_server.h"

#include <QWebSocket>

static QString getIdentifier(QWebSocket *peer)
{
    return QStringLiteral("%1:%2").arg(peer->peerAddress().toString(),
                                       QString::number(peer->peerPort()));
}

Web_socket_server::Web_socket_server(quint16 port, QObject *parent) :
    QObject(parent),
    m_pWebSocketServer(new QWebSocketServer(QStringLiteral("Chat Server"),
                       QWebSocketServer::NonSecureMode, this))
{
    if (m_pWebSocketServer->listen(QHostAddress::Any, port))
    {
        QTextStream(stdout) << "Chat Server listening on port " << port << '\n';
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
    QTextStream(stdout) << getIdentifier(pSocket) << " connected!\n";
    pSocket->setParent(this);

//    connect(pSocket, &QWebSocket::textMessageReceived, this, &Web_socket_server::processMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &Web_socket_server::socketDisconnected);

    m_clients << pSocket;

    emit signalNew_connection(pSocket);

//    QByteArray byte_array;
//    byte_array.push_back("monitor_table");
//    pSocket->sendTextMessage("monitor_table,0,8:30,9:45");
}

void Web_socket_server::processMessage(QWebSocket *web_socket, const QString &message)
{
    web_socket->sendTextMessage(message);
//    QWebSocket *pSender = qobject_cast<QWebSocket *>(sender());
//    for (auto pClient : m_clients)
//    {
//        if (pClient != pSender) //don't echo message back to sender
//            pClient->sendTextMessage(message);
//    }
}

void Web_socket_server::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    QTextStream(stdout) << getIdentifier(pClient) << " disconnected!\n";
    if (pClient)
    {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}
