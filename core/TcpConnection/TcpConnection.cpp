//
// Created by guigui on 1/18/20.
//

#include <iostream>
#include "TcpConnection.hpp"

TcpConnection::pointer TcpConnection::create(boost::asio::io_service &io_service) {
    return pointer(new TcpConnection(io_service));
}

boost::asio::ip::tcp::socket &TcpConnection::socket() {
    return socket_;
}

void TcpConnection::start() {
    message_ = "it works";
    boost::asio::async_write(socket_, boost::asio::buffer(message_),
            boost::bind(&TcpConnection::handle_write, shared_from_this(), boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred)
    );
}

void TcpConnection::handle_write(const boost::system::error_code &error, size_t bytes_transferred) {
    std::cout << "message sent " << bytes_transferred << std::endl;
}
