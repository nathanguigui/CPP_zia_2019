//
// Created by guigui on 1/24/20.
//

#include "VirtualHostsConfig.hpp"

VirtualHostsConfig::VirtualHostsConfig(std::string path) : hostsConfigPath_(path), configValid_(false), fileCount_(0) {
    fileCount_ = 0;
    std::cout << "Searching virtual hosts in path: " << path << std::endl;
    for (auto& p: std::filesystem::directory_iterator(hostsConfigPath_)) {
        if (p.path().string().substr(p.path().string().find_last_of('.') + 1) == "json") {
            std::cout << "Found virtual host config: " << p.path() << std::endl;
            std::ifstream in(p.path());
            Json::Value tmp;
            in >> tmp;
            this->config(tmp);
            fileCount_++;
        }
    }
    this->checkConfigValidity();
}

bool VirtualHostsConfig::checkConfigValidity() {
    //std::cout << this->hostsConfig_.toStyledString();
    for (const auto &host: this->hostsConfig_)
        std::cout << "Serving: " << host["host_root"].asString() << " for hostname: " << host["hostname"].asString() << std::endl;
    return configValid_;
}

void VirtualHostsConfig::update(Json::Value &currentHosts, Json::Value &newHost) {
    if (!currentHosts.isObject() || !newHost.isObject()) return;

    for (const auto& key : newHost.getMemberNames()) {
        if (currentHosts[key].isObject())
            update(currentHosts[key], newHost[key]);
        else
            currentHosts[key] = newHost[key];
    }
}

void VirtualHostsConfig::config(Json::Value &newHost) {
    if (newHost["hosts"].isArray())
        for (Json::Value::ArrayIndex i = 0; i < newHost["hosts"].size(); i++)
            if (newHost["hosts"][i].isObject())
                if (newHost["hosts"][i]["host_root"].isString())
                    this->hostsConfig_.push_back(newHost["hosts"][i]);
}

const std::vector<Json::Value> &VirtualHostsConfig::getHostsConfig() const {
    return hostsConfig_;
}

bool VirtualHostsConfig::hasHostname(const std::string& hostname) {
    for (const auto &host: hostsConfig_) {
        if (host["hostname"].isString()) {
            if (hostname.find(host["hostname"].asString()) != std::string::npos)
                return true;
        }
    }
    return false;
}
