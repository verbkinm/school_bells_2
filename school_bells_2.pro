TARGET = school_bells_2
TEMPLATE = app
QT += core multimedia websockets
CONFIG += console c++17
CONFIG -= app_bundle

SOURCES += \
        Program_exec/program_exec.cpp \
        Current_Shedule\current_shedule.cpp \
        Settings/Day/day.cpp \
        Settings/General/general.cpp \
        Settings/Network/network.cpp \
        Settings/Shedule/shift/lesson/lesson.cpp \
        Settings/Shedule/shedule.cpp \
        Settings/Shedule/shift/shift.cpp \
        Settings/Shedule/shift/lesson/time/time.cpp \
        Settings/settings.cpp \
        Log/log.cpp \
        Web_Socket_server/web_socket_server.cpp \
        main.cpp \
        Media_Player/media_player.cpp \
        school_bells.cpp

HEADERS += \
    Program_exec/program_exec.h \
    Current_Shedule\current_shedule.h \
    Settings/Day/day.h \
    Settings/General/general.h \
    Settings/Network/network.h \
    Settings/Shedule/shift/lesson/lesson.h \
    Settings/Shedule/shedule.h \
    Settings/Shedule/shift/lesson_time_state.h \
    Settings/Shedule/shift/shift.h \
    Settings/Shedule/shift/lesson/time/time.h \
    Media_Player/media_player.h \
    Settings/settings.h \
    Log/log.h \
    Web_Socket_server/web_socket_server.h \
    school_bells.h

DISTFILES +=
