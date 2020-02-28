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
#include <iostream>
#include "src/core/VirtualHostManager/VirtualHostManager.hpp"
#include "src/core/ModuleManager/ModuleManager.hpp"
#include <src/core/HttpParser/HttpDeserialyzer.hpp>
#include <src/core/HttpResponseMaker/HttpResponseMaker.hpp>

using namespace boost;
typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> ssl_socket;

class TlsTcpConnection {
public:

    TlsTcpConnection(boost::asio::io_service &io_service, boost::asio::ssl::context &context,
                     VirtualHostManager *virtualHostManager, ModuleManager *moduleManager);

    ssl_socket::lowest_layer_type& socket();

    void start();

    void handle_handshake(const boost::system::error_code& error);

    void handle_read(const boost::system::error_code& error, size_t bytes_transferred);

    void handle_write(const boost::system::error_code& error);

private:
    ssl_socket socket_;

    VirtualHostManager *virtualHostManager_;

    ModuleManager *moduleManager_;

    enum { max_length = 8192 };

    char data_[max_length];

    boost::array<char, max_length> buffer_;

    HttpDeserialyzer httpParser_;

    HttpRequest httpRequest_;

    HttpResponse httpResponse_;

    HttpResponseMaker httpResponseMaker_;
};


#endif //CPP_ZIA_2019_TLSTCPCONNECTION_HPP
