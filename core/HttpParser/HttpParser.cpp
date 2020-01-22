//
// Created by guigui on 1/19/20.
//

#include <vector>
#include <iostream>
#include "HttpParser.hpp"

HttpParser::HttpParser(const std::string &rawData) : rawData_(rawData), initiated_(true) {
    this->parseRawData();
}

const std::string &HttpParser::getRawData() const {
    return rawData_;
}

HttpParser::METHOD HttpParser::getMethod() const {
    return method_;
}

const std::string &HttpParser::getVersion() const {
    return version_;
}

const std::string &HttpParser::getHost() const {
    return host_;
}

const std::string &HttpParser::getConnection() const {
    return connection_;
}

bool HttpParser::isDoNotTrack() const {
    return doNotTrack_;
}

bool HttpParser::isUpgradeInsecureRequest() const {
    return upgradeInsecureRequest_;
}

const std::string &HttpParser::getUserAgent() const {
    return userAgent_;
}

const std::string &HttpParser::getAccept() const {
    return accept_;
}

const std::string &HttpParser::getAcceptEncoding() const {
    return acceptEncoding_;
}

const std::string &HttpParser::getAcceptLanguage() const {
    return acceptLanguage_;
}

void HttpParser::setRawData(const std::string &rawData) {
    rawData_ = rawData;
    this->parseRawData();
    this->initiated_ = true;
}

void HttpParser::parseRawData() {
    std::vector<std::string> requestHeaders;
    boost::split(requestHeaders, this->rawData_, boost::is_any_of("\r\n"));
    bool firstLine = true;
    for (const auto &header: requestHeaders) {
        std::cerr << header << std::endl;
        std::vector<std::string> tmp;
        if (firstLine) {
            boost::split(tmp, header, boost::is_any_of(" "));
            if (tmp.size() == 3) {
                this->method_ = HttpParser::getMethodFromString(tmp[0]);
                this->route_ = tmp[1];
                this->version_ = tmp[2];
                this->valid_ = true;
            }
            firstLine = false;
        } else {
            boost::split(tmp, header, boost::is_any_of(":"));
            std::cerr << tmp[1];
            if (tmp.size() == 2) {
                if (tmp[0] == "Host") this->host_ = tmp[1];
                if (tmp[0] == "Connection") this->host_ = tmp[1];
                if (tmp[0] == "DNT") this->doNotTrack_ = true;
                if (tmp[0] == "Upgrade-Insecure-Requests") this->upgradeInsecureRequest_ = true;
                if (tmp[0] == "User-Agent") this->userAgent_ = tmp[1];
                if (tmp[0] == "Accept") this->accept_ = tmp[1];
                if (tmp[0] == "Accept-Encoding") this->acceptEncoding_ = tmp[1];
                if (tmp[0] == "Accept-Language") this->acceptLanguage_ = tmp[1];
            }
        }
    }
}

HttpParser HttpParser::operator<<(const std::string &rawData) {
    this->setRawData(rawData);
    return *this;
}

bool HttpParser::isInitiated() const {
    return initiated_;
}

HttpParser::METHOD HttpParser::getMethodFromString(std::string methodStr) {
    if (methodStr == "GET")
        return GET;
    if (methodStr == "HEAD")
        return HEAD;
    if (methodStr == "POST")
        return POST;
    if (methodStr == "PUT")
        return PUT;
    if (methodStr == "DELETE")
        return DELETE;
    if (methodStr == "CONNECT")
        return CONNECT;
    if (methodStr == "OPTIONS")
        return OPTIONS;
    if (methodStr == "TRACE")
        return TRACE;
    if (methodStr == "PATCH")
        return PATCH;
    return METHOD_UNDEFINED;
}

bool HttpParser::isValid() const {
    return valid_;
}

const std::string &HttpParser::getContent() const {
    return content_;
}

const std::string &HttpParser::getRoute() const {
    return route_;
}

HttpParser::HttpParser() = default;

HttpParser::~HttpParser() = default;
