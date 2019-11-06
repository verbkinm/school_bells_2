#ifndef SCHOOL_BELLS_H
#define SCHOOL_BELLS_H

#include <iostream>
#include <memory>
#include <Settings/settings.h>
#include "Settings/General/general.h"
#include "Current_Shedule/current_shedule.h"
#include "Media_Player/media_player.h"
#include <log.h>

#include "Program_exec/program_exec.h"
#include "Web_Socket_server/web_socket_server.h"

class School_bells : QObject
{
    Q_OBJECT
public:
    School_bells(QObject *parent = nullptr);
    ~School_bells();

private:
    void fill_current_shedule();
    void fill_shifts(const Shift &shift);
    void create_day_shedule();

    std::shared_ptr<Settings> _spSettings;
    Current_Shedule _current_shedule;
    std::unique_ptr<Web_socket_server>_spWeb_socket_server;

    QTimer _day_timer;
    size_t _current_day_of_week;

private slots:
    void slotNew_day();
    void slotCreate_day_shedule();
};

#endif // SCHOOL_BELLS_H
