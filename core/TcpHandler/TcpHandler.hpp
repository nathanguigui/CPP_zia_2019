//
// Created by guigui on 1/18/20.
//

#ifndef CPP_RTYPE_2019_TCPHANDLER_HPP
#define CPP_RTYPE_2019_TCPHANDLER_HPP

#include "core/TcpConnection/TcpConnection.hpp"
#include <set>

class TcpHandler {
public:
    TcpHandler();
    void startConnection(const TcpConnection::pointer&);
    void stopConnection(const TcpConnection::pointer&);
    void stopAllConnection();
    std::set<TcpConnection::pointer> connections_;
};

#endif //CPP_RTYPE_2019_TCPHANDLER_HPP
