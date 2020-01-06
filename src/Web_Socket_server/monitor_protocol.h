#ifndef MONITOR_PROTOCOL_H
#define MONITOR_PROTOCOL_H

#include "Settings/settings.h"
#include "abstract_protocol.h"

#include <memory>
#include <QWebSocket>
#include <QWebSocketServer>

#include <QObject>

class Monitor_Protocol : public QObject, Abstract_Protocol
{
public:
    Monitor_Protocol(QWebSocket* pSocket,
                     std::shared_ptr<Settings> setting,
                     const std::string &message,
                     QObject *parent = nullptr);

private:
    void fill_shift_in_sending_data(std::string &message) const;
    void fill_lesson_in_sending_data(const Shift &shift, std::string &message) const;

    void sendData(QWebSocket *web_socket) override;
    void checkMessage(const std::string &message) override;
};

#endif // MONITOR_PROTOCOL_H
