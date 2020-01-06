#ifndef ABSTRACT_PROTOCOL_H
#define ABSTRACT_PROTOCOL_H

#include "Settings/settings.h"

#include <memory>
#include <QWebSocket>
#include <QWebSocketServer>
#include <QObject>

class Abstract_Protocol
{
public:
    Abstract_Protocol(QWebSocket* pSocket,
                      std::shared_ptr<Settings> setting);

    virtual ~Abstract_Protocol();

    virtual void sendData(QWebSocket *web_socket) = 0;
    virtual void checkMessage(const std::string &message) = 0;

    std::shared_ptr<Settings> _spSettings;
    QWebSocket* _pSocket = nullptr;
};

#endif // ABSTRACT_PROTOCOL_H
