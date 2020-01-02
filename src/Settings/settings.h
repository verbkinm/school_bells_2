#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include "Day/day.h"
#include "Shedule/shedule.h"
#include "General/general.h"
#include "Network/network.h"
#include "../subject.h"

class Settings : public Subject
{
public:
    Settings();

    const General general() const;
    const Network network() const;

    const std::array<Day, 7> *days() const;
    const std::vector<Shedule> *shedules() const;

    Shedule shedule_of_day() const;

private:
    void read_settings();
    void read_settings_general();
    void read_settings_network();
    void read_settings_days();
    void read_settings_shedule();
    void read_settings_shedule_shift(Shedule &shedule);
    void read_settings_shedule_lesson(Shift &shift, int shift_number);

    void write_settings();
    void write_settings_general();
    void write_settings_network();
    void write_settings_days();
    void write_settings_shedule();
    void write_settings_shedule_shift(size_t shedule_number);
    void write_settings_shedule_lesson(size_t shedule_number, size_t shift_number);

    std::array<Day, 7> _days;
    General _general;
    std::vector<Shedule> _shedules;
    Network _network;

    QSettings _settings;
};

#endif // SETTINGS_H
