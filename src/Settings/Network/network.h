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

    std::string getLogin() const;
    void setLogin(const std::string &login);

    std::string getPassword() const;
    void setPassword(const std::string &password);

private:
    std::string _addr;
    int _port;
    bool _enable;
    std::string _login;
    std::string _password;

};

#endif // NETWORK_H
