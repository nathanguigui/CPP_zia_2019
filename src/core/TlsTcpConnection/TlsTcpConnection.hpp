//
// Created by guigui on 2/2/20.
//

#ifndef CPP_ZIA_2019_TLSTCPCONNECTION_HPP
#define CPP_ZIA_2019_TLSTCPCONNECTION_HPP

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <boost/asio/ssl.hpp>

using namespace boost;

class TlsTcpConnection: public boost::enable_shared_from_this<TlsTcpConnection> {
public:

    typedef boost::shared_ptr<TlsTcpConnection> pointer;

    TlsTcpConnection(boost::asio::ssl::context &context, boost::asio::ip::tcp::socket socket);

    //static pointer create(asio::ssl::context &context, asio::ip::tcp::socket socket);

    void start();

private:

    void doHandshake();

    void readData();

    void writeData();

    void handle_write(const boost::system::error_code &error, size_t bytes_transferred);

    void handle_read(const boost::system::error_code &err, size_t bytes_transferred);

    asio::ssl::stream<asio::ip::tcp::socket> socket_;

};


#endif //CPP_ZIA_2019_TLSTCPCONNECTION_HPP
