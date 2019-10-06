#include <iostream>
#include <Settings/settings.h>
#include "Current_Shedule/current_shedule.h"
#include "Media_Player/media_player.h"

#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    std::setlocale(LC_ALL,"ru_RU.UTF-8");
//    std::setlocale(LC_ALL,"ru_RU.UTF-8");
    std::string s = "Привет";
    std::cout << s << std::endl;

    std::wstring ws = L"Привет";
    std::wcout << ws << std::endl;




//    Media_Player media_player;

//    media_player.play("C:\\Qt\\myProg\\bells\\sounds\\Повседневный.mp3");
//    Settings settings;
//    Current_Shedule current_shedule;

//    const General  *general = settings.general();
//    const std::array<Day, 7> *days = settings.days();
//    const std::vector<Shedule> *shedules = settings.shedules();

//    size_t current_day_of_week = Day::current_day_of_week();
//    if(!days->at(current_day_of_week).isEnable())
//        return 1;

//    Shedule shedule = shedules->at(days->at(current_day_of_week).getNumber_shedule_of_day());

//    for(const auto &shift : shedule._shifts)
//    {
//        if(!shift.isEnable())
//            continue;
//        for (const auto &lesson : shift._lessons)
//        {
//            if(!lesson.isEnable())
//                continue;
//            if(general->getCall_before_lesson())
//                current_shedule.add(lesson.getTime_begin() - Time(0, general->getNumber_of_minutes_to_call_before_lesson()), general->getManual_call());
//            current_shedule.add(lesson.getTime_begin(), lesson.getSound_begin());
//            current_shedule.add(lesson.getTime_end(), lesson.getSound_end());
//        }
//    }


//    try
//    {
//        Media_Player media_player;
//        media_player.play(current_shedule.getNext_call().sound());
//        std::cout << current_shedule.getNext_call().time().toString() << " " << current_shedule.getNext_call().sound().c_str() << std::endl;
//        std::cout << current_shedule.getLast_call().time().toString() << std::endl;
//    }
//    catch(std::out_of_range &)
//    {
//        std::cout << "shedule is empty" << std::endl;
//    }



    return a.exec();
//    return 1;
}

