#ifndef CURRENT_SHEDULE_H
#define CURRENT_SHEDULE_H

#include <map>
#include <QTimer>
#include "Settings/Shedule/time/time.h"
#include "Media_Player/media_player.h"
#include "Program_exec/program_exec.h"
#include "../Settings/General/general.h"

class Current_Shedule : QObject
{
    Q_OBJECT
public:
    Current_Shedule(QObject *parent = nullptr);

    void add(const Time &time, const std::string &sound);
    void remove(const Time &time);
    void clear();

    void printTable() const;
    void watch();
    void unwatch();

    void setGeneral_settings(const General *general);

private:
    void check_shedule_size() const;
    void setNext_call_according_local_time();
    void circularity_of_iterator();

    std::map<Time, std::string> _call_table;
    std::map<Time, std::string>::iterator _current_iterator;
    QTimer _timer;
    Media_Player _player;
    Program_Exec _cmd;
    General const *_general;

private slots:
    void slotTimer_out();
};

#endif // CURRENT_SHEDULE_H
