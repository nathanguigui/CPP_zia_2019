//
// Created by guigui on 1/22/20.
//

#ifndef CPP_RTYPE_2019_HTTPDESERIALYZER_HPP
#define CPP_RTYPE_2019_HTTPDESERIALYZER_HPP
#include <boost/logic/tribool.hpp>
#include <boost/tuple/tuple.hpp>

struct HttpRequest;

class HttpDeserialyzer {
public:

    HttpDeserialyzer();

    void reset();

    template <typename InputIterator>boost::tuple<boost::tribool, InputIterator> parse(HttpRequest &req, InputIterator begin, InputIterator end) {
        while (begin != end) {
            boost::tribool result = this->consume(req, *begin++);
            if (result || !result)
                return boost::make_tuple(result, begin);
        }
        boost::tribool result = boost::indeterminate;
        return boost::make_tuple(result, begin);
    }

private:

    boost::tribool consume(HttpRequest &req, char input);

    static bool isChar(int c);

    static bool isCtl(int c);

    static bool isTspecial(int c);

    static bool isDigit(int c);

    enum state {
        MethodStart,
        Method,
        Uri,
        HttpVersionH,
        HttpVersionT1,
        HttpVersionT2,
        HttpVersionP,
        HttpVersionSlash,
        HttpVersionMajorStart,
        HttpVersionMajor,
        HttpVersionMinorStart,
        HttpVersionMinor,
        ExpectingNewline1,
        HeaderLineStart,
        HeaderLws,
        HeaderName,
        SpaceBeforeHeaderValue,
        HeaderValue,
        ExpectingNewline2,
        ExpectingNewline3
    } state_;
};

#endif //CPP_RTYPE_2019_HTTPDESERIALYZER_HPP
