//
// Created by guigui on 2/2/20.
//

#include <src/core/VirtualHostManager/VirtualHostManager.hpp>
#include <src/core/ModuleManager/ModuleManager.hpp>
#include <boost/logic/tribool.hpp>
#include <boost/tuple/tuple.hpp>
#include <src/core/HttpResponseMaker/HttpResponseMaker.hpp>
#include "TlsTcpConnection.hpp"

TlsTcpConnection::TlsTcpConnection(boost::asio::io_service &io_service, boost::asio::ssl::context &context,
    VirtualHostManager *virtualHostManager, ModuleManager *moduleManager)
        : socket_(io_service, context), virtualHostManager_(virtualHostManager), moduleManager_(moduleManager) {

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
    if (!error) {
        boost::tribool result;
        boost::tie(result, boost::tuples::ignore) = httpParser_.parse(httpRequest_, buffer_.data(), buffer_.data() + bytes_transferred);
        if (result) {
            httpRequest_.valid = true;
            this->moduleManager_->handleRequest(httpRequest_);
            httpResponse_.httpMajorVersion = 1;
            httpResponse_.httpMinorVersion = 0;
            HttpResponseMaker::addMessageFromCode(httpResponse_, HttpResponseMaker::SUCCESS);
            this->virtualHostManager_->access(httpRequest_, this->socket().remote_endpoint().address().to_string(), httpResponse_);
            this->moduleManager_->handlePreResponse(httpRequest_, httpResponse_);
            if (httpResponse_.body.empty()) {
                asio::async_write(socket_, asio::buffer(httpResponseMaker_.makeStockResponse(HttpResponseMaker::NOT_FOUND)),
                    boost::bind(&TlsTcpConnection::handle_write, this,
                            asio::placeholders::error));
            } else {
                asio::async_write(socket_, asio::buffer(HttpResponseMaker::serializeHttpResponse(httpResponse_)),
                    boost::bind(&TlsTcpConnection::handle_write, this,
                            asio::placeholders::error));
            }
        } else if (!result) {
            httpRequest_.valid = false;
            this->moduleManager_->handleRequest(httpRequest_);
            // create response in struct here
            this->moduleManager_->handlePreResponse(httpRequest_, httpResponse_);
            asio::async_write(socket_, asio::buffer(httpResponseMaker_.makeStockResponse(HttpResponseMaker::BAD_REQUEST)),
                    boost::bind(&TlsTcpConnection::handle_write, this,
                            asio::placeholders::error));
        } else {
            socket_.async_read_some(asio::buffer(buffer_),
                boost::bind(&TlsTcpConnection::handle_read, this,
                  asio::placeholders::error,
                  asio::placeholders::bytes_transferred));
        }
    } else
        std::cerr << error.message();
}

void TlsTcpConnection::handle_write(const boost::system::error_code &error) {

}
