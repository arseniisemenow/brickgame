cmake_minimum_required (VERSION 3.8)

project("CURL-DEMO")


set(SOURCES
        "main.c"
        "retrieve_data.c"
        "retrieve_data.h"
        "cjson.c"
        "cjson.h"
)

include_directories(${CURL_INCLUDE_DIR})

add_executable(CURL-DEMO ${SOURCES})

include(FindPkgConfig)
pkg_check_modules(CURL libcurl REQUIRED)
include_directories(
        SYSTEM ${CURL_INCLUDE_DIRS}
)
target_link_libraries(CURL-DEMO
        ${CURL_LIBRARIES}
)


if(LIBCURL_ENABLE)
    target_link_libraries(CURL-DEMO CURL::libcurl)
endif()