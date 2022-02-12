# global config
cmake_minimum_required(VERSION 3.16)
project(imgui_window_test)

set(CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)

set(vendorPath "${PROJECT_SOURCE_DIR}/vendor")

find_package(Threads REQUIRED)
find_package(Vulkan REQUIRED)

add_subdirectory(vendor)
add_subdirectory(Lib)
#add_subdirectory(tests)
add_subdirectory(Example)
