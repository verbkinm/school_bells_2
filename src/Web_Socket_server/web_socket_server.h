#ifndef WEB_SOCKET_SERVER_H
#define WEB_SOCKET_SERVER_H

#include "Settings/settings.h"

#include <memory>
#include <QList>
#include <QWebSocket>
#include <QWebSocketServer>

class Web_socket_server : public QObject
{
    Q_OBJECT
public:
    explicit Web_socket_server(std::shared_ptr<Settings> setting, QHostAddress addr = QHostAddress::Any, quint16 port = 80, QObject *parent = nullptr);
    ~Web_socket_server() override;

signals:
    void settingsChanged();

public slots:
    void slotNewConnection();
    void slotGet_message(const QString &message);
    void socketDisconnected();

    void slotSendData(QWebSocket *web_socket);

private:
    void fill_shift_in_sending_data(std::string &message) const;
    void fill_lesson_in_sending_data(const Shift &shift, std::string &message) const;

    void sendData_to_monitor(QWebSocket *web_socket);


    QString getIdentifier(QWebSocket *peer);

    std::unique_ptr<QWebSocketServer> _spWebSocketServer;
    QList<QWebSocket *> m_clients;
    std::shared_ptr<Settings> _spSettings;
};

#endif //WEB_SOCKET_SERVER_H
