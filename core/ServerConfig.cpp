//
// Created by guigui on 1/24/20.
//

#include <iostream>
#include "ServerConfig.hpp"

ServerConfig::ServerConfig(std::string &serverConfigPath) : serverConfigPath_(serverConfigPath), configValid_(false) {
    std::ifstream in(serverConfigPath);
    in >> this->serverConfig_;
    this->checkConfigValidity();
}

bool ServerConfig::isConfigValid() const {
    return configValid_;
}

void ServerConfig::checkConfigValidity() {
    if (serverConfig_["default_http_port"].isNumeric() && serverConfig_["pid"].isString()
    && serverConfig_["hosts"].isString()) {
            configValid_ = true;
            std::cout << "Server config valid." << std::endl;
    } if (!configValid_)
        std::cout << "Server config invalid." << std::endl;
}