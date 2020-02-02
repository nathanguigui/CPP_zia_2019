//
// Created by guigui on 1/22/20.
//

#include "HttpDeserialyzer.hpp"
#include "src/zia_modules/includes/HttpRequest/HttpRequest.hpp"

HttpDeserialyzer::HttpDeserialyzer(): state_(MethodStart) {}

void HttpDeserialyzer::reset() {
    this->state_ = MethodStart;
}

boost::tribool HttpDeserialyzer::consume(HttpRequest &req, char input) {
    switch (state_) {
        case MethodStart:
            if (!isChar(input) || isCtl(input) || isTspecial(input))
                return false;
            else {
                state_ = Method;
                req.method.push_back(input);
                return boost::indeterminate;
            }
        case Method:
            if (input == ' ') {
                state_ = Uri;
                return boost::indeterminate;
            }
            else if (!isChar(input) || isCtl(input) || isTspecial(input))
                return false;
            else {
                req.method.push_back(input);
                return boost::indeterminate;
            }
        case Uri:
            if (input == ' ') {
                state_ = HttpVersionH;
                return boost::indeterminate;
            } else if (isCtl(input))
                return false;
            else {
                req.uri.push_back(input);
                return boost::indeterminate;
            }
        case HttpVersionH:
            if (input == 'H') {
                state_ = HttpVersionT1;
                return boost::indeterminate;
            } else
                return false;
        case HttpVersionT1:
            if (input == 'T') {
                state_ = HttpVersionT2;
                return boost::indeterminate;
            } else
                return false;
        case HttpVersionT2:
            if (input == 'T') {
                state_ = HttpVersionP;
                return boost::indeterminate;
            } else
                return false;
        case HttpVersionP:
            if (input == 'P') {
                state_ = HttpVersionSlash;
                return boost::indeterminate;
            } else
                return false;
        case HttpVersionSlash:
            if (input == '/') {
                req.httpMajorVersion = 0;
                req.httpMinorVersion = 0;
                state_ = HttpVersionMajorStart;
                return boost::indeterminate;
            } else
                return false;
        case HttpVersionMajorStart:
            if (isDigit(input)) {
                req.httpMajorVersion = req.httpMajorVersion * 10 + input - '0';
                state_ = HttpVersionMajor;
                return boost::indeterminate;
            } else
                return false;
        case HttpVersionMajor:
            if (input == '.') {
                state_ = HttpVersionMinorStart;
                return boost::indeterminate;
            } else if (isDigit(input)) {
                req.httpMajorVersion = req.httpMajorVersion * 10 + input - '0';
                return boost::indeterminate;
            } else
                return false;
        case HttpVersionMinorStart:
            if (isDigit(input)) {
                req.httpMinorVersion = req.httpMinorVersion * 10 + input - '0';
                state_ = HttpVersionMinor;
                return boost::indeterminate;
            } else
                return false;
        case HttpVersionMinor:
            if (input == '\r') {
                state_ = ExpectingNewline1;
                return boost::indeterminate;
            } else if (isDigit(input)) {
                req.httpMinorVersion = req.httpMinorVersion * 10 + input - '0';
                return boost::indeterminate;
            } else
                return false;
        case ExpectingNewline1:
            if (input == '\n') {
                state_ = HeaderLineStart;
                return boost::indeterminate;
            } else
                return false;
        case HeaderLineStart:
            if (input == '\r') {
                state_ = ExpectingNewline3;
                return boost::indeterminate;
            } else if (!req.headers.empty() && (input == ' ' || input == '\t')) {
                state_ = HeaderLws;
                return boost::indeterminate;
            } else if (!isChar(input) || isCtl(input) || isTspecial(input))
                return false;
            else {
                req.headers.push_back(HttpHeader());
                req.headers.back().name.push_back(input);
                state_ = HeaderName;
                return boost::indeterminate;
            }
        case HeaderLws:
            if (input == '\r') {
                state_ = ExpectingNewline2;
                return boost::indeterminate;
            } else if (input == ' ' || input == '\t')
                return boost::indeterminate;
            else if (isCtl(input))
                return false;
            else {
                state_ = HeaderValue;
                req.headers.back().value.push_back(input);
                return boost::indeterminate;
            }
        case HeaderName:
            if (input == ':') {
                state_ = SpaceBeforeHeaderValue;
                return boost::indeterminate;
            } else if (!isChar(input) || isCtl(input) || isTspecial(input))
                return false;
            else {
                req.headers.back().name.push_back(input);
                return boost::indeterminate;
            }
        case SpaceBeforeHeaderValue:
            if (input == ' ') {
                state_ = HeaderValue;
                return boost::indeterminate;
            } else
                return false;
        case HeaderValue:
            if (input == '\r') {
                state_ = ExpectingNewline2;
                return boost::indeterminate;
            } else if (isCtl(input))
                return false;
            else {
                req.headers.back().value.push_back(input);
                return boost::indeterminate;
            }
        case ExpectingNewline2:
            if (input == '\n') {
                state_ = HeaderLineStart;
                return boost::indeterminate;
            } else
                return false;
        case ExpectingNewline3:
            return (input == '\n');
        default:
            return false;
  }
}

bool HttpDeserialyzer::isChar(int c) {
    return c >= 0 && c <= 127;
}

bool HttpDeserialyzer::isCtl(int c) {
    return (c >= 0 && c <= 31) || (c == 127);
}

bool HttpDeserialyzer::isTspecial(int c) {
    switch (c) {
        case '(': case ')': case '<': case '>': case '@':
        case ',': case ';': case ':': case '\\': case '"':
        case '/': case '[': case ']': case '?': case '=':
        case '{': case '}': case ' ': case '\t':
            return true;
        default:
            return false;
    }
}

bool HttpDeserialyzer::isDigit(int c) {
    return c >= '0' && c <= '9';
}
