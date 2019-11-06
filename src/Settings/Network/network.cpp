#include "network.h"

Network::Network() : _addr("localhost"), _port(80), _enable(false)
{

}

std::string Network::getAddr() const
{
    return _addr;
}

void Network::setAddr(const std::string &value)
{
    _addr = value;
}


int Network::getPort() const
{
    return _port;
}

void Network::setPort(int value)
{
    _port = value;
}

bool Network::isEnable() const
{
    return _enable;
}

void Network::setEnable(bool value)
{
    _enable = value;
}
