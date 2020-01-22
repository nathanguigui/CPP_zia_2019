//
// Created by guigui on 1/22/20.
//

#ifndef CPP_RTYPE_2019_HTTPREQUEST_HPP
#define CPP_RTYPE_2019_HTTPREQUEST_HPP

#include <string>
#include <vector>

struct HttpHeader {
    std::string name;
    std::string value;
};

struct HttpRequest {
    std::string method;
    std::string uri;
    int httpMajorVersion;
    int httpMinorVersion;
    std::vector<HttpHeader> headers;
};

#endif //CPP_RTYPE_2019_HTTPREQUEST_HPP
