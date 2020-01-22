//
// Created by guigui on 1/18/20.
//

#include "TcpServer.hpp"

TcpServer::TcpServer(boost::asio::io_service &io_service) : acceptor_(io_service, {{}, 25565}), ioService_(io_service) {
    start_accept();
}

void TcpServer::start_accept() {
    TcpConnection::pointer new_connection = TcpConnection::create(ioService_);

    acceptor_.async_accept(new_connection->socket(),
        boost::bind(&TcpServer::handle_accept, this, new_connection,
          boost::asio::placeholders::error));
}

void TcpServer::handle_accept(TcpConnection::pointer new_connection, const boost::system::error_code &error) {
    if (!error) {
        this->connectionsManager_.startConnection(new_connection);
        start_accept();
    }
}
