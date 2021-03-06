cmake_minimum_required(VERSION 3.1.0)

project(CPP_zia_2019)

include(${CMAKE_SOURCE_DIR}/build/conanbuildinfo.cmake)
conan_basic_setup()


###########
# TCP LIB #
###########
set(TCP_SRC
        src/core/TcpServer/TcpServer.cpp
        src/core/TcpServer/TcpServer.hpp
        src/core/TcpConnection/TcpConnection.cpp
        src/core/TcpConnection/TcpConnection.hpp
        src/core/TcpHandler/TcpHandler.cpp
        src/core/TcpHandler/TcpHandler.hpp
        src/core/TlsTcpServer/TlsTcpServer.cpp
        src/core/TlsTcpServer/TlsTcpServer.hpp
        src/core/TlsTcpConnection/TlsTcpConnection.cpp
        src/core/TlsTcpConnection/TlsTcpConnection.hpp
        src/core/ITcpServer/ITcpServer.hpp)

############
# HTTP LIB #
############
set(HTTP_SRC
        src/core/HttpParser/HttpDeserialyzer.cpp
        src/core/HttpParser/HttpDeserialyzer.hpp
        src/core/HttpResponseMaker/HttpResponseMaker.cpp
        src/core/HttpResponseMaker/HttpResponseMaker.hpp)

##############
# CONFIG LIB #
##############
set(CONFIG_SRC
        src/core/ServerConfig/ServerConfig.cpp
        src/core/ServerConfig/ServerConfig.hpp
        src/core/VirtualHostsConfig/VirtualHostsConfig.cpp
        src/core/VirtualHostsConfig/VirtualHostsConfig.hpp
        src/core/VirtualHostManager/VirtualHostManager.cpp
        src/core/VirtualHostManager/VirtualHostManager.hpp)

#############
# VHOST LIB #
#############
set(VHOST_SRC
        src/core/VirtualHostManager/VirtualHostManager.cpp
        src/core/VirtualHostManager/VirtualHostManager.hpp)

###############
# MODULES LIB #
###############
set(MODULES_LIB
        src/core/ModuleManager/ModuleManager.cpp
        src/core/ModuleManager/ModuleManager.hpp
        src/zia_modules/includes/IModule/IModule.hpp)

############
# ZIA CORE #
############
set(CORE_SRC
        src/core/ZiaCore/ZiaCore.cpp
        src/core/ZiaCore/ZiaCore.hpp
        src/core/ZiaCore/ZiaArgs.hpp
        src/core/ZiaCore/ZiaVersion.hpp)


##############
# LOG MODULE #
##############
set(LOG_MODULE_SRC
        src/zia_modules/example/LogModule/LogModule.cpp
        src/zia_modules/example/LogModule/LogModule.hpp
        )

##############
# SSL MODULE #
##############
set(SSL_MODULE_SRC
        src/modules/SslModule/SslModule.cpp src/modules/SslModule/SslModule.hpp)

##############
# PHP MODULE #
##############
set(PHP_MODULE_SRC
        src/modules/PhpModule/PhpModule.cpp
        src/modules/PhpModule/PhpModule.hpp)

if ( MSVC )
    if (MSVC_VERSION GREATER_EQUAL "1900")
        include(CheckCXXCompilerFlag)
        CHECK_CXX_COMPILER_FLAG("/std:c++latest" _cpp_latest_flag_supported)
        if (_cpp_latest_flag_supported)
            add_compile_options("/std:c++latest")
        endif()
    endif()
else( MSVC )
    add_definitions("-std=c++17")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -lstdc++fs -pipe -ldl -lcrypto -lssl")
endif( MSVC )

ADD_LIBRARY(TcpZiaLib STATIC ${TCP_SRC})
TARGET_LINK_LIBRARIES(TcpZiaLib ${CONAN_LIBS})
set_property(TARGET TcpZiaLib PROPERTY CXX_STANDARD 17)

ADD_LIBRARY(HttpZiaLib STATIC ${HTTP_SRC})
TARGET_LINK_LIBRARIES(HttpZiaLib ${CONAN_LIBS})
SET_PROPERTY(TARGET HttpZiaLib PROPERTY CXX_STANDARD 17)

ADD_LIBRARY(ConfigZiaLib STATIC ${CONFIG_SRC})
TARGET_LINK_LIBRARIES(ConfigZiaLib ${CONAN_LIBS})
SET_PROPERTY(TARGET ConfigZiaLib PROPERTY CXX_STANDARD 17)

ADD_LIBRARY(VhostZiaLib STATIC ${VHOST_SRC})
TARGET_LINK_LIBRARIES(VhostZiaLib ${CONAN_LIBS})
SET_PROPERTY(TARGET VhostZiaLib PROPERTY CXX_STANDARD 17)

ADD_LIBRARY(ZiaCore STATIC ${CORE_SRC})
TARGET_LINK_LIBRARIES(ZiaCore ${CONAN_LIBS})
SET_PROPERTY(TARGET ZiaCore PROPERTY CXX_STANDARD 17)

ADD_LIBRARY(ModulesZiaLib STATIC ${MODULES_LIB})
TARGET_LINK_LIBRARIES(ZiaCore ${CONAN_LIBS})
SET_PROPERTY(TARGET ZiaCore PROPERTY CXX_STANDARD 17)


ADD_LIBRARY(LogModule SHARED ${LOG_MODULE_SRC})
SET_PROPERTY(TARGET LogModule PROPERTY CXX_STANDARD 17)
ADD_LIBRARY(SslModule SHARED ${SSL_MODULE_SRC})
SET_PROPERTY(TARGET SslModule PROPERTY CXX_STANDARD 17)
ADD_LIBRARY(PhpModule SHARED ${PHP_MODULE_SRC})
SET_PROPERTY(TARGET PhpModule PROPERTY CXX_STANDARD 17)

add_executable(zia src/core/main.cpp src/core/MimeTypes/MimeTypes.cpp src/core/MimeTypes/MimeTypes.hpp)
target_link_libraries(zia ${CONAN_LIBS} ZiaCore TcpZiaLib HttpZiaLib ConfigZiaLib VhostZiaLib ModulesZiaLib)
SET_PROPERTY(TARGET zia PROPERTY CXX_STANDARD 17)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

########
# COPY #
########

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

    add_custom_target(CopyModules ALL
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/build/lib/*.dylib
            ${CMAKE_BINARY_DIR}/../config/mod-available/
            COMMENT "Modules compiled and copied to default mod-available folder."
            )
    
    add_custom_command(TARGET zia
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/build/bin/zia
            ${CMAKE_BINARY_DIR}/../
            COMMENT "Compilation done, executable copied."
        )

else (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

if ( MSVC )
    add_custom_target(CopyModules ALL
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/build/bin/PhpModule.dll
            ${CMAKE_BINARY_DIR}/../config/mod-available/
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/build/bin/LogModule.dll
            ${CMAKE_BINARY_DIR}/../config/mod-available/
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/build/bin/SslModule.dll
            ${CMAKE_BINARY_DIR}/../config/mod-available/
            COMMENT "Modules compiled and copied to default mod-available folder."
            )
    
    add_custom_command(TARGET zia
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/build/bin/zia.exe
            ${CMAKE_BINARY_DIR}/../
            COMMENT "Compilation done, executable copied."
        )
else ( MSVC )
    add_custom_target(CopyModules ALL
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/build/lib/*.so
            ${CMAKE_BINARY_DIR}/../config/mod-available/
            COMMENT "Modules compiled and copied to default mod-available folder."
            )
    
    add_custom_command(TARGET zia
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/build/bin/zia
            ${CMAKE_BINARY_DIR}/../
            COMMENT "Compilation done, executable copied."
        )
endif ( MSVC )

endif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin") 


add_dependencies(CopyModules LogModule PhpModule SslModule)

message("

,gggggggg,          ,a8a,           ,ggg,  
d8P\"\"\"\"\"\"Y8b,       ,8\" \"8,         dP\"\"8I  
88,_a     `8b       d8   8b        dP   88  
`Y8P\"      88       88   88       dP    88  
           88       88   88      ,8'    88  
          d8'       Y8   8P      d88888888  
       _,d8'        `8, ,8'__   ,8\"     88  
     d8888ba,  8888  \"8,8\"dP\"  ,8P      Y8  
         \"Y88b,`8b,  ,d8b,Yb,_,dP       `8b,
         ,d8888  \"Y88P\" \"Y8\"Y8P\"         `Y8
       ,8P\"  88                             
      d8'    88                             
     d8'    ,88                             
     88     d8'                             
     Y8,_ _,8P                              
      \"Y888P\"                               
                            
")
