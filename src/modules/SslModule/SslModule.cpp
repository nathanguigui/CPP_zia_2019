//
// Created by guigui on 2/2/20.
//

#include "SslModule.hpp"

SslModule::SslModule() : port_(1999), certificateChainPath_("test"), privateKeyPath_("test"), tmpDhPath_("test") {
}

SslModule::~SslModule() = default;

void SslModule::handleRequest(HttpRequest &request) {

}

void SslModule::handlePreResponse(HttpRequest &request, HttpResponse &response) {

}

void SslModule::handlePreStart(std::vector<ServerInstanceConfig> &instances) {
    ServerInstanceConfig myTls;
    myTls.port = port_;
    myTls.useTls = true;
    myTls.certificateChainPath = certificateChainPath_;
    myTls.privateKeyPath = privateKeyPath_;
    myTls.tmpDhPath = tmpDhPath_;
    instances.push_back(myTls);
}

extern "C" IModule *createObject() {
    return new SslModule();
}

extern "C" void destroyObject(IModule *object ) {
    delete dynamic_cast<SslModule *>(object);
}