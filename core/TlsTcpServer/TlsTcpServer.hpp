//
// Created by guigui on 2/2/20.
//

#ifndef CPP_ZIA_2019_TLSTCPSERVER_HPP
#define CPP_ZIA_2019_TLSTCPSERVER_HPP

#include "core/ITcpServer/ITcpServer.hpp"
#include "core/TlsTcpConnection/TlsTcpConnection.hpp"

class TlsTcpServer : public ITcpServer {
public:
    TlsTcpServer(boost::asio::io_context &ioContext, VirtualHostManager *virtualHostManager,
                 ModuleManager *moduleManager);

    void start_accept();

    std::string get_password();

private:
    boost::asio::ip::tcp::acceptor acceptor_;

    boost::asio::ssl::context context_;

    VirtualHostManager *virtualHostManager_;

    ModuleManager *moduleManager_;

};


#endif //CPP_ZIA_2019_TLSTCPSERVER_HPP
