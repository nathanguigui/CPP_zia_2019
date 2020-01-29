//
// Created by guigui on 1/18/20.
//

#ifndef CPP_RTYPE_2019_TCPSERVER_HPP
#define CPP_RTYPE_2019_TCPSERVER_HPP

#include "core/ServerConfig/ServerConfig.hpp"
#include "core/VirtualHostsConfig/VirtualHostsConfig.hpp"
#include "core/VirtualHostManager/VirtualHostManager.hpp"
#include "core/ModuleManager/ModuleManager.hpp"
#include "core/TcpHandler/TcpHandler.hpp"
#include "core/TcpConnection/TcpConnection.hpp"


class TcpServer {
public:
    explicit TcpServer(boost::asio::io_service &io_service, ServerConfig *config, VirtualHostsConfig *virtualHost,
                       ModuleManager *moduleManger);
private:
    void start_accept();
    void handle_accept(TcpConnection::pointer new_connection, const boost::system::error_code& error);
    boost::asio::ip::tcp::acceptor acceptor_;
    boost::asio::io_service &ioService_;
    TcpHandler connectionsManager_;
    ServerConfig *serverConfig_;
    VirtualHostsConfig *virtualHostsConfig_;
    VirtualHostManager *virtualHostManagers_;
    ModuleManager *moduleManager_;
};

#endif //CPP_RTYPE_2019_TCPSERVER_HPP
