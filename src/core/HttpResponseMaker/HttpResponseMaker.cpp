//
// Created by guigui on 1/26/20.
//

#include "HttpResponseMaker.hpp"

HttpResponseMaker::HttpResponseMaker(): httpMajorVersion_(1), httpMinorVersion_(0) {}

std::string HttpResponseMaker::makeSuccessResponse(std::string content, std::string mime) {
    std::stringstream ss;
    ss << "HTTP/" << httpMajorVersion_ << "." << httpMinorVersion_ << " 200 OK\r\n";
    ss << "Content-Length: " << content.size() << "\r\n";
    ss << "Content-Type: " << mime << "\r\n";
    this->setHeaders(ss);
    ss << "\r\n" << content << "\r\n";
    return ss.str();
}

std::string HttpResponseMaker::makeStockResponse(HttpResponseMaker::ResponseCode code) {
    std::stringstream ss;
    ss << "HTTP/" << httpMajorVersion_ << "." << httpMinorVersion_ << " " << code << " ";
    this->addMessageFromCode(ss, code);
    this->setHeaders(ss);
    ss << "Content-Type: text/html\r\n\r\n";
    this->addMessageFromCode(ss, code);
    return ss.str();
}

void HttpResponseMaker::addHeader(std::string name, std::string value) {
    this->headers_.push_back({name, value});
}

void HttpResponseMaker::clearHeaders() {
    this->headers_.clear();
}

void HttpResponseMaker::setContentType(const std::string &contentType) {
    contentType_ = contentType;
}

void HttpResponseMaker::setHeaders(std::stringstream &ss) {
    for (const auto &header: this->headers_)
        ss << header.name << ": " << header.value << "\r\n";
}

void HttpResponseMaker::addMessageFromCode(std::stringstream &ss, HttpResponseMaker::ResponseCode code) {
    switch (code) {
        case SUCCESS:
            ss << "OK\r\n";
            break;
        case REDIRECT_PERMANENT:
            break;
        case REDIRECT_TEMP:
            break;
        case BAD_REQUEST:
            ss << "Bad Request\r\n";
            break;
        case USER_NOT_AUTH:
            break;
        case ACCESS_DENIED:
            break;
        case NOT_FOUND:
            ss << "Not Found\r\n";
            break;
        case SERVER_ERROR:
            ss << "Service Unavailable\r\n";
            break;
    }
}

std::string HttpResponseMaker::serializeHttpResponse(HttpResponse response) {
    std::stringstream ss;
    ss << "HTTP/" << response.httpMajorVersion << "." << response.httpMinorVersion << " " << response.responseCode << " " << response.responseMessage <<"\r\n";
    ss << "Content-Length: " << (response.body.size() > 65535 ? 65535 : response.body.size()) << "\r\n";
    HttpResponseMaker::setHeaders(ss, response);
    ss << "\r\n" << response.body << "\r\n";
    return ss.str();
}

void HttpResponseMaker::setHeaders(std::stringstream &ss, HttpResponse &httpResponse) {
    for (const auto &header: httpResponse.headers)
        ss << header.name << ": " << header.value << "\r\n";
}

void HttpResponseMaker::addMessageFromCode(HttpResponse &httpResponse, HttpResponseMaker::ResponseCode responseCode) {
    httpResponse.responseCode = responseCode;
    switch (responseCode) {
        case SUCCESS:
            httpResponse.responseMessage = "OK";
            break;
        case REDIRECT_PERMANENT:
            break;
        case REDIRECT_TEMP:
            break;
        case BAD_REQUEST:
            httpResponse.responseMessage = "Bad Request";
            break;
        case USER_NOT_AUTH:
            break;
        case ACCESS_DENIED:
            break;
        case NOT_FOUND:
            httpResponse.responseMessage = "Not Found";
            break;
        case SERVER_ERROR:
            httpResponse.responseMessage = "Service Unavailable";
            break;
    }
}
