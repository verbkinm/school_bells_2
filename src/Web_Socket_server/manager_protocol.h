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
    bool getAuth() const;

    void continueSession();

private:
    void sendData(QWebSocket *web_socket) const override;
    void checkMessage(const std::string &message) override;
    std::string allSettingsToString() const;

    std::string bool_to_str(bool val) const;

    std::string general_to_str() const;
    std::string tcp_server_to_str() const;
    std::string days_to_str() const;

    std::string shedules_to_str() const;
    std::string shift_to_str(size_t shedule_number) const;
    std::string lessons_tot_str(const Shift &shift, size_t shift_number) const;

    std::string _data;
    uint64_t _session_id;
    bool _auth;
};

#endif // MANAGER_PROTOCOL_H
