//
// Created by guigui on 1/29/20.
//

#ifndef CPP_RTYPE_2019_HTTPRESPONSE_HPP
#define CPP_RTYPE_2019_HTTPRESPONSE_HPP

#include "../HttpHeader/HttpHeader.hpp"
#include <string>
#include <vector>

struct HttpResponse {
    int httpMajorVersion;
    int httpMinorVersion;
    int responseCode;
    std::string responseMessage;
    std::vector<HttpHeader> headers;
    std::string body;
};
#endif //CPP_RTYPE_2019_HTTPRESPONSE_HPP
