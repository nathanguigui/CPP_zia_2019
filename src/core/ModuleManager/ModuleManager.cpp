//
// Created by guigui on 1/29/20.
//

#include "ModuleManager.hpp"

ModuleManager::ModuleManager(const std::string &modulesPath) : modulesPath_(modulesPath) {
    std::cout << "Searching module in path: " << modulesPath << std::endl;
    try {
        for (auto& p: std::filesystem::directory_iterator(modulesPath_)) {
            #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
            if (p.path().string().substr(p.path().string().find_last_of('.') + 1) == "dll") {
            #else
            if (p.path().string().substr(p.path().string().find_last_of('.') + 1) == "so") {
            #endif
                //std::ifstream in(p.path());
                    ModuleToolbox moduleToolbox{};
                    std::cout << "Trying to load module: " << p.path().string().c_str() << std::endl;
                #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
                    // TODO open lib in windows
                    moduleToolbox.libHandle = LoadLibrary(p.path().string().c_str());
                    if (moduleToolbox.libHandle) {
                        moduleToolbox.constructor = (IModule * (*)()) = GetProcAddress(moduleToolbox.libHandle, "createObject");
                        moduleToolbox.destructor = (void (*)(IModule *))GetProcAddress(moduleToolbox.libHandle, "destroyObject");
                        moduleToolbox.module = (IModule *)moduleToolbox.constructor();
                        modulesList_.push_back(moduleToolbox);
                        std::cout << "Found module: " << p.path() << std::endl;
                    }
                #else
                    moduleToolbox.libHandle = dlopen(p.path().string().c_str(), RTLD_LAZY);
                    if (moduleToolbox.libHandle) {
                        moduleToolbox.constructor = (IModule * (*)())dlsym(moduleToolbox.libHandle, "createObject");
                        moduleToolbox.destructor = (void (*)(IModule *))dlsym(moduleToolbox.libHandle, "destroyObject");
                        moduleToolbox.module = (IModule *)moduleToolbox.constructor();
                        modulesList_.push_back(moduleToolbox);
                        std::cout << "Found module: " << p.path() << std::endl;
                    }
                #endif
            }
        }
    } catch (std::exception &e) {
        
    }

}

ModuleManager::~ModuleManager() {
    for (const auto &module: modulesList_) {
        module.destructor(module.module);
        #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)

        #else
            dlclose(module.libHandle);
        #endif
    }
}

void ModuleManager::handleRequest(HttpRequest &request) {
    for (const auto &module: modulesList_)
        module.module->handleRequest(request);
}

void ModuleManager::handlePreResponse(HttpRequest &request, HttpResponse &response) {
    for (const auto &module: modulesList_)
        module.module->handlePreResponse(request, response);
}

void ModuleManager::handlePreStart(std::vector<ServerInstanceConfig> &instances) {
    for (const auto &module: modulesList_)
        module.module->handlePreStart(instances);
}
