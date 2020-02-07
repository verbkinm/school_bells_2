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
    if(_spWebSocketServer->listen(QHostAddress(_spSettings->network().getAddr().c_str()), _spSettings->network().getPort()))
    {
        Log::write("Server listening on address \"" + _spWebSocketServer->serverUrl().toString().toStdString());
        connect(_spWebSocketServer.get(), &QWebSocketServer::newConnection, this, &Web_socket_server::slotNewConnection);
        connect(_spWebSocketServer.get(), &QWebSocketServer::closed, this, &Web_socket_server::slotServerClose);
        connect(_spWebSocketServer.get(), &QWebSocketServer::serverError, this, &Web_socket_server::slotServerClose);
    }
    else
        Log::write("start WS server error!");
}

Web_socket_server::~Web_socket_server()
{
    Log::write("Server stop");
    _spWebSocketServer->close();
}

void Web_socket_server::slotNewConnection()
{
    auto pSocket = _spWebSocketServer->nextPendingConnection();
    Log::write(getIdentifier(pSocket) + " connected!");
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
        for(const auto value : _auth_session)
            if(value == managerProtocol.getSession_id())
                managerProtocol.continueSession();

        if(managerProtocol.getAuth())
            _auth_session.insert(managerProtocol.getSession_id());
    }
}

void Web_socket_server::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    Log::write(getIdentifier(pClient) + " disconnected!");
    if(pClient)
    {
        _clients.erase(pClient);
        pClient->deleteLater();
    }
}

void Web_socket_server::slotServerClose()
{
    Log::write("Server stop");
}

void Web_socket_server::slotServerError(QWebSocketProtocol::CloseCode closeCode)
{
    std::cout << closeCode << "\n";
}

std::string Web_socket_server::getIdentifier(QWebSocket *peer) const
{
    return peer->peerAddress().toString().toStdString() + ":" + std::to_string(peer->peerPort());
}
