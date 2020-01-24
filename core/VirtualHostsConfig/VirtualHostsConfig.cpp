//
// Created by guigui on 1/24/20.
//

#include "VirtualHostsConfig.hpp"

VirtualHostsConfig::VirtualHostsConfig(std::string &hostsConfigPath) : hostsConfigPath_(hostsConfigPath), configValid_(false) {}

bool VirtualHostsConfig::checkConfigValidity() {
    return configValid_;
}
