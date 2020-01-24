//
// Created by guigui on 1/24/20.
//

#ifndef CPP_RTYPE_2019_ZIACORE_HPP
#define CPP_RTYPE_2019_ZIACORE_HPP

#include <boost/asio.hpp>
#include <boost/version.hpp>
#include <json/version.h>
#include "core/TcpServer/TcpServer.hpp"
#include "core/ServerConfig.hpp"
#include "ZiaArgs.hpp"

class ZiaCore {
public:

    ZiaCore();

    static void printHelp();

    void processParams(int ac, char **av);

    void startZia();

private:
    void startServer();
    static void printVersion();
    TcpServer *httpServer_{};
    boost::asio::io_service ioService_;
    ServerConfig *serverConfig_;
    ZiaArgs argsProps_{"", false, false};
    //TcpServer sslServer_;
};


#endif //CPP_RTYPE_2019_ZIACORE_HPP
