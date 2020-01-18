#include <iostream>
#include <boost/version.hpp>
#include <boost/asio.hpp>
#include <json/version.h>
#include <core/TcpServer/TcpServer.hpp>

int main(int argc, char *argv[]) {
    std::cout << "Using Boost " << BOOST_VERSION / 100000 << "." << BOOST_VERSION / 100 % 1000 << "." << BOOST_VERSION % 100 << std::endl;
    std::cout << "Using JsonCpp " << JSONCPP_VERSION_STRING << std::endl;
    try {
        boost::asio::io_service io_service;
        TcpServer server(io_service);
        io_service.run();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}