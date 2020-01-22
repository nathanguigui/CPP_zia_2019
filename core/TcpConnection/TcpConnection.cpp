//
// Created by guigui on 1/18/20.
//

#include <iostream>
#include "TcpConnection.hpp"

std::string convertToString(char* a) {
    int i;
    std::string s = "";
    for (i = 0; a[i]; i++) {
        s = s + a[i];
    }
    return s;
}

TcpConnection::pointer TcpConnection::create(asio::io_service &io_service) {
    return pointer(new TcpConnection(io_service));
}

asio::ip::tcp::socket &TcpConnection::socket() {
    return socket_;
}

void TcpConnection::start() {
    socket_.async_read_some(asio::buffer(buffer_),
        boost::bind(&TcpConnection::handle_read, shared_from_this(),
          asio::placeholders::error,
          asio::placeholders::bytes_transferred));

}

void TcpConnection::handle_write(const boost::system::error_code &error, size_t bytes_transferred) {
    if (!error) {
        boost::system::error_code ignored_ec;
        socket_.shutdown(asio::ip::tcp::socket::shutdown_both, ignored_ec);
    } else if (error != boost::asio::error::operation_aborted) {

    }
}

void TcpConnection::handle_read(const boost::system::error_code &err, size_t bytes_transferred) {
    if (!err) {
        boost::tribool result;
        boost::tie(result, boost::tuples::ignore) = httpParser_.parse(httpRequest_, buffer_.data(), buffer_.data() + bytes_transferred);
        if (result) {
            /// API => got a valid request
            //request_handler_.handle_request(request_, reply_);
            /// API => response created
            std::string buf("HTTP/1.0 400 Bad Request\r\nContent-Length: 8\r\nReferrer-Policy: no-referrer\r\nContent-Type: text/html; charset=UTF-8\r\nDate: Wed, 22 Jan 2020 16:46:10 GMT\r\n\r\nit works\r\n");
            boost::array<char, 8192> tmp;
            for (const auto &c : buf)
                tmp.assign(c);
            asio::async_write(socket_, asio::buffer(buf),
                    boost::bind(&TcpConnection::handle_write, shared_from_this(),
                            asio::placeholders::error,
                            asio::placeholders::bytes_transferred));
            /// API => response sent to client
        } else if (!result) {
            std::string buf("HTTP/1.0 400 Bad Request\r\nContent-Length: 8\r\nReferrer-Policy: no-referrer\r\nContent-Type: text/html; charset=UTF-8\r\nDate: Wed, 22 Jan 2020 16:46:00 GMT\r\n\r\nit works\r\n");
            boost::array<char, 8192> tmp;
            for (const auto &c : buf)
                tmp.assign(c);
            asio::async_write(socket_, asio::buffer(tmp),
                    boost::bind(&TcpConnection::handle_write, shared_from_this(),
                            asio::placeholders::error,
                            asio::placeholders::bytes_transferred));
            /// API => got an invalid request
            /*reply_ = reply::stock_reply(reply::bad_request);
            /// API => response created
            asio::async_write(socket_, reply_.to_buffers(),
                boost::bind(&connection::handle_write, shared_from_this(),
                  asio::placeholders::error));*/
            /// API => response sent to client
        } else {
            socket_.async_read_some(asio::buffer(buffer_),
                boost::bind(&TcpConnection::handle_read, shared_from_this(),
                  asio::placeholders::error,
                  asio::placeholders::bytes_transferred));
        }
    } else
        std::cerr << err.message();
}

void TcpConnection::readData() {
    /*this->socket_.async_read_some(
            asio::buffer(inputBuffer_, maxPacketLen),
            boost::bind(&TcpConnection::handle_read,
                        shared_from_this(),
                        asio::placeholders::error,
                        asio::placeholders::bytes_transferred));*/
}

void TcpConnection::writeData() {
    this->socket_.async_write_some(
            asio::buffer(this->outputBuffer_, this->maxPacketLen),
            boost::bind(&TcpConnection::handle_write,
                        shared_from_this(),
                        asio::placeholders::error,
                        asio::placeholders::bytes_transferred));
}

TcpConnection::TcpConnection(asio::io_service &io_service): socket_(io_service) {
    this->inputBuffer_ = (char*)malloc(this->maxPacketLen);
}
