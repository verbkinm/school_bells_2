#include "log.h"
#include "manager_protocol.h"

#define SEPARATOR_ARGS std::string(",")
#define SEPARATOR_SYMBOL std::string(":=")

#define MP "manager_protocol"
#define MPA "manager_protocol_auth:"
#define MPS "manager_protocol_session:"

Manager_Protocol::Manager_Protocol(QWebSocket *pSocket,
                                   std::shared_ptr<Settings> setting,
                                   const std::string &message,
                                   QObject *parent) :
    QObject(parent), Abstract_Protocol(pSocket, setting), _session_id(0), _auth(false)
{
    checkMessage(message);
}

uint64_t Manager_Protocol::getSession_id() const
{
    return _session_id;
}

void Manager_Protocol::continueSession()
{
    _data = "manager_protocol_session_continue:" + allSettingsToString();
    sendData(_pSocket);
}

void Manager_Protocol::sendData(QWebSocket *web_socket) const
{
    web_socket->sendTextMessage(_data.c_str());
}

void Manager_Protocol::checkMessage(const std::string &message)
{
    std::string log_msg(_pSocket->peerAddress().toString().toStdString() + ":" + std::to_string(_pSocket->peerPort()) + " Manager connected");

    QString msg(message.c_str());

    if(msg == MP)
    {
        Log::write(log_msg);
        _data = "manager_protocol_auth";
        sendData(_pSocket);
    }
    else if(msg.startsWith(MPA))
    {
        QString raw_string = msg.mid(QString(MPA).length());
        if(raw_string.contains("@") && raw_string.split("@").length() == 2)
        {
            QString login = raw_string.split("@").at(0);
            QString password = raw_string.split("@").at(1);

            if(_spSettings->network().getLogin() == login.toStdString() &&
                    _spSettings->network().getPassword() == password.toStdString())
            {
                Log::write(log_msg + std::string(", Authorization successful"));
                _session_id = static_cast<uint64_t>(rand() * rand() -1);
                _auth = true;
                _data = "manager_protocol_session_id:" + std::to_string(_session_id);
                sendData(_pSocket);
                _data = "manager_protocol_data:" + allSettingsToString();
                sendData(_pSocket);
            }
            else
            {
                _data = "manager_protocol_auth_error";
                sendData(_pSocket);
                Log::write(log_msg + ", Authorization failed");
            }
        }
    }
    else if(msg.startsWith(MPS))
    {
        QString raw_string = msg.mid(QString(MPS).length());
        _session_id = raw_string.toULongLong();
    }
}

std::string Manager_Protocol::allSettingsToString() const
{
    return general_to_str() + tcp_server_to_str() + days_to_str() + shedules_to_str();
}

std::string Manager_Protocol::bool_to_str(bool val) const
{
    if(val)
        return "true";
    return "false";
}

std::string Manager_Protocol::general_to_str() const
{
    std::string general = "General,";
    general += "manual_call" + SEPARATOR_SYMBOL + _spSettings->general().getManual_call() + SEPARATOR_ARGS;
    general += "sound_dir_path" + SEPARATOR_SYMBOL + _spSettings->general().getSound_dir_path() + SEPARATOR_ARGS;
    general += "call_before_lesson" + SEPARATOR_SYMBOL + bool_to_str(_spSettings->general().getCall_before_lesson()) + SEPARATOR_ARGS;
    general += "sound_before_lesson" + SEPARATOR_SYMBOL + _spSettings->general().getSound_before_lesson() + SEPARATOR_ARGS;
    general += "number_of_minutes_to_call_before_lesson" + SEPARATOR_SYMBOL + std::to_string(_spSettings->general().getNumber_of_minutes_to_call_before_lesson()) + SEPARATOR_ARGS;
    general += "programs_before_bell" + SEPARATOR_SYMBOL + _spSettings->general().getPrograms_before_bell() + SEPARATOR_ARGS;
    general += "programs_after_bell" + SEPARATOR_SYMBOL + _spSettings->general().getPrograms_after_bell();
    general += ";";
    return general;
}

std::string Manager_Protocol::tcp_server_to_str() const
{
    std::string tcp_server = "TCP_Server,";
    tcp_server += "addr" + SEPARATOR_SYMBOL + _spSettings->network().getAddr() + SEPARATOR_ARGS;
    tcp_server += "port" + SEPARATOR_SYMBOL + std::to_string(_spSettings->network().getPort()) + SEPARATOR_ARGS;
    tcp_server += "enable" + SEPARATOR_SYMBOL + bool_to_str(_spSettings->network().isEnable());
    tcp_server += ";";
    return tcp_server;
}

std::string Manager_Protocol::days_to_str() const
{
    std::string days;
    for(size_t i = 0; i < 7; i++)
    {
        days += "Days" + std::to_string(i) + SEPARATOR_ARGS;
        days += "enable" + SEPARATOR_SYMBOL + bool_to_str(_spSettings->days()->at(i).isEnable()) +SEPARATOR_ARGS;
        days += "number_shedule_of_day" + SEPARATOR_SYMBOL + std::to_string(_spSettings->days()->at(i).getNumber_shedule_of_day());
        days += ";";
    }
    return days;
}

std::string Manager_Protocol::shedules_to_str() const
{
    std::string shedules;
    for(size_t shedule_number = 0; shedule_number < _spSettings->shedules()->size(); shedule_number++)
    {
        shedules += "Shedules,";
        shedules += "name" + SEPARATOR_SYMBOL + _spSettings->shedules()->at(shedule_number).name() + SEPARATOR_ARGS + "\n";
        shedules += shift_to_str(shedule_number);
        shedules += ";";
    }
    return shedules;
}

std::string Manager_Protocol::shift_to_str(size_t shedule_number) const
{
    std::string shifts;
    size_t shift_number = 0;
    for(const auto &shift : _spSettings->shedules()->at(shedule_number)._shifts)
    {
        shifts += "shift" + std::to_string(shift_number) + "_enable" + SEPARATOR_SYMBOL + bool_to_str(shift.isEnable()) + SEPARATOR_ARGS;
        shifts += "shift" + std::to_string(shift_number) + "_start_number_of_lesson" + SEPARATOR_SYMBOL + std::to_string(shift.getStart_number_of_lesson()) + SEPARATOR_ARGS;
        shifts += lessons_tot_str(shift, shift_number) + "\n";
        shift_number++;
    }
    return shifts;
}

std::string Manager_Protocol::lessons_tot_str(const Shift &shift, size_t shift_number) const
{
    std::string lessons;
    size_t lesson_number = 0;
    for(const auto &lesson : shift._lessons)
    {
        lessons += "shift" + std::to_string(shift_number) + "_lesson" + std::to_string(lesson_number) + "_enable" + SEPARATOR_SYMBOL + bool_to_str(lesson.isEnable()) + SEPARATOR_ARGS;
        lessons += "shift" + std::to_string(shift_number) + "_lesson" + std::to_string(lesson_number) + "_sound_begin" + SEPARATOR_SYMBOL + lesson.getSound_begin() + SEPARATOR_ARGS;
        lessons += "shift" + std::to_string(shift_number) + "_lesson" + std::to_string(lesson_number) + "_sound_end" + SEPARATOR_SYMBOL + lesson.getSound_end() + SEPARATOR_ARGS;
        lessons += "shift" + std::to_string(shift_number) + "_lesson" + std::to_string(lesson_number) + "_time_begin" + SEPARATOR_SYMBOL + lesson.getTime_begin().toString() + SEPARATOR_ARGS;
        lessons += "shift" + std::to_string(shift_number) + "_lesson" + std::to_string(lesson_number) + "_time_end" + SEPARATOR_SYMBOL + lesson.getTime_end().toString() + SEPARATOR_ARGS;
        lesson_number++;
    }
    return lessons;
}

bool Manager_Protocol::getAuth() const
{
    return _auth;
}
