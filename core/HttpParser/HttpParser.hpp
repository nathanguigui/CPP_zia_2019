//
// Created by guigui on 1/19/20.
//

#ifndef CPP_RTYPE_2019_HTTPPARSER_HPP
#define CPP_RTYPE_2019_HTTPPARSER_HPP


#include <string>
#include <boost/algorithm/string.hpp>

class HttpParser {
public:

    enum METHOD {
        GET,
        HEAD,
        POST,
        PUT,
        DELETE,
        CONNECT,
        OPTIONS,
        TRACE,
        PATCH,
        METHOD_UNDEFINED
    };

    explicit HttpParser(const std::string &rawData);

    HttpParser();

    virtual ~HttpParser();

    const std::string &getRawData() const;

    METHOD getMethod() const;

    const std::string &getVersion() const;

    const std::string &getHost() const;

    const std::string &getConnection() const;

    bool isDoNotTrack() const;

    bool isUpgradeInsecureRequest() const;

    const std::string &getUserAgent() const;

    const std::string &getAccept() const;

    const std::string &getAcceptEncoding() const;

    const std::string &getAcceptLanguage() const;

    void setRawData(const std::string &rawData);

    HttpParser operator<<(const std::string &rawData);

    bool isInitiated() const;

    bool isValid() const;

    const std::string &getContent() const;

    const std::string &getRoute() const;

private:

    void parseRawData();

    static METHOD getMethodFromString(std::string);

    std::string rawData_;
    bool initiated_ = false;

    METHOD method_ = METHOD_UNDEFINED;
    std::string version_;
    std::string host_;
    std::string connection_;
    bool doNotTrack_{};
    bool upgradeInsecureRequest_{};
    std::string userAgent_;
    std::string accept_;
    std::string acceptEncoding_;
    std::string acceptLanguage_;
    std::string content_;
    std::string route_;

    bool valid_ = false;
};


#endif //CPP_RTYPE_2019_HTTPPARSER_HPP
