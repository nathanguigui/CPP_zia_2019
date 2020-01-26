//
// Created by guigui on 1/26/20.
//

#ifndef CPP_RTYPE_2019_HTTPRESPONSEMAKER_HPP
#define CPP_RTYPE_2019_HTTPRESPONSEMAKER_HPP

#include "core/HttpParser/HttpRequest.hpp"
#include <vector>
#include <sstream>

class HttpResponseMaker {
public:

    enum ResponseCode {
        SUCCESS = 200,
        REDIRECT_PERMANENT = 301,
        REDIRECT_TEMP = 302,
        BAD_REQUEST = 400,
        USER_NOT_AUTH = 401,
        ACCESS_DENIED = 403,
        NOT_FOUND = 404,
        SERVER_ERROR = 500,
    };

    HttpResponseMaker();

    std::string makeSuccessResponse(std::string content, std::string mime);

    std::string makeStockResponse(HttpResponseMaker::ResponseCode code);

    void setContentType(const std::string &contentType);

    void addHeader(std::string name, std::string value);

    void clearHeaders();

private:

    void setHeaders(std::stringstream &ss);

    void addMessageFromCode(std::stringstream &ss, HttpResponseMaker::ResponseCode code);

    int httpMajorVersion_;
    int httpMinorVersion_;
    std::vector<HttpHeader> headers_;
    std::string contentType_;
};


#endif //CPP_RTYPE_2019_HTTPRESPONSEMAKER_HPP
