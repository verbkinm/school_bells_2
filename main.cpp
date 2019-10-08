#include <iostream>
#include <Settings/settings.h>
#include "Settings/General/general.h"
#include "Current_Shedule/current_shedule.h"
#include "Media_Player/media_player.h"
#include "Log/log.h"
#include "Program_exec/program_exec.h"

#include <windows.h>

#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::cout << "киррилица" << std::endl;

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


    try
    {
        current_shedule.printTable();
        Media_Player media_player;
//        media_player.play(current_shedule.getNext_call().sound());
//        media_player.play("C:\\1.mp3");
//        std::clog << current_shedule.getNext_call().time().toString() << std::endl;
//        std::clog << current_shedule.getLast_call().time().toString() << std::endl;
    }
    catch(std::out_of_range &)
    {
        std::cout << "shedule is empty" << std::endl;
    }

    QMediaPlayer _player;
    std::string _sound = "C:\\1.mp3";
    _player.setVolume(100);
    _player.setMedia(QUrl::fromLocalFile(_sound.c_str()));
    _player.play();

    return a.exec();
}

