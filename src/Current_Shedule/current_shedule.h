#ifndef CURRENT_SHEDULE_H
#define CURRENT_SHEDULE_H

#include <map>
#include <memory>
#include <QTimer>
#include "Media_Player/media_player.h"
#include "Program_exec/program_exec.h"
#include "../Settings/settings.h"
#include "../observer.h"

class Current_Shedule : QObject, public Observer
{
    Q_OBJECT
public:
    Current_Shedule(std::shared_ptr<const Settings> settings, QObject *parent = nullptr);

    void update() override;

private:
    void printTable() const;

    void setNext_call_according_local_time();
    void circularity_of_iterator();

    void fill_current_shedule();
    void fill_shifts(const Shift &shift);
    void add(const Time_of_day &time, const std::string &sound);

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
