# vim: tw=1000
cmake_minimum_required(VERSION 2.8.8)
project(Browser)

set(browser_src main.cpp browser.cpp)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wextra")

add_executable(browser ${browser_src})
