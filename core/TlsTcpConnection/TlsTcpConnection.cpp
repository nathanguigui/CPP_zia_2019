//
// Created by guigui on 2/2/20.
//

#include "TlsTcpConnection.hpp"

TlsTcpConnection::TlsTcpConnection(asio::ssl::context &context, asio::ip::tcp::socket socket)
    : socket_(std::move(socket), context) {

}

void TlsTcpConnection::start() {
    this->doHandshake();
}

void TlsTcpConnection::doHandshake() {
    auto self(shared_from_this());
    socket_.async_handshake(asio::ssl::stream_base::server, [this, self](const boost::system::error_code &error) {
        if (!error) {
            this->readData();
        }
    });
}

void TlsTcpConnection::readData() {
    // TODO read data
}

void TlsTcpConnection::writeData() {
    // TODO write data
}

void TlsTcpConnection::handle_write(const boost::system::error_code &error, size_t bytes_transferred) {
    // TODO write data
}

void TlsTcpConnection::handle_read(const boost::system::error_code &err, size_t bytes_transferred) {
    // TODO read data
}

TlsTcpConnection::pointer TlsTcpConnection::create(asio::ssl::context &context, asio::ip::tcp::socket socket) {
    //return TlsTcpConnection::pointer(new TlsTcpConnection(context, socket));
}
