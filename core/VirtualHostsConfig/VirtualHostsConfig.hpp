//
// Created by guigui on 1/24/20.
//

#ifndef CPP_RTYPE_2019_VIRTUALHOSTSCONFIG_HPP
#define CPP_RTYPE_2019_VIRTUALHOSTSCONFIG_HPP


#include <json/json.h>

class VirtualHostsConfig {
public:
    explicit VirtualHostsConfig(std::string &hostsConfigPath);

private:

    bool checkConfigValidity();

    Json::Value hostsConfig_;
    std::string &hostsConfigPath_;
    bool configValid_;
};


#endif //CPP_RTYPE_2019_VIRTUALHOSTSCONFIG_HPP
