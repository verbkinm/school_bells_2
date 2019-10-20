#ifndef WEB_SOCKET_SERVER_H
#define WEB_SOCKET_SERVER_H

#include <QList>

#include <QWebSocket>
#include <QWebSocketServer>

class Web_socket_server : public QObject
{
    Q_OBJECT
public:
    explicit Web_socket_server(QHostAddress addr = QHostAddress::Any, quint16 port = 80, QObject *parent = nullptr);
    ~Web_socket_server() override;


signals:
    void signalNew_connection(QWebSocket *);
    void signalGet_message_from_monitor(QWebSocket *);

public slots:
    void onNewConnection();
    void slotSend_message(QWebSocket *web_socket, const QString &message);
    void slotGet_message(const QString &message);
    void socketDisconnected();

private:
    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;
};

#endif //WEB_SOCKET_SERVER_H
