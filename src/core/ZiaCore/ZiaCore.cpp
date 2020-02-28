//
// Created by guigui on 1/24/20.
//

#include "ZiaCore.hpp"

ZiaCore::ZiaCore() {
}

void ZiaCore::processParams(int ac, char **av) {

    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
        /// TODO check argument on windows
    #else
        const char *const short_opts = "h:c:k:v";
        const option long_opts[] = {
                {"help", no_argument, nullptr, 'h'},
                {"config", required_argument, nullptr, 'c'},
                {"check", no_argument, nullptr, 'k'},
                {"version", no_argument, nullptr, 'v'},
        };
        while (true) {
            const auto opt = getopt_long(ac, av, short_opts, long_opts, nullptr);
            if (opt == -1)
                break;
            switch (opt) {
                case 'c':
                    this->argsProps_.configPath = std::string(optarg);
                    break;
                case 'k':
                    this->argsProps_.checkOnly = true;
                    break;
                case 'v':
                    this->argsProps_.versionOnly = true;
                    break;
                case 'h': case '?': default:
                    ZiaCore::printHelp();
                    break;
            }
        }
    #endif
}

void ZiaCore::printHelp() {
    std::cout <<
            "--help             Print help" << std::endl <<
            "--config           Precise path for config" << std::endl <<
            "--check            Check config validity only" << std::endl <<
            "--version          Display current zia version" << std::endl;
    exit(0);
}

void ZiaCore::startZia() {
    if (argsProps_.versionOnly)
        ZiaCore::printVersion();
    else {
        serverConfig_ = new ServerConfig(argsProps_.configPath);
        if (!serverConfig_->isConfigValid()) {

        } else {
            moduleManager_ = new ModuleManager(serverConfig_->getModulesEnabledPath());
            virtualHostsConfig_ = new VirtualHostsConfig(serverConfig_->getHostsPath());

        }
        if (serverConfig_->isConfigValid()) {
            if (!argsProps_.checkOnly)
                this->startServer();
        }
    }
}

void ZiaCore::startServer() {
    this->virtualHostManager_ = new VirtualHostManager(this->virtualHostsConfig_);
    this->moduleManager_->handlePreStart(this->serverInstances_);
    this->serverInstances_.push_back({25565, false, "", "", ""});
    for (const auto &instance: this->serverInstances_) {
        std::cout << instance.useTls << " " << instance.port << std::endl;
        //try {
            if (!instance.useTls) {
                /*
                std::cout << "creating server" << std::endl;
                auto newServer = new TcpServer(ioService_, serverConfig_, virtualHostsConfig_, moduleManager_);
                this->serverBlocks_.push_back(newServer);
                 */
            } else {
                std::cout << "creating tls server" << std::endl;
                auto newServer = new TlsTcpServer(ioService_, virtualHostManager_, moduleManager_);
                this->serverBlocks_.push_back(newServer);
            }
            //ziaInstances_.push_back(newInstance);
        /*} catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
            std::cout << "exception happended" << std::endl;
        }*/
    }
    ioService_.run();
}

void ZiaCore::printVersion() {
    std::cout
            << "Zia version " << ZIA_VERSION_STRING << std::endl
            << "Using Boost " << BOOST_VERSION / 100000 << "." << BOOST_VERSION / 100 % 1000 << "." <<BOOST_VERSION % 100 << std::endl
            << "Using JsonCpp " << JSONCPP_VERSION_STRING << std::endl;
}
