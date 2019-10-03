#ifndef NETWORK_H
#define NETWORK_H

#include <string>

class Network
{
public:
    Network();

    std::string getAddr() const;
    void setAddr(const std::string &value);

    int getPort() const;
    void setPort(int value);

    bool isRun_at_program_start() const;
    void setRun_at_program_start(bool value);

private:
    std::string _addr;
    int _port;
    bool _run_at_program_start;

};

#endif // NETWORK_H
