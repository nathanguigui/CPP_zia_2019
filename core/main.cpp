#include <iostream>
#include <boost/version.hpp>
//#include <jsoncpp/json/version.h>
#include <json/version.h>

int main(int argc, char *argv[]) {
    std::cout << "Using Boost " << BOOST_VERSION / 100000 << "." << BOOST_VERSION / 100 % 1000 << "." << BOOST_VERSION % 100 << std::endl;
    std::cout << "Using JsonCpp " << JSONCPP_VERSION_STRING << std::endl;
}