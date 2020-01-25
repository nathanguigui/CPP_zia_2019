cmake_minimum_required(VERSION 3.1.0)

project(CPP_rtype_2019)

add_definitions("-std=c++11")

include(${CMAKE_SOURCE_DIR}/build/conanbuildinfo.cmake)
conan_basic_setup()





###########
# TCP LIB #
###########
set(TCP_SRC
        core/TcpServer/TcpServer.cpp
        core/TcpServer/TcpServer.hpp
        core/TcpConnection/TcpConnection.cpp
        core/TcpConnection/TcpConnection.hpp
        core/TcpHandler/TcpHandler.cpp
        core/TcpHandler/TcpHandler.hpp
)



############
# HTTP LIB #
############
set(HTTP_PARSER_SRC
        core/HttpParser/HttpDeserialyzer.cpp
        core/HttpParser/HttpDeserialyzer.hpp
        core/HttpParser/HttpRequest.hpp
)




##############
# CONFIG LIB #
##############
set(CONFIG_SRC
        core/ServerConfig/ServerConfig.cpp
        core/ServerConfig/ServerConfig.hpp
        core/VirtualHostsConfig/VirtualHostsConfig.cpp core/VirtualHostsConfig/VirtualHostsConfig.hpp)




############
# ZIA CORE #
############
set(CORE_SRC
        core/ZiaCore/ZiaCore.cpp
        core/ZiaCore/ZiaCore.hpp
        core/ZiaCore/ZiaArgs.hpp core/ZiaCore/ZiaVersion.hpp)





if ( MSVC )



    ADD_LIBRARY(TcpZiaLib STATIC ${TCP_SRC})
    TARGET_LINK_LIBRARIES(TcpZiaLib ${CONAN_LIBS})

    ADD_LIBRARY(HttpParserZiaLib STATIC ${HTTP_PARSER_SRC})
    TARGET_LINK_LIBRARIES(HttpParserZiaLib ${CONAN_LIBS})

    ADD_LIBRARY(ConfigZiaLib STATIC ${CONFIG_SRC})
    TARGET_LINK_LIBRARIES(ConfigZiaLib ${CONAN_LIBS})

    ADD_LIBRARY(ZiaCore STATIC ${CORE_SRC})
    TARGET_LINK_LIBRARIES(ZiaCore ${CONAN_LIBS})

    add_executable(zia core/main.cpp)
    target_link_libraries(zia ${CONAN_LIBS} ZiaCore TcpZiaLib HttpParserZiaLib ConfigZiaLib)


    #add_executable(zia ${CORE_SRC} ${CONFIG_SRC} ${HTTP_PARSER_SRC} ${TCP_SRC})
    #target_link_libraries(zia ${CONAN_LIBS})

else( MSVC )

    ADD_LIBRARY(TcpZiaLib SHARED ${TCP_SRC})
    TARGET_LINK_LIBRARIES(TcpZiaLib ${CONAN_LIBS})

    ADD_LIBRARY(HttpParserZiaLib SHARED ${HTTP_PARSER_SRC})
    TARGET_LINK_LIBRARIES(HttpParserZiaLib ${CONAN_LIBS})

    ADD_LIBRARY(ConfigZiaLib SHARED ${CONFIG_SRC})
    TARGET_LINK_LIBRARIES(ConfigZiaLib ${CONAN_LIBS})

    ADD_LIBRARY(ZiaCore SHARED ${CORE_SRC})
    TARGET_LINK_LIBRARIES(ZiaCore ${CONAN_LIBS})

    add_executable(zia core/main.cpp)
    target_link_libraries(zia ${CONAN_LIBS} ZiaCore TcpZiaLib HttpParserZiaLib ConfigZiaLib)

endif( MSVC )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -pipe")

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
