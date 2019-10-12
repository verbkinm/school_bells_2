#include "settings.h"

Settings::Settings() : _settings(QSettings::IniFormat, QSettings::UserScope, "LYCEUM", "bells2")
{
    _settings.setIniCodec("utf8");

    read_settings();
    write_settings();
}

void Settings::read_settings()
{
    read_settings_general();
    read_settings_network();
    read_settings_days();
    read_settings_shedule();
}

void Settings::read_settings_general()
{
    _general.setManual_call(_settings.value("manual_call", "нет").toString().toStdString());
    _general.setSound_dir_path(_settings.value("sound_dir_path", "").toString().toStdString());
    _general.setCall_before_lesson(_settings.value("call_before_lesson", false).toBool());
    _general.setSound_before_lesson(_settings.value("sound_before_lesson", "нет").toString().toStdString());
    _general.setNumber_of_minutes_to_call_before_lesson(_settings.value("number_of_minutes_to_call_before_lesson", 0).toInt());

    _general.setPrograms_before_bell(_settings.value("programs_before_bell", "").toString().toStdString());
    _general.setPrograms_after_bell(_settings.value("programs_after_bell", "").toString().toStdString());
}

void Settings::read_settings_network()
{
    _settings.beginGroup("TCP_Server");
    _network.setAddr(_settings.value("addr", "localhost").toString().toStdString());
    _network.setPort(_settings.value("port", 80).toInt());
    _network.setEnable(_settings.value("enable", false).toBool());
    _settings.endGroup();
}

void Settings::read_settings_days()
{
    for(size_t i = 0; i < 7; ++i)
    {
        _settings.beginGroup("Days" + QString::number(i));
        _days[i].setEnable(_settings.value("enable", false).toBool());
        _days[i].setNumber_shedule_of_day(_settings.value("number_shedule_of_day", 0).toULongLong());
        _settings.endGroup();
    }
}

void Settings::read_settings_shedule()
{
    int shedule_count = _settings.childGroups().filter(QRegExp("^Shedule\\d")).length();
    if(shedule_count < 1)
        shedule_count = 2;

    for(int shedule_number = 0; shedule_number < shedule_count; ++shedule_number)
    {
        _settings.beginGroup("Shedule" + QString::number(shedule_number));
        Shedule shedule;
        shedule.setName(_settings.value("name", _settings.group()).toString().toStdString());

        read_settings_shedule_shift(shedule);

        _shedules.push_back(shedule);
        _settings.endGroup();
    }
}

void Settings::read_settings_shedule_shift(Shedule &shedule)
{
    int shift_count = _settings.allKeys().filter(QRegExp("^shift\\d_enable")).length();
    if(shift_count < 1)
        shift_count = 2;

    for(int shift_number = 0; shift_number < shift_count; ++shift_number)
    {
        Shift shift;
        shift.setEnable(_settings.value("shift" + QString::number(shift_number) + "_enable", false).toBool());
        shift.setStart_number_of_lesson(_settings.value("shift" + QString::number(shift_number) + "_start_number_of_lesson", 1).toInt());

        read_settings_shedule_lesson(shift, shift_number);
        shedule._shifts.push_back(shift);
    }
}

void Settings::read_settings_shedule_lesson(Shift &shift, int shift_number)
{
    int lesson_count_int_shift = _settings.allKeys().filter(QRegExp("^shift" + QString::number(shift_number) + "_lesson\\d_enable")).length();
    if(lesson_count_int_shift < 1)
        lesson_count_int_shift = 7;

    for(int lesson_number = 0; lesson_number < lesson_count_int_shift; ++lesson_number)
    {
        Lesson lesson;
        lesson.setEnable(_settings.value("shift" + QString::number(shift_number) + "_lesson" + QString::number(lesson_number) + "_enable", false).toBool());
        lesson.setSound_begin(_settings.value("shift" + QString::number(shift_number) + "_lesson" + QString::number(lesson_number) + "_sound_begin", "нет").toString().toStdString());
        lesson.setSound_end(_settings.value("shift" + QString::number(shift_number) + "_lesson" + QString::number(lesson_number) + "_sound_end", "нет").toString().toStdString());

        Time time(0,0);
        time.setFrom_string(_settings.value("shift" + QString::number(shift_number) + "_lesson" + QString::number(lesson_number) + "_time_begin", "00:00").toString().toStdString());
        lesson.setTime_begin(time);
        time.setFrom_string(_settings.value("shift" + QString::number(shift_number) + "_lesson" + QString::number(lesson_number) + "_time_end", "00:00").toString().toStdString());
        lesson.setTime_end(time);

        shift._lessons.push_back(lesson);
    }
}

void Settings::write_settings()
{
    write_settings_general();
    write_settings_network();
    write_settings_days();
    write_settings_shedule();
    _settings.sync();
}

void Settings::write_settings_general()
{
    _settings.setValue("manual_call", QString::fromUtf8(_general.getManual_call().c_str()));
    _settings.setValue("sound_dir_path", QString::fromUtf8(_general.getSound_dir_path().c_str()));
    _settings.setValue("call_before_lesson", _general.getCall_before_lesson());
    _settings.setValue("sound_before_lesson", QString::fromUtf8(_general.getSound_before_lesson().c_str()));
//    _settings.setValue("sound_before_lesson", "C:\\Users\\verbkinm\\Рабочий стол\\Гимн Лицея_ Павленко.mp3");
    _settings.setValue("number_of_minutes_to_call_before_lesson", _general.getNumber_of_minutes_to_call_before_lesson());

    _settings.setValue("programs_before_bell", _general.getPrograms_before_bell().c_str());
    _settings.setValue("programs_after_bell", _general.getPrograms_after_bell().c_str());
}

void Settings::write_settings_network()
{
    _settings.beginGroup("TCP_Server");
    _settings.setValue("addr", QString::fromUtf8(_network.getAddr().c_str()));
    _settings.setValue("port", _network.getPort());
    _settings.setValue("enable", _network.isEnable());
    _settings.endGroup();
}

void Settings::write_settings_days()
{
    for(size_t i = 0; i < 7; ++i)
    {
        _settings.beginGroup("Days"+QString::number(i));
        _settings.setValue("enable", _days[i].isEnable());
        _settings.setValue("number_shedule_of_day", _days[i].getNumber_shedule_of_day());
        _settings.endGroup();
    }
}

void Settings::write_settings_shedule()
{
    for(size_t shedule_number = 0; shedule_number < _shedules.size(); ++shedule_number)
    {
        _settings.beginGroup("Shedule" + QString::number(static_cast<int>(shedule_number)));
        write_settings_shedule_shift(shedule_number);
        _settings.endGroup();
    }
}

void Settings::write_settings_shedule_shift(size_t shedule_number)
{
    _settings.setValue("name", QString::fromUtf8(_shedules.at(shedule_number).name().c_str()));
    for(size_t shift_number = 0; shift_number < _shedules.at(shedule_number)._shifts.size(); ++shift_number)
        write_settings_shedule_lesson(shedule_number, shift_number);
}

void Settings::write_settings_shedule_lesson(size_t shedule_number, size_t shift_number)
{
    _settings.setValue("shift" + QString::number(shift_number) + "_enable", _shedules.at(shedule_number)._shifts.at(shift_number).isEnable());
    _settings.setValue("shift" + QString::number(shift_number) + "_start_number_of_lesson", _shedules.at(shedule_number)._shifts.at(shift_number).getStart_number_of_lesson());
    for(size_t lesson_number = 0; lesson_number < _shedules.at(shift_number)._shifts.at(shift_number).getNumber_of_lessons(); ++lesson_number)
    {
        _settings.setValue("shift" + QString::number(shift_number) + "_lesson" + QString::number(lesson_number) + "_enable", _shedules.at(shedule_number)._shifts.at(shift_number)._lessons.at(lesson_number).isEnable());
        _settings.setValue("shift" + QString::number(shift_number) + "_lesson" + QString::number(lesson_number) + "_sound_begin", QString::fromUtf8(_shedules.at(shedule_number)._shifts.at(shift_number)._lessons.at(lesson_number).getSound_begin().c_str()));
        _settings.setValue("shift" + QString::number(shift_number) + "_lesson" + QString::number(lesson_number) + "_sound_end", QString::fromUtf8(_shedules.at(shedule_number)._shifts.at(shift_number)._lessons.at(lesson_number).getSound_end().c_str()));
        _settings.setValue("shift" + QString::number(shift_number) + "_lesson" + QString::number(lesson_number) + "_time_begin", QString::fromUtf8(_shedules.at(shedule_number)._shifts.at(shift_number)._lessons.at(lesson_number).getTime_begin_str().c_str()));
        _settings.setValue("shift" + QString::number(shift_number) + "_lesson" + QString::number(lesson_number) + "_time_end", QString::fromUtf8(_shedules.at(shedule_number)._shifts.at(shift_number)._lessons.at(lesson_number).getTime_end_str().c_str()));
    }
}

const General *Settings::general() const
{
    return &_general;
}

void Settings::setGeneral(const General &general)
{
    _general = general;
}

const Network *Settings::network() const
{
    return &_network;
}

const std::array<Day, 7> *Settings::days() const
{
    return &_days;
}

const std::vector<Shedule> *Settings::shedules() const
{
    return &_shedules;
}
