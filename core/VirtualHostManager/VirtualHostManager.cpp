//
// Created by guigui on 1/26/20.
//

#include "VirtualHostManager.hpp"

VirtualHostManager::VirtualHostManager(VirtualHostsConfig *virtualHostsConfig) : virtualHostsConfig(
        virtualHostsConfig) {}

VirtualHostsConfig *VirtualHostManager::getVirtualHostsConfig() const {
    return virtualHostsConfig;
}

std::string VirtualHostManager::access(HttpRequest &httpRequest) {
    auto vhosts = virtualHostsConfig->getHostsConfig();
    //if (virtualHostsConfig->hasHostname("localhost")) {
        for (const auto &host: vhosts) {
            try {
                std::string path = host["host_root"].asString() + httpRequest.uri;
                std::ifstream file(path);
                std::stringstream ss;
                ss << file.rdbuf();
                return ss.str();
            } catch (std::exception &e) {
                continue;
            }
        }
    //}
    throw std::exception();
}
