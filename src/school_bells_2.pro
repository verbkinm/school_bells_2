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
        Settings/settings.cpp \
        Web_Socket_server/abstract_protocol.cpp \
        Web_Socket_server/manager_protocol.cpp \
        Web_Socket_server/monitor_protocol.cpp \
        Web_Socket_server/web_socket_server.cpp \
        main.cpp \
        Media_Player/media_player.cpp \
        observer.cpp \
        school_bells.cpp \
        subject.cpp

HEADERS += \
    Program_exec/program_exec.h \
    Current_Shedule\current_shedule.h \
    Settings/Day/day.h \
    Settings/General/general.h \
    Settings/Network/network.h \
    Settings/Shedule/shift/lesson/lesson.h \
    Settings/Shedule/shedule.h \
    Settings/Shedule/shift/shift.h \
    Media_Player/media_player.h \
    Settings/settings.h \
    Web_Socket_server/abstract_protocol.h \
    Web_Socket_server/manager_protocol.h \
    Web_Socket_server/monitor_protocol.h \
    Web_Socket_server/web_socket_server.h \
    observer.h \
    school_bells.h \
    subject.h

DISTFILES +=

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/Time_of_day/ -lTime_of_day
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/Time_of_day/ -lTime_of_dayD
else:unix:!macx: LIBS += -L$$PWD/lib/Time_of_day/ -lTime_of_day

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/Log/ -lLog
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/Log/ -lLogD
else:unix:!macx: LIBS += -L$$PWD/lib/Log/ -lLog

INCLUDEPATH += $$PWD/lib/include
DEPENDPATH += $$PWD/lib/include
