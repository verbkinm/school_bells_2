#ifndef MANAGER_PROTOCOL_H
#define MANAGER_PROTOCOL_H

#include "Settings/settings.h"
#include "abstract_protocol.h"

#include <memory>
#include <QWebSocket>
#include <QWebSocketServer>

#include <QObject>

class Manager_Protocol : public QObject, Abstract_Protocol
{
public:
    Manager_Protocol(QWebSocket* pSocket,
                     std::shared_ptr<Settings> setting,
                     const std::string &message,
                     QObject *parent = nullptr);

    uint64_t getSession_id() const;

private:
    void sendData(QWebSocket *web_socket) override;
    void checkMessage(const std::string &message) override;

    std::string _data;
    uint64_t _session_id;
};

#endif // MANAGER_PROTOCOL_H
