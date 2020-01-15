cmake_minimum_required(VERSION 3.1.0)

project(CPP_rtype_2019)

add_definitions("-std=c++11")

include(${CMAKE_SOURCE_DIR}/build/conanbuildinfo.cmake)
conan_basic_setup()

if ( MSVC )
    #windows
endif( MSVC )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -pipe -j4 -lboost")

#include_directories(
#    ${CMAKE_CURRENT_BINARY_DIR}
#    ${CMAKE_CURRENT_SOURCE_DIR}
#)

set(CORE_SRC
    core/main.cpp
)

add_executable(zia ${CORE_SRC})
target_link_libraries(zia ${CONAN_LIBS})

message("

,gggggggg,          ,a8a,           ,ggg,  
d8P""""""Y8b,       ,8" "8,         dP""8I  
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