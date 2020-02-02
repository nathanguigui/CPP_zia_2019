//
// Created by guigui on 1/29/20.
//

#ifndef CPP_ZIA_2019_MODULEMANAGER_HPP
#define CPP_ZIA_2019_MODULEMANAGER_HPP

#ifdef WIN32

#else
    #include <dlfcn.h>
#endif

#include <vector>
#include <filesystem>
#include <fstream>
#include <iostream>
#include "ModuleToolbox.hpp"

class ModuleManager {
public:

    explicit ModuleManager(const std::string &modulesPath);

    virtual ~ModuleManager();

    /// Activate hooks called when request came on server
    void handleRequest(HttpRequest &request);

    /// Activate hooks called before response
    void handlePreResponse(HttpRequest &request, HttpResponse &response);


private:

    /// Path to locate modules
    std::string modulesPath_;

    /// List of all modules
    std::vector<ModuleToolbox> modulesList_;

    /// List of all object opened
    std::vector<void *> libObjectList_;
};


#endif //CPP_ZIA_2019_MODULEMANAGER_HPP
