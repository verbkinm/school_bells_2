#include "iostream"
#include <string_view>
#include <string>

#include "log.h"
#include "manager_protocol.h"

Manager_Protocol::Manager_Protocol(QWebSocket *pSocket,
                                   std::shared_ptr<Settings> setting,
                                   const std::string &message,
                                   QObject *parent) : QObject(parent), Abstract_Protocol(pSocket, setting), _session_id(0)
{
    checkMessage(message);
}

uint64_t Manager_Protocol::getSession_id() const
{
    return _session_id;
}

void Manager_Protocol::sendData(QWebSocket *web_socket)
{
    web_socket->sendTextMessage(_data.c_str());
}

void Manager_Protocol::checkMessage(const std::string &message)
{
    QString log_msg = _pSocket->peerAddress().toString() + ":" + QString::number(_pSocket->peerPort()) + " Manager connected";

    QString msg(message.c_str());
    if(msg == "manager_protocol")
    {
        std::cout << log_msg.toStdString() << std::endl;
        Log::write(log_msg.toStdString());

        _data = "manager_protocol_auth";
        sendData(_pSocket);
    }
    else if(msg.startsWith("manager_protocol_auth:"))
    {
        QString raw_string = msg.mid(QString("manager_protocol_auth:").length());
        if(raw_string.contains("@") && raw_string.split("@").length() == 2)
        {
            QString login = raw_string.split("@").at(0);
            QString password = raw_string.split("@").at(1);

            if(_spSettings->network().getLogin() == login.toStdString() &&
               _spSettings->network().getPassword() == password.toStdString())
            {
                std::cout << log_msg.toStdString() << ", Authorization successful" << std::endl;
                Log::write(log_msg.toStdString() + std::string(", Authorization successful"));
                _session_id = static_cast<uint64_t>(rand() * rand() -1);
                _data = "manager_protocol_session_id:" + QString::number(_session_id).toStdString();
                sendData(_pSocket);
            }
            else
            {
                std::cout << log_msg.toStdString() << ", Authorization failed" << std::endl;
                Log::write(log_msg.toStdString() + std::string(", Authorization failed"));
            }
        }

    }
}
