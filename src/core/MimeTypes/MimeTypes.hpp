//
// Created by guigui on 1/31/20.
//

#ifndef CPP_ZIA_2019_MIMETYPES_HPP
#define CPP_ZIA_2019_MIMETYPES_HPP

#include <string>

struct Mime {
    const char *mimeType;
    const char *extension;
};

std::string extensionToMime(const std::string &extension);


#endif //CPP_ZIA_2019_MIMETYPES_HPP
