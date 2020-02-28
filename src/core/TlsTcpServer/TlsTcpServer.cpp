//
// Created by guigui on 2/2/20.
//

#include "TlsTcpServer.hpp"

TlsTcpServer::TlsTcpServer(boost::asio::io_context &ioService, VirtualHostManager *virtualHostManager,
                           ModuleManager *moduleManager) : io_service_(ioService),
      acceptor_(ioService, {{}, 25567}), context_(boost::asio::ssl::context::sslv23),
      virtualHostManager_(virtualHostManager), moduleManager_(moduleManager) {
    context_.set_password_callback(std::bind(&TlsTcpServer::get_password, this));
    context_.use_certificate_chain_file("./config/ssl/user.crt");
    context_.use_private_key_file("./config/ssl/user.key", asio::ssl::context::pem);
    context_.use_tmp_dh_file("./config/ssl/dh2048.pem");
    auto *newSession = new TlsTcpConnection(io_service_, context_, virtualHostManager_, moduleManager_);
    acceptor_.async_accept(newSession->socket(),
        boost::bind(&TlsTcpServer::handle_accept, this, newSession,
        boost::asio::placeholders::error));
}

std::string TlsTcpServer::get_password() {
    return "test";
}

void TlsTcpServer::handle_accept(TlsTcpConnection *connection, const boost::system::error_code &error) {
    if (!error) {
        connection->start();
        acceptor_.async_accept(connection->socket(),
            boost::bind(&TlsTcpServer::handle_accept, this, connection,
            boost::asio::placeholders::error));
    }/*else
        delete connection;*/
}

void TlsTcpServer::start_accept() {

}
