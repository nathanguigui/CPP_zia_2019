//
// Created by guigui on 1/26/20.
//

#ifndef CPP_RTYPE_2019_VIRTUALHOSTMANAGER_HPP
#define CPP_RTYPE_2019_VIRTUALHOSTMANAGER_HPP


#include <core/VirtualHostsConfig/VirtualHostsConfig.hpp>
#include "zia_modules/includes/HttpRequest/HttpRequest.hpp"

class VirtualHostManager {
public:
    explicit VirtualHostManager(VirtualHostsConfig *virtualHostsConfig);

    std::string access(HttpRequest &httpRequest, std::string hostname);

    VirtualHostsConfig *getVirtualHostsConfig() const;



private:
    VirtualHostsConfig *virtualHostsConfig;
};


#endif //CPP_RTYPE_2019_VIRTUALHOSTMANAGER_HPP
