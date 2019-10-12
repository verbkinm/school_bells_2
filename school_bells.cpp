#include "school_bells.h"

#define TIMER_INTERVAL 1000
#define WRONG_DAY_OF_WEEK 100

School_bells::School_bells(QObject *parent) : QObject (parent), _current_day_of_week(WRONG_DAY_OF_WEEK)
{
    connect(&_day_timer, SIGNAL(timeout()), SLOT(slotNew_day()));
    slotNew_day();

    if(_settings.network()->isEnable())
    {
        _spWeb_socket_server = std::make_unique<Web_socket_server>();
        connect(&*_spWeb_socket_server, SIGNAL(signalNew_connection(QWebSocket *)), this, SLOT(slotSendData(QWebSocket *)));
    }
}

void School_bells::check_current_day()
{
    Day current_day = _settings.days()->at(Day::current_day_of_week());
    if(current_day.isEnable())
        _shedule = _settings.shedules()->at(current_day.getNumber_shedule_of_day());
}

void School_bells::fill_current_shedule()
{
    _current_shedule.unwatch();
    _current_shedule.clear();
    for(const auto &shift : _shedule._shifts)
    {
        if(shift.isEnable())
            fill_shifts(shift);
    }
}

void School_bells::fill_shifts(const Shift &shift)
{
    for (const auto &lesson : shift._lessons)
    {
        if(!lesson.isEnable())
            continue;
        if(_settings.general()->getCall_before_lesson())
            _current_shedule.add(lesson.getTime_begin() - Time(0, _settings.general()->getNumber_of_minutes_to_call_before_lesson()), _settings.general()->getSound_before_lesson());
        _current_shedule.add(lesson.getTime_begin(), lesson.getSound_begin());
        _current_shedule.add(lesson.getTime_end(), lesson.getSound_end());
    }
}

void School_bells::create_day_shedule()
{
    check_current_day();
    fill_current_shedule();

    _current_shedule.setGeneral_settings(_settings.general());
    _current_shedule.watch();
    _current_shedule.printTable();
}

void School_bells::slotNew_day()
{
    if(_current_day_of_week == Day::current_day_of_week())
        return;

    std::cout << "new day" << std::endl;
    _day_timer.stop();
    create_day_shedule();
    _current_day_of_week = Day::current_day_of_week();
    _day_timer.start(TIMER_INTERVAL);
}

void School_bells::slotSendData(QWebSocket *web_socket)
{
    QString message = _current_shedule.getString_from_call_table().c_str();
    _spWeb_socket_server.get()->processMessage(web_socket, message);
}
