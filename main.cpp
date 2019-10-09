#include <iostream>
#include <Settings/settings.h>
#include "Settings/General/general.h"
#include "Current_Shedule/current_shedule.h"
#include "Media_Player/media_player.h"
#include "Log/log.h"
#include "Program_exec/program_exec.h"
#include "timer.h"

#include <windows.h>

#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Current_Shedule current_shedule;

    Settings settings;

    const General  *general = settings.general();
    const std::array<Day, 7> *days = settings.days();
    const std::vector<Shedule> *shedules = settings.shedules();

    size_t current_day_of_week = Day::current_day_of_week();
    auto current_day = days->at(current_day_of_week);
    if(!current_day.isEnable())
        return 1;

    Shedule shedule = shedules->at(current_day.getNumber_shedule_of_day());

    for(const auto &shift : shedule._shifts)
    {
        if(!shift.isEnable())
            continue;
        for (const auto &lesson : shift._lessons)
        {
            if(!lesson.isEnable())
                continue;
            if(general->getCall_before_lesson())
                current_shedule.add(lesson.getTime_begin() - Time(0, general->getNumber_of_minutes_to_call_before_lesson()), general->getSound_before_lesson());
            current_shedule.add(lesson.getTime_begin(), lesson.getSound_begin());
            current_shedule.add(lesson.getTime_end(), lesson.getSound_end());
        }
    }

    current_shedule.printTable();
    current_shedule.watch();

//    Media_Player media_player;
//    try
//    {
//        current_shedule.printTable();
////        media_player.play(current_shedule.getNext_call().sound());
////        media_player.play("C:\\Qt\\myProg\\bells\\sounds\\Зарядка.mp3");
//    }
//    catch(std::out_of_range &)
//    {
//        std::cout << "shedule is empty" << std::endl;
//    }


    return a.exec();
}

