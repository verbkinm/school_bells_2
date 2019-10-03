#ifndef GENERAL_H
#define GENERAL_H

#include <string>

class General
{
public:
    General();

    std::string getManual_call() const;
    void setManual_call(const std::string &manual_call);

    std::string getSound_dir_path() const;
    void setSound_dir_path(const std::string &sound_dir_path);

//    Network network;

private:
    std::string _manual_call;
    std::string _sound_dir_path;
};

#endif // GENERAL_H
