//
// Created by guigui on 1/31/20.
//

#include "MimeTypes.hpp"

std::string extensionToMime(const std::string &extension) {
    for (Mime *m = mimeMappings; m->extension; ++m) {
        if (m->extension == extension)
            return m->mimeType;
    }
    return "text/plain";
}