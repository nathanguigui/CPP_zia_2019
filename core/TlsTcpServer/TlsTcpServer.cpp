//
// Created by guigui on 2/2/20.
//

#include <core/VirtualHostManager/VirtualHostManager.hpp>
#include <core/ModuleManager/ModuleManager.hpp>
#include "TlsTcpServer.hpp"

TlsTcpServer::TlsTcpServer(boost::asio::io_context &ioContext, VirtualHostManager *virtualHostManager,
                           ModuleManager *moduleManager)
        : acceptor_(ioContext, {{}, 2020}), context_(boost::asio::ssl::context::sslv23),
        moduleManager_(moduleManager), virtualHostManager_(virtualHostManager) {
    context_.set_options(
            asio::ssl::context::default_workarounds |
            asio::ssl::context::no_sslv2 |
            asio::ssl::context::single_dh_use);
    context_.set_password_callback(std::bind(&TlsTcpServer::get_password, this));
    context_.use_certificate_chain_file("./config/ssl/user.crt");
    context_.use_private_key_file("./config/ssl/user.key", asio::ssl::context::pem);
    context_.use_tmp_dh_file("./config/ssl/dh2048.pem");
    start_accept();
}

void TlsTcpServer::start_accept() {
    acceptor_.async_accept([this](const boost::system::error_code &error, asio::ip::tcp::socket socket) {
        if (!error) {
            std::make_shared<TlsTcpConnection>(context_, std::move(socket))->start();
        }
        start_accept();
    });
}

std::string TlsTcpServer::get_password() {
    return "test";
}
