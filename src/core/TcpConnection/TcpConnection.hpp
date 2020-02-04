//
// Created by guigui on 1/18/20.
//

#ifndef CPP_RTYPE_2019_TCPCONNECTION_HPP
#define CPP_RTYPE_2019_TCPCONNECTION_HPP
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <src/core/HttpParser/HttpDeserialyzer.hpp>
#include "zia_modules/includes/HttpRequest/HttpRequest.hpp"
#include <src/core/HttpResponseMaker/HttpResponseMaker.hpp>
#include <src/core/VirtualHostsConfig/VirtualHostsConfig.hpp>
#include <src/core/VirtualHostManager/VirtualHostManager.hpp>
#include "src/core/ModuleManager/ModuleManager.hpp"

using namespace boost;

class TcpConnection: public boost::enable_shared_from_this<TcpConnection> {
public:
    typedef boost::shared_ptr<TcpConnection> pointer;

    TcpConnection(asio::io_service &io_service, VirtualHostManager *vhostsConfig,
                           ModuleManager *moduleManager);

    static pointer create(asio::io_service &io_service, VirtualHostManager *vhostsConfig, ModuleManager *moduleManager);

    boost::asio::ip::tcp::socket& socket();

    void start();

private:


    void readData();

    void writeData();

    void handle_write(const boost::system::error_code &error, size_t bytes_transferred);

    void handle_read(const boost::system::error_code &err, size_t bytes_transferred);

    VirtualHostManager *virtualHostsConfig_;

    boost::asio::ip::tcp::socket socket_;

    std::string outputBuffer_;

    char *inputBuffer_;

    int maxPacketLen = 8192;

    boost::array<char, 8192> buffer_;

    HttpDeserialyzer httpParser_;

    HttpRequest httpRequest_;

    HttpResponse httpResponse_;

    HttpResponseMaker httpResponseMaker_;

    ModuleManager *moduleManager_;

    asio::streambuf request_;
};


#endif //CPP_RTYPE_2019_TCPCONNECTION_HPP
