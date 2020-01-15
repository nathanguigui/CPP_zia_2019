#include <iostream>
#include <boost/version.hpp>
//#include <jsoncpp/json/version.h>

int main(int argc, char *argv[]) {
    std::cout << "Using Boost "     
          << BOOST_VERSION / 100000     << "."  // major version
          << BOOST_VERSION / 100 % 1000 << "."  // minor version
          << BOOST_VERSION % 100                // patch level
          << std::endl;
    //std::cout << "Using JsonCpp " << JSONCPP_VERSION_STRING
}