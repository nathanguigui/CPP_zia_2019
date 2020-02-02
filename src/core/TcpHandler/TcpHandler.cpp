//
// Created by guigui on 1/18/20.
//

#include "TcpHandler.hpp"

TcpHandler::TcpHandler() = default;

void TcpHandler::startConnection(const TcpConnection::pointer& connection) {
    connection->start();
    this->connections_.insert(connection);
}

void TcpHandler::stopConnection(const TcpConnection::pointer& connection) {
    this->connections_.erase(connection);
}

void TcpHandler::stopAllConnection() {
    for (const auto &connection: this->connections_)
        this->connections_.erase(connection);
}
