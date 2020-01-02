#include "network.h"

Network::Network() : _addr("localhost"), _port(80), _enable(false), _login("admin"), _password("admin")
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

std::string Network::getLogin()
{
    return _login;
}

void Network::setLogin(const std::string &login)
{
    _login = login;
}

std::string Network::getPassword()
{
    return _password;
}

void Network::setPassword(const std::string &password)
{
    _password = password;
}
