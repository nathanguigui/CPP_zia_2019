//
// Created by guigui on 1/30/20.
//

#ifndef CPP_ZIA_2019_MODULETOOLBOX_HPP
#define CPP_ZIA_2019_MODULETOOLBOX_HPP

#include "zia_modules/includes/IModule/IModule.hpp"

struct ModuleToolbox {
    IModule *module;
    void *libHandle;
    IModule *(*constructor)();
    void (*destructor)(IModule*);
};

#endif //CPP_ZIA_2019_MODULETOOLBOX_HPP
