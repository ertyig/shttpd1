cmake_minimum_required(VERSION 3.20)
project(shttpd C)

set(CMAKE_C_STANDARD 99)

add_executable(shttpd shttpd.c shttpd_parameters.c shttpd_worker.c shttpd.h shttpd_cgi.c shttpd_error.c shttpd_request.c shttpd_method.c shttpd_mine.c shttpd_uri.c)
