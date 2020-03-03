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
                    ss << host["host_root"].asString();
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

void VirtualHostManager::access(HttpRequest &httpRequest, std::string hostname, HttpResponse &httpResponse) {
    auto vhosts = virtualHostsConfig->getHostsConfig();
    try {
        if (virtualHostsConfig->hasHostname(hostname)) {
            for (const auto &host: vhosts) {
                if (host["hostname"].asString() == hostname){
                    try {
                        std::string path = host["host_root"].asString() + httpRequest.uri;
                        #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
                        boost::replace_all(path, "/", "\\");
                        std::cout << path << std::endl;
                        #endif
                        std::ifstream file(path);
                        std::stringstream ss;
                        ss << file.rdbuf() << std::endl;
                        httpResponse.filePath = path;
                        httpResponse.body = ss.str();
                        httpResponse.headers.push_back({"Content-Type", extensionToMime(path.substr(path.find_last_of('.') + 1))});
                        return;
                    } catch (std::exception &e) {
                        continue;
                    }
                }
            }
        }
    } catch (std::exception &e) {
        httpResponse.body = "404 not found.";
    }
    httpResponse.body = "404 not found.";
}
