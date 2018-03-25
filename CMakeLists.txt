cmake_minimum_required (VERSION 3.4)
project (Shiny-cppclient-sdk)

# Version
set (Version_major 0)
set (Version_minor 0)
set (Version_patch 1)

configure_file("${PROJECT_SOURCE_DIR}/src/shiny-version.h.in" "${PROJECT_BINARY_DIR}/include/shiny-version.h")
list(APPEND include_dirs "${PROJECT_BINARY_DIR}/include")

# Socket.io
if(NOT SIO_DIR)
    message("Set SIO_DIR to find socket.io C++ Client.")
    return()
endif()

list(APPEND include_dirs "${SIO_DIR}/build/include")
list(APPEND link_dirs "${SIO_DIR}/build/lib/Release")

# RapidJSON
# 在Socket.io里面有，所以直接用了。
list(APPEND include_dirs "${SIO_DIR}/lib/rapidjson/include")

# SSL
option(ENABLE_SSL "Enable SSL for websocket link like https://" OFF)

if (NOT ENABLE_SSL)
    list(APPEND extra_libs "sioclient")
else()
    list(APPEND extra_libs "sioclient_tls")
    find_package(OpenSSL)
    list(APPEND extra_libs ${OPENSSL_LIBRARIES})
endif()

# Boost
find_package(Boost REQUIRED COMPONENTS system date_time random)
list(APPEND include_dirs ${Boost_INCLUDE_DIRS})
list(APPEND link_dirs ${Boost_LIBRARY_DIRS})
list(APPEND extra_libs ${Boost_LIBRARIES})

# Compile and link
link_directories(${link_dirs})
aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src ALL_SRC) # find srcs
file(GLOB ALL_HEADERS ${CMAKE_CURRENT_LIST_DIR}/src/*.h) # find .h files
add_library(shiny_cpp_client_sdk ${ALL_SRC} ${ALL_HEADERS})
target_include_directories(shiny_cpp_client_sdk PRIVATE ${include_dirs})
target_link_libraries(shiny_cpp_client_sdk PRIVATE ${extra_libs})

# add test
add_executable(shiny_cpp_test test.cpp)
target_include_directories(shiny_cpp_test PRIVATE ${include_dirs}
    "${CMAKE_CURRENT_LIST_DIR}/src"
)
target_link_libraries(shiny_cpp_test PRIVATE ${extra_libs}
    shiny_cpp_client_sdk
)

# install
install (TARGETS shiny_cpp_client_sdk DESTINATION "${CMAKE_CURRENT_LIST_DIR}/bin")
install (FILES ${ALL_HEADERS} "${PROJECT_BINARY_DIR}/include/shiny-version.h" DESTINATION "${CMAKE_CURRENT_LIST_DIR}/include")