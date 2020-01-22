#include "iostream"
#include "log.h"

#include "monitor_protocol.h"


Monitor_Protocol::Monitor_Protocol(QWebSocket* pSocket,
                                   std::shared_ptr<Settings> setting,
                                   const std::string &message,
                                   QObject *parent) : QObject(parent), Abstract_Protocol(pSocket, setting)
{
    QString log_msg = pSocket->peerAddress().toString() + ":" + QString(pSocket->peerPort()) + " Monitor connected";
    Log::write(log_msg.toStdString());

    checkMessage(message);
}

void Monitor_Protocol::fill_shift_in_sending_data(std::string &message) const
{
    for(size_t shift_number = 0; shift_number < _spSettings->shedule_of_day()._shifts.size(); ++shift_number)
    {
        const Shift shift = _spSettings->shedule_of_day()._shifts.at(shift_number);
        if(!shift.isEnable())
            continue;
        message += std::to_string(shift_number);
        message += "," + std::to_string(shift.getStart_number_of_lesson());
        fill_lesson_in_sending_data(shift, message);
        message += ";";
    }
}

void Monitor_Protocol::fill_lesson_in_sending_data(const Shift &shift, std::string &message) const
{
    for(const Lesson &lesson : shift._lessons)
    {
        if(lesson.isEnable())
        {
            message += "," + lesson.getTime_begin().toString();
            message += "," + lesson.getTime_end().toString();
        }
        else
        {
            message += ", -- : --";
            message += ", -- : --";
        }
    }
}

void Monitor_Protocol::sendData(QWebSocket *web_socket)
{
    std::string message = "monitor_protocol_data,";
    fill_shift_in_sending_data(message);
    web_socket->sendTextMessage(message.c_str());
}

void Monitor_Protocol::checkMessage(const std::string &message)
{
    if(message == "monitor_protocol")
        sendData(_pSocket);
}
