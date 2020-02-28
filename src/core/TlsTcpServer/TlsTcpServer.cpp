//
// Created by guigui on 2/2/20.
//

#include "TlsTcpServer.hpp"

TlsTcpServer::TlsTcpServer(boost::asio::io_context &ioService, VirtualHostManager *virtualHostManager,
                           ModuleManager *moduleManager) : io_service_(ioService),
      acceptor_(ioService, {{}, 25567}), context_(boost::asio::ssl::context::sslv23),
      virtualHostManager_(virtualHostManager), moduleManager_(moduleManager) {
    context_.set_password_callback(std::bind(&TlsTcpServer::get_password, this));
    context_.use_certificate_chain_file("./live/pastek.space/cert.pem");
    context_.use_private_key_file("./live/pastek.space/privkey.pem", asio::ssl::context::pem);
    //context_.use_tmp_dh_file("./config/ssl/dh2048.pem");
    start_accept();
}

std::string TlsTcpServer::get_password() {
    return "test";
}

void TlsTcpServer::handle_accept(TlsTcpConnection *connection, const boost::system::error_code &error) {
    if (!error) {
        std::cout << "starting connection";
        connection->start();
        start_accept();
    }
    else
        std::cout << error.message() << std::endl;
}

void TlsTcpServer::start_accept() {
    auto *newSession = new TlsTcpConnection(io_service_, context_, virtualHostManager_, moduleManager_);
    acceptor_.async_accept(newSession->socket(),
        boost::bind(&TlsTcpServer::handle_accept, this, newSession,
          boost::asio::placeholders::error));

}
