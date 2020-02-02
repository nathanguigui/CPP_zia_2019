//
// Created by guigui on 1/29/20.
//

#ifndef CPP_ZIA_2019_LOGMODULE_HPP
#define CPP_ZIA_2019_LOGMODULE_HPP

#include "zia_modules/includes/IModule/IModule.hpp"
#include <iostream>

class LogModule : public IModule {
public:

    LogModule();

    virtual ~LogModule();

    /// Hook called when request came on server
    void handleRequest(HttpRequest &request) override;

    /// Hook called before response
    void handlePreResponse(HttpRequest &request, HttpResponse &response) override;

    /// Hook called after response
    void handlePostResponse(HttpRequest &request, HttpResponse &response) override;

    /// Hook called before zia create instances
    void handlePreStart(std::vector<ServerInstanceConfig> &instances) override;

private:
};


#endif //CPP_ZIA_2019_LOGMODULE_HPP
