//
// Created by guigui on 2/2/20.
//

#ifndef CPP_ZIA_2019_SERVERINSTANCECONFIG_HPP
#define CPP_ZIA_2019_SERVERINSTANCECONFIG_HPP

struct ServerInstanceConfig {
    int port;
    bool useTls;
    std::string certificateChainPath;
    std::string privateKeyPath;
    std::string tmpDhPath;
};

#endif //CPP_ZIA_2019_SERVERINSTANCECONFIG_HPP
