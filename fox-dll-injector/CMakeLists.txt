cmake_minimum_required (VERSION 3.8)
project ("fox-dll-injector")

add_library(dll-main SHARED dllmain.cpp)


include_directories(include)
add_executable (fox-dll-injector "main.cpp"  "include/fox/fox-process.hpp" "include/fox/fox-injector.hpp" "dllmain.cpp")

# Require administrative access
SET_TARGET_PROPERTIES(fox-dll-injector PROPERTIES LINK_FLAGS    "/MANIFESTUAC:\"level='requireAdministrator' uiAccess='false'\" /SUBSYSTEM:CONSOLE")
