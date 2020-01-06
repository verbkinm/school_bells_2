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
    explicit Web_socket_server(std::shared_ptr<Settings> setting, QObject *parent = nullptr);
    ~Web_socket_server() override;

public slots:
    void slotNewConnection();
    void slotGet_message(const QString &message);
    void socketDisconnected();

private:
    QString getIdentifier(QWebSocket *peer);

    std::unique_ptr<QWebSocketServer> _spWebSocketServer;
    std::multiset<QWebSocket *> _clients;
    std::shared_ptr<Settings> _spSettings;
    std::map<QWebSocket *, uint64_t> _auth_session;
};

#endif //WEB_SOCKET_SERVER_H
