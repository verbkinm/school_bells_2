#include "network.h"

Network::Network() : _addr("localhost"), _port(80), _run_at_program_start(false)
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

bool Network::isRun_at_program_start() const
{
    return _run_at_program_start;
}

void Network::setRun_at_program_start(bool value)
{
    _run_at_program_start = value;
}
