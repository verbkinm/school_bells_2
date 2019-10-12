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

    bool isEnable() const;
    void setEnable(bool value);

private:
    std::string _addr;
    int _port;
    bool _enable;

};

#endif // NETWORK_H
