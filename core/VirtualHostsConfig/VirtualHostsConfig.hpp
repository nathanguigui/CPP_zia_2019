//
// Created by guigui on 1/24/20.
//

#ifndef CPP_RTYPE_2019_VIRTUALHOSTSCONFIG_HPP
#define CPP_RTYPE_2019_VIRTUALHOSTSCONFIG_HPP


#include <json/json.h>
#include <iostream>
#include <filesystem>
#include <fstream>

class VirtualHostsConfig {
public:

    explicit VirtualHostsConfig(std::string path);

private:

    void config(Json::Value &newHost);

    static void update(Json::Value &currentHosts, Json::Value &newHost);

    bool checkConfigValidity();

    std::vector<Json::Value> hostsConfig_;
    std::string &hostsConfigPath_;
    bool configValid_;
    int fileCount_;
};


#endif //CPP_RTYPE_2019_VIRTUALHOSTSCONFIG_HPP
