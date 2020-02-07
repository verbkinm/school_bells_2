#ifndef WEB_SOCKET_SERVER_H
#define WEB_SOCKET_SERVER_H

#include "Settings/settings.h"

#include <memory>
#include <set>
#include <QWebSocket>
#include <QWebSocketServer>

class Web_socket_server : public QObject
{
    Q_OBJECT
public:
    Web_socket_server(std::shared_ptr<Settings> setting, QObject *parent = nullptr);
    ~Web_socket_server();

public slots:
    void slotNewConnection();
    void slotGet_message(const QString &message);

private slots:
    void socketDisconnected();
    void slotServerClose();
    void slotServerError(QWebSocketProtocol::CloseCode closeCode);

private:
    std::string getIdentifier(QWebSocket *peer) const;

    std::unique_ptr<QWebSocketServer> _spWebSocketServer;
    std::set<QWebSocket *> _clients;
    std::shared_ptr<Settings> _spSettings;
    std::set<uint64_t> _auth_session;

};

#endif //WEB_SOCKET_SERVER_H
