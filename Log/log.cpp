#include <iostream>
#include <fstream>
#include <ctime>

#include "log.h"

void Log::write(const std::string &file_name, const std::string &data)
{
    std::ofstream file;
    file.open(file_name, std::ios::app);
    if(!file)
    {
        std::cerr << "Couldn't open file \"" << file_name << "\"" << std::endl;
        return;
    }

    time_t rawtime;
    tm *timeinfo;
    time(&rawtime);
    timeinfo=localtime(&rawtime);

    char out_str[80];
    strftime(out_str, 80, "%x %X: ", timeinfo);
    file << out_str << data << std::endl;

    file.close();
}
