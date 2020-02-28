//
// Created by guigui on 2/2/20.
//

#ifndef CPP_ZIA_2019_SSLMODULE_HPP
#define CPP_ZIA_2019_SSLMODULE_HPP


#include <src/zia_modules/includes/IModule/IModule.hpp>

class SslModule : public IModule {
public:
    SslModule();

    virtual ~SslModule();

    /// Hook called when request came on server
    void handleRequest(HttpRequest &request) override;

    /// Hook called before response
    void handlePreResponse(HttpRequest &request, HttpResponse &response) override;

    /// Hook called before zia create instances
    void handlePreStart(std::vector<ServerInstanceConfig> &instances) override;

private:

    int port_;

    std::string certificateChainPath_;

    std::string privateKeyPath_;

    std::string tmpDhPath_;

};


#endif //CPP_ZIA_2019_SSLMODULE_HPP
