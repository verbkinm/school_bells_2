#ifndef LOG_H
#define LOG_H

#include <string>

class Log
{
public: 
    static void write(const std::string &file_name, const std::string &data);
};

#endif // LOG_H
