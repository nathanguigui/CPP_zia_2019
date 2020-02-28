//
// Created by guigui on 1/24/20.
//

#include <iostream>
#include "ServerConfig.hpp"

ServerConfig::ServerConfig(std::string &serverConfigPath) : serverConfigPath_(serverConfigPath), configValid_(false) {
    try {
        std::ifstream in(serverConfigPath);
        in >> this->serverConfig_;
        this->checkConfigValidity();
    } catch (Json::RuntimeError &e) {
        std::cout << "Config file not found." << std::endl;
        std::cout << "Using default values." << std::endl;
        defaultHttpPort_ = 25565;
        useDefaultConfig_ = true;
    }

}

bool ServerConfig::isConfigValid() const {
    return configValid_;
}

bool ServerConfig::checkConfigValidity() {
    int score = 0;
    if (serverConfig_["default_http_port"].isNumeric())
        defaultHttpPort_ = serverConfig_["default_http_port"].asInt(); score++;
    if (serverConfig_["pid"].isString())
        pidPath_ = serverConfig_["pid"].asString(); score++;
    if (serverConfig_["hosts"].isString())
        hostsPath_ = serverConfig_["hosts"].asString(); score++;
    if (serverConfig_["modules_enabled"].isString())
        modulesEnabledPath_ = serverConfig_["modules_enabled"].asString(); score++;
    if (score == 4)
        std::cout << "Server config valid." << std::endl; configValid_ = true;
    if (!configValid_)
        std::cout << "Server config invalid." << std::endl;
    return configValid_;
}

const Json::Value &ServerConfig::getServerConfig() const {
    return serverConfig_;
}

int ServerConfig::getDefaultHttpPort() const {
    return defaultHttpPort_;
}

const std::string &ServerConfig::getPidPath() const {
    return pidPath_;
}

const std::string &ServerConfig::getHostsPath() const {
    return hostsPath_;
}

const std::string &ServerConfig::getModulesEnabledPath() const {
    return modulesEnabledPath_;
}

bool ServerConfig::isUseDefaultConfig() const {
    return useDefaultConfig_;
}
