cmake_minimum_required(VERSION 3.1.0)

project(CPP_zia_2019)

add_definitions("-std=c++17")

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

if ( MSVC )

else( MSVC )

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -pipe -ldl -lcrypto -lssl")
endif( MSVC )

ADD_LIBRARY(TcpZiaLib STATIC ${TCP_SRC})
TARGET_LINK_LIBRARIES(TcpZiaLib ${CONAN_LIBS})

ADD_LIBRARY(HttpZiaLib STATIC ${HTTP_SRC})
TARGET_LINK_LIBRARIES(HttpZiaLib ${CONAN_LIBS})

ADD_LIBRARY(ConfigZiaLib STATIC ${CONFIG_SRC})
TARGET_LINK_LIBRARIES(ConfigZiaLib ${CONAN_LIBS})

ADD_LIBRARY(VhostZiaLib STATIC ${VHOST_SRC})
TARGET_LINK_LIBRARIES(VhostZiaLib ${CONAN_LIBS})

ADD_LIBRARY(ZiaCore STATIC ${CORE_SRC})
TARGET_LINK_LIBRARIES(ZiaCore ${CONAN_LIBS})

ADD_LIBRARY(ModulesZiaLib STATIC ${MODULES_LIB})
TARGET_LINK_LIBRARIES(ZiaCore ${CONAN_LIBS})


ADD_LIBRARY(LogModule SHARED ${LOG_MODULE_SRC})
ADD_LIBRARY(SslModule SHARED ${SSL_MODULE_SRC})

add_executable(zia src/core/main.cpp src/core/MimeTypes/MimeTypes.cpp src/core/MimeTypes/MimeTypes.hpp)
target_link_libraries(zia ${CONAN_LIBS} ZiaCore TcpZiaLib HttpZiaLib ConfigZiaLib VhostZiaLib ModulesZiaLib)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

########
# COPY #
########
add_custom_command(TARGET zia
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/build/bin/
        ${CMAKE_BINARY_DIR}/../
        COMMENT "Compilation done, executable copied."
)

add_custom_command(TARGET LogModule
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/build/lib/*.so
        ${CMAKE_BINARY_DIR}/../config/mod-available/
        COMMENT "Modules compiled and copied to default mod-available folder."
        )

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
