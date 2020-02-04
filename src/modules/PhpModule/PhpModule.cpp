//
// Created by guigui on 2/3/20.
//

#include <sstream>
#include <iomanip>
#include "PhpModule.hpp"

PhpModule::PhpModule() = default;

PhpModule::~PhpModule() = default;

void PhpModule::handleRequest(HttpRequest &request) {

}

void PhpModule::handlePreResponse(HttpRequest &request, HttpResponse &response) {
    std::string command = "php " + response.filePath;
    response.body = PhpModule::exec(command.c_str());
}

void PhpModule::handlePreStart(std::vector<ServerInstanceConfig> &instances) {

}

std::string PhpModule::exec(const char *cmd) {
    std::array<char, 128> buffer;
    std::string result;
    #if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
        std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd, "r"), _pclose);
    #else
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    #endif
    if (!pipe)
        throw std::runtime_error("popen() failed!");
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
        result += buffer.data();
    return result;

}

extern "C" IModule *createObject() {
    return new PhpModule();
}

extern "C" void destroyObject(IModule *object ) {
    delete dynamic_cast<PhpModule *>(object);
}
