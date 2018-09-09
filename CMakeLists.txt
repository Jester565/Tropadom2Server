cmake_minimum_required ( VERSION 3.1 )
set (T_PROJECT_NAME TropadomServer)

project(${T_PROJECT_NAME})

set(CMAKE_BUILD_TYPE "Release" CACHE STRING "")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_DEBUG} /MT")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_GENERATOR_PLATFORM x64)

find_package(Protobuf REQUIRED)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME ON)
find_package(Boost 1.66.0 COMPONENTS thread regex REQUIRED)


set(allegro false CACHE BOOL "Link to allegro")
if (allegro)
    set(allegincludedir "" CACHE STRING "The directory of allegro includes")
    set(alleglibdir "" CACHE STRING "The directories of allegro's libraries")
    if (UNIX)
        set(alleglib "liballegro.a" CACHE STRING "The path of the main allegro library relative to allegdir")
        set(ttflib "liballegro_ttf.a" CACHE STRING "The path of the ttf allegro extension relative to allegdir")
        set(imglib "liballegro_image.a" CACHE STRING "The path of the img allegro extension relative to allegdir")
        set(primlib "liballegro_primitives.a" CACHE STRING "The path of the primtive allegro extension relative to allegdir")
        set(fontlib "liballegro_font.a" CACHE STRING "The path of the font allegro extension relative to allegdir")
    else()
        set(alleglib "allegro-static.lib" CACHE STRING "The path of the main allegro library relative to allegdir")
        set(ttflib "allegro_ttf-static.lib" CACHE STRING "The path of the ttf allegro extension relative to allegdir")
        set(imglib "allegro_image-static.lib" CACHE STRING "The path of the img allegro extension relative to allegdir")
        set(primlib "allegro_primitives-static.lib" CACHE STRING "The path of the primtive allegro extension relative to allegdir")
        set(fontlib "allegro_font-static.lib" CACHE STRING "The path of the font allegro extension relative to allegdir")
    endif()
endif()

set(allegextbuild true CACHE BOOL "Add AllegroExt as subproject")
set(allegextincludedir "${CMAKE_CURRENT_SOURCE_DIR}/AllegroExt/allegroext" CACHE STRING "Include directory of AllegroExt")
set(allegextlibdir "" CACHE STRING "Directory of AllegroExt")
set(allegextlib "AllegroExt" CACHE STRING "Name of AllegroExt library")

set(asyncserverparentinclude "${CMAKE_CURRENT_SOURCE_DIR}/AsyncCppServer/AsyncServerParent/asyncserverparent" CACHE STRING "Include directory of AsyncServerParent")
set(asyncserverparentlibdir "" CACHE STRING "Directory of AsyncServerParent libraries")
set(asyncserverparentlib "AsyncServerParent" CACHE STRING "Name of AsyncServerParent library")

set(asynccppserverbuild true CACHE BOOL "Add AsyncCppServer as subproject")
set(asynccppserverinclude "${CMAKE_CURRENT_SOURCE_DIR}/AsyncCppServer/asynccppserver" CACHE STRING "Include directory of AsyncCppServer")
set(asynccppserverlibdir "" CACHE STRING "Directory of AsyncCppServer libraries")
set(asynccppserverlib "AsyncCppServer" CACHE STRING "Name of AsyncCppServer library")

set(HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tropadomserver)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(PROTO_DIR ${CMAKE_CURRENT_SOURCE_DIR}/protos)

set(HEADERS
	${HEADER_DIR}/CaveManager.h
    ${HEADER_DIR}/DepositManager.h
    ${HEADER_DIR}/PerlinManager.h
    ${HEADER_DIR}/Pinger.h
    ${HEADER_DIR}/TerrainManager.h
    ${HEADER_DIR}/TropClient.h
    ${HEADER_DIR}/TropClientManager.h
    ${HEADER_DIR}/TropCore.h
    ${HEADER_DIR}/TropServer.h)

set(SOURCES
	${SOURCE_DIR}/CaveManager.cpp
    ${SOURCE_DIR}/DepositManager.cpp
    ${SOURCE_DIR}/PerlinManager.cpp
    ${SOURCE_DIR}/Pinger.cpp
    ${SOURCE_DIR}/Source.cpp
    ${SOURCE_DIR}/TerrainManager.cpp
    ${SOURCE_DIR}/TropClient.cpp
    ${SOURCE_DIR}/TropClientManager.cpp
    ${SOURCE_DIR}/TropCore.cpp
    ${SOURCE_DIR}/TropServer.cpp)

set (PROTOS 
    ${PROTO_DIR}/Trop.proto)

include_directories(
    ${HEADER_DIR})

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${PROTOBUF_INCLUDE_DIRS}
    ${allegincludedir}
    ${allegextincludedir}
    ${asyncserverparentinclude}
    ${asynccppserverinclude})

#Include protobuf pb.cc and pb.h in binary
include_directories(${CMAKE_CURRENT_BINARY_DIR})

#Generate pb.cc and pb.h from proto files
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTOS})

if (allegextbuild)
    add_subdirectory(AllegroExt)
endif()

if (asynccppserverbuild)
    add_subdirectory(AsyncCppServer)
endif()

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES} ${PROTO_HDRS} ${PROTO_SRCS})

target_link_libraries(${PROJECT_NAME} 
    ${Boost_LIBRARIES}
    ${Protobuf_LIBRARIES}
    ${alleglibdir}${alleglib}
    ${alleglibdir}${ttflib}
    ${alleglibdir}${imglib}
    ${alleglibdir}${primlib}
    ${alleglibdir}${fontlib}
    ${allegextlibdir}${allegextlib}
    ${asyncserverparentlibdir}${asyncserverparentlib}
    ${asynccppserverlibdir}${asynccppserverlib})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED 11)

add_custom_command(TARGET ${T_PROJECT_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_CURRENT_SOURCE_DIR}/wdir ${CMAKE_CURRENT_BINARY_DIR})