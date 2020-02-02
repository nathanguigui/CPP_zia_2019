//
// Created by guigui on 1/26/20.
//

#ifndef CPP_RTYPE_2019_VIRTUALHOSTMANAGER_HPP
#define CPP_RTYPE_2019_VIRTUALHOSTMANAGER_HPP


#include <src/core/VirtualHostsConfig/VirtualHostsConfig.hpp>
#include <src/zia_modules/includes/HttpResponse/HttpResponse.hpp>
#include "src/zia_modules/includes/HttpRequest/HttpRequest.hpp"
#include "src/core/MimeTypes/MimeTypes.hpp"

class VirtualHostManager {
public:
    explicit VirtualHostManager(VirtualHostsConfig *virtualHostsConfig);

    std::string access(HttpRequest &httpRequest, std::string hostname);

    void access(HttpRequest &httpRequest, std::string hostname, HttpResponse &httpResponse);

    VirtualHostsConfig *getVirtualHostsConfig() const;



private:
    VirtualHostsConfig *virtualHostsConfig;
};


#endif //CPP_RTYPE_2019_VIRTUALHOSTMANAGER_HPP
