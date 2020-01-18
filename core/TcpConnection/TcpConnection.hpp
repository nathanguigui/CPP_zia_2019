//
// Created by guigui on 1/18/20.
//

#ifndef CPP_RTYPE_2019_TCPCONNECTION_HPP
#define CPP_RTYPE_2019_TCPCONNECTION_HPP
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>


class TcpConnection: public boost::enable_shared_from_this<TcpConnection> {
public:
    typedef boost::shared_ptr<TcpConnection> pointer;

    static pointer create(boost::asio::io_service& io_service);

    boost::asio::ip::tcp::socket& socket();

    void start();

private:

    explicit TcpConnection(boost::asio::io_service& io_service): socket_(io_service) {

    }

    void handle_write(const boost::system::error_code& error, size_t bytes_transferred);

    boost::asio::ip::tcp::socket socket_;
    std::string message_;
};


#endif //CPP_RTYPE_2019_TCPCONNECTION_HPP
