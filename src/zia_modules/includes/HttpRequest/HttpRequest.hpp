//
// Created by guigui on 1/29/20.
//

#ifndef CPP_RTYPE_2019_HTTPREQUEST_HPP
#define CPP_RTYPE_2019_HTTPREQUEST_HPP

#include <string>
#include <vector>
#include "zia_modules/includes/HttpHeader/HttpHeader.hpp"

struct HttpRequest {
    std::string method;
    std::string uri;
    int httpMajorVersion;
    int httpMinorVersion;
    bool valid;
    std::vector<HttpHeader> headers;
};

#endif //CPP_RTYPE_2019_HTTPREQUEST_HPP
