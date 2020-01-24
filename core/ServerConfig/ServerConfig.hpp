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

private:

    bool checkConfigValidity();

    Json::Value serverConfig_;
    std::string &serverConfigPath_;
    bool configValid_;
};


#endif //CPP_RTYPE_2019_SERVERCONFIG_HPP
