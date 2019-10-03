TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += qt

SOURCES += \
        day\day.cpp \
        general\network.cpp \
        general\general.cpp \
        settings.cpp \
        shedule\time\time.cpp \
        shedule\lesson\lesson.cpp \
        main.cpp \
        shedule\shedule.cpp \
        shedule\shift\shift.cpp

HEADERS += \
    day\day.h \
    general\network.h \
    general\general.h \
    settings.h \
    shedule\time\time.h \
    shedule\lesson\lesson.h \
    shedule\shedule.h \
    shedule\shift\shift.h

DISTFILES +=
