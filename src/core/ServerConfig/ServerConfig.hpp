//
// Created by guigui on 1/24/20.
//

#ifndef CPP_RTYPE_2019_SERVERCONFIG_HPP
#define CPP_RTYPE_2019_SERVERCONFIG_HPP
#include <json/json.h>
#include <fstream>

class ServerConfig {
public:
    explicit ServerConfig(std::string &serverConfigPath);

    bool isConfigValid() const;

    const Json::Value &getServerConfig() const;

    int getDefaultHttpPort() const;

    const std::string &getPidPath() const;

    const std::string &getHostsPath() const;

    const std::string &getModulesEnabledPath() const;

private:

    bool checkConfigValidity();

    Json::Value serverConfig_;
    std::string &serverConfigPath_;
    bool configValid_;
    int defaultHttpPort_;
    std::string pidPath_;
    std::string hostsPath_;
    std::string modulesEnabledPath_;
};


#endif //CPP_RTYPE_2019_SERVERCONFIG_HPP
