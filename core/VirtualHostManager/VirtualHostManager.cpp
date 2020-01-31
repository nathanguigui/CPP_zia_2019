//
// Created by guigui on 1/26/20.
//

#include "VirtualHostManager.hpp"

VirtualHostManager::VirtualHostManager(VirtualHostsConfig *virtualHostsConfig) : virtualHostsConfig(
        virtualHostsConfig) {}

VirtualHostsConfig *VirtualHostManager::getVirtualHostsConfig() const {
    return virtualHostsConfig;
}

std::string VirtualHostManager::access(HttpRequest &httpRequest, std::string hostname) {
    auto vhosts = virtualHostsConfig->getHostsConfig();
    try {
        if (virtualHostsConfig->hasHostname(hostname)) {
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
        }
    } catch (std::exception &e) {
        return ("404 not found.");
    }
    return ("404 not found.");
}
