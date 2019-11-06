#ifndef CURRENT_SHEDULE_H
#define CURRENT_SHEDULE_H

#include <map>
#include <memory>
#include <QTimer>
#include "Media_Player/media_player.h"
#include "Program_exec/program_exec.h"
#include "../Settings/settings.h"

class Current_Shedule : QObject
{
    Q_OBJECT
public:
    Current_Shedule(std::shared_ptr<const Settings> settings, QObject *parent = nullptr);

    void add(const Time_of_day &time, const std::string &sound);
    void remove(const Time_of_day &time);
    void clear();

    void printTable() const;
    void watch();
    void unwatch();

private:
    void check_shedule_size() const;
    void setNext_call_according_local_time();
    void circularity_of_iterator();

    std::map<Time_of_day, std::string> _call_table;
    std::map<Time_of_day, std::string>::iterator _current_iterator;
    QTimer _timer;
    Media_Player _player;
    Program_Exec _cmd;
    std::shared_ptr<Settings const> _spSettings;

private slots:
    void slotTimer_out();
};

#endif // CURRENT_SHEDULE_H
