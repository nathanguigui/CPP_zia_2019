//
// Created by guigui on 1/24/20.
//

#ifndef CPP_RTYPE_2019_ZIACORE_HPP
#define CPP_RTYPE_2019_ZIACORE_HPP

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)

#else
    #include <getopt.h>
#endif
#include <boost/asio.hpp>
#include <boost/version.hpp>
#include <json/version.h>
#include "src/core/TcpServer/TcpServer.hpp"
#include "src/core/ServerConfig/ServerConfig.hpp"
#include "src/core/VirtualHostsConfig/VirtualHostsConfig.hpp"
#include "src/core/ModuleManager/ModuleManager.hpp"
#include "ZiaArgs.hpp"
#include "ZiaInstances.hpp"
#include <iostream>
#include <src/core/ServerConfig/ServerConfig.hpp>
#include <src/core/TlsTcpServer/TlsTcpServer.hpp>
#include "ZiaVersion.hpp"

class ZiaCore {
public:

    ZiaCore();

    static void printHelp();

    void processParams(int ac, char **av);

    void startZia();

private:

    void startServer();

    static void printVersion();

    boost::asio::io_service ioService_;

    ServerConfig *serverConfig_;

    VirtualHostsConfig *virtualHostsConfig_;

    ModuleManager *moduleManager_;

    ZiaArgs argsProps_{"./config/server.json", false, false};

    std::vector<ServerInstanceConfig> serverInstances_;

    std::vector<ITcpServer*> serverBlocks_;

    VirtualHostManager *virtualHostManager_;

    //TcpServer sslServer_;
};


#endif //CPP_RTYPE_2019_ZIACORE_HPP
