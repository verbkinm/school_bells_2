#include "abstract_protocol.h"

Abstract_Protocol::Abstract_Protocol(QWebSocket* pSocket,
                                     std::shared_ptr<Settings> setting) :
    _spSettings(setting),
    _pSocket(pSocket)
{

}

Abstract_Protocol::~Abstract_Protocol()
{

}
