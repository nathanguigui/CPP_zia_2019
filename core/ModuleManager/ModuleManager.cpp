//
// Created by guigui on 1/29/20.
//

#include "ModuleManager.hpp"

ModuleManager::ModuleManager(const std::string &modulesPath) : modulesPath_(modulesPath) {
    for (auto& p: std::filesystem::directory_iterator(modulesPath_)) {
        if (p.path().string().substr(p.path().string().find_last_of('.') + 1) == "so") {
            //std::ifstream in(p.path());
            std::cout << p.path() << std::endl;
        }
    }
}

ModuleManager::~ModuleManager() = default;

void ModuleManager::handleRequest(HttpRequest &request) {
    for (const auto &module: modulesList_)
        module->handleRequest(request);
}

void ModuleManager::handlePreResponse(HttpRequest &request, HttpResponse &response) {
    for (const auto &module: modulesList_)
        module->handlePreResponse(request, response);
}

void ModuleManager::handlePostResponse(HttpRequest &request, HttpResponse &response) {
    for (const auto &module: modulesList_)
        module->handlePostResponse(request, response);
}
