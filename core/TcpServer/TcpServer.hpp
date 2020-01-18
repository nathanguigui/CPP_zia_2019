//
// Created by guigui on 1/18/20.
//

#ifndef CPP_RTYPE_2019_TCPSERVER_HPP
#define CPP_RTYPE_2019_TCPSERVER_HPP

#include "core/TcpHandler/TcpHandler.hpp"
#include "core/TcpConnection/TcpConnection.hpp"


class TcpServer {
public:
    explicit TcpServer(boost::asio::io_service& io_service)
    : acceptor_(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 25565)), ioService_(io_service) {
        start_accept();
    }
private:
    void start_accept();
    void handle_accept(TcpConnection::pointer new_connection, const boost::system::error_code& error);
    boost::asio::ip::tcp::acceptor acceptor_;
    boost::asio::io_service &ioService_;
    TcpHandler connectionsManager_;
};

#endif //CPP_RTYPE_2019_TCPSERVER_HPP
