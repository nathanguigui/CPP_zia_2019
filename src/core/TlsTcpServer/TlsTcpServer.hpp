//
// Created by guigui on 2/2/20.
//

#ifndef CPP_ZIA_2019_TLSTCPSERVER_HPP
#define CPP_ZIA_2019_TLSTCPSERVER_HPP

#include "src/core/ITcpServer/ITcpServer.hpp"
#include "src/core/TlsTcpConnection/TlsTcpConnection.hpp"
#include <src/core/VirtualHostManager/VirtualHostManager.hpp>
#include <src/core/ModuleManager/ModuleManager.hpp>

class TlsTcpServer : public ITcpServer {
public:
    TlsTcpServer(boost::asio::io_context &ioService, VirtualHostManager *virtualHostManager,
                 ModuleManager *moduleManager);

    void handle_accept(TlsTcpConnection *connection, const boost::system::error_code& error);

    std::string get_password();

    void start_accept() override;

private:

    boost::asio::io_service& io_service_;

    boost::asio::ip::tcp::acceptor acceptor_;

    boost::asio::ssl::context context_;

    VirtualHostManager *virtualHostManager_;

    ModuleManager *moduleManager_;

};


#endif //CPP_ZIA_2019_TLSTCPSERVER_HPP
