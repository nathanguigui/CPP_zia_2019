//
// Created by guigui on 2/3/20.
//

#ifndef CPP_ZIA_2019_PHPMODULE_HPP
#define CPP_ZIA_2019_PHPMODULE_HPP

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)

#else
    #include <cstdio>
#endif

#include "zia_modules/includes/IModule/IModule.hpp"
#include <array>
#include <memory>

class PhpModule : public IModule {

public:
    PhpModule();

    virtual ~PhpModule();

    /// Hook called when request came on server
    void handleRequest(HttpRequest &request) override;

    /// Hook called before response
    void handlePreResponse(HttpRequest &request, HttpResponse &response) override;

    /// Hook called before zia create instances
    void handlePreStart(std::vector<ServerInstanceConfig> &instances) override;

    static std::string exec(const char *cmd);

};


#endif //CPP_ZIA_2019_PHPMODULE_HPP
