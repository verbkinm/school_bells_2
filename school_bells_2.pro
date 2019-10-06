TARGET = school_bells_2
TEMPLATE = app
QT += core multimedia
CONFIG += console c++17
CONFIG -= app_bundle

SOURCES += \
        Current_Shedule\call.cpp \
        Current_Shedule\current_shedule.cpp \
        Settings/Day/day.cpp \
        Settings/General/general.cpp \
        Settings/General/network.cpp \
        Settings/Shedule/lesson/lesson.cpp \
        Settings/Shedule/shedule.cpp \
        Settings/Shedule/shift/shift.cpp \
        Settings/Shedule/time/time.cpp \
        Settings/settings.cpp \
        main.cpp \
        Media_Player/media_player.cpp

HEADERS += \
    Current_Shedule\call.h \
    Current_Shedule\current_shedule.h \
    Settings/Day/day.h \
    Settings/General/general.h \
    Settings/General/network.h \
    Settings/Shedule/lesson/lesson.h \
    Settings/Shedule/shedule.h \
    Settings/Shedule/shift/shift.h \
    Settings/Shedule/time/time.h \
    Media_Player/media_player.h \
    Settings/settings.h \

DISTFILES +=
