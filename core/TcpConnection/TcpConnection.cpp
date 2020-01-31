//
// Created by guigui on 1/18/20.
//

#include <iostream>
#include <core/VirtualHostManager/VirtualHostManager.hpp>
#include <core/ModuleManager/ModuleManager.hpp>
#include "TcpConnection.hpp"

std::string convertToString(char* a) {
    int i;
    std::string s = "";
    for (i = 0; a[i]; i++) {
        s = s + a[i];
    }
    return s;
}

TcpConnection::pointer TcpConnection::create(asio::io_service &io_service, VirtualHostManager *vhostsConfig, ModuleManager *moduleManager) {
    return pointer(new TcpConnection(io_service, vhostsConfig, moduleManager));
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
            httpRequest_.valid = true;
            this->moduleManager_->handleRequest(httpRequest_);
            std::string tmp;
            tmp = httpResponseMaker_.makeSuccessResponse(virtualHostsConfig_->access(httpRequest_, socket_.remote_endpoint().address().to_string()), "text/html");
            this->moduleManager_->handlePreResponse(httpRequest_, httpResponse_);
            asio::async_write(socket_, asio::buffer(tmp),
                    boost::bind(&TcpConnection::handle_write, shared_from_this(),
                            asio::placeholders::error,
                            asio::placeholders::bytes_transferred));
            this->moduleManager_->handlePostResponse(httpRequest_, httpResponse_);
        } else if (!result) {
            httpRequest_.valid = false;
            this->moduleManager_->handleRequest(httpRequest_);
            // create response in struct here
            this->moduleManager_->handlePreResponse(httpRequest_, httpResponse_);
            asio::async_write(socket_, asio::buffer(httpResponseMaker_.makeStockResponse(HttpResponseMaker::BAD_REQUEST)),
                    boost::bind(&TcpConnection::handle_write, shared_from_this(),
                            asio::placeholders::error,
                            asio::placeholders::bytes_transferred));
            this->moduleManager_->handlePostResponse(httpRequest_, httpResponse_);
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

TcpConnection::TcpConnection(asio::io_service &io_service, VirtualHostManager *vhostsConfig,
                             ModuleManager *moduleManager) : socket_(io_service), virtualHostsConfig_(vhostsConfig), moduleManager_(moduleManager) {
    this->inputBuffer_ = (char*)malloc(this->maxPacketLen);
}
