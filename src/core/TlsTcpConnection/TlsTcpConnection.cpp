//
// Created by guigui on 2/2/20.
//

#include <src/core/VirtualHostManager/VirtualHostManager.hpp>
#include <src/core/ModuleManager/ModuleManager.hpp>
#include "TlsTcpConnection.hpp"

TlsTcpConnection::TlsTcpConnection(boost::asio::io_service &io_service, boost::asio::ssl::context &context,
                                   VirtualHostManager *virtualHostManager, ModuleManager *moduleManager) : socket_(io_service, context) {

}

ssl_socket::lowest_layer_type &TlsTcpConnection::socket() {
    return socket_.lowest_layer();
}

void TlsTcpConnection::start() {
    socket_.async_handshake(boost::asio::ssl::stream_base::server,
        boost::bind(&TlsTcpConnection::handle_handshake, this,
            boost::asio::placeholders::error));
}

void TlsTcpConnection::handle_handshake(const boost::system::error_code &error) {
    if (!error) {
        socket_.async_read_some(boost::asio::buffer(data_, max_length),
            boost::bind(&TlsTcpConnection::handle_read, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    } else
        delete this;
}

void TlsTcpConnection::handle_read(const boost::system::error_code &error, size_t bytes_transferred) {

}

void TlsTcpConnection::handle_write(const boost::system::error_code &error) {

}
