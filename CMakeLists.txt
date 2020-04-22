# minimum version required for cmake
# check `cmake --version` for ver info
cmake_minimum_required(VERSION 3.5)

# set the project name
project (Clogger)

# add dirs for external libs
add_subdirectory(../GitLibs ./GitLibs)

#find required packages
find_package(Threads)

# -------------------------------------
# clogger static library
# -------------------------------------
add_library(Clogger_lib INTERFACE
)
add_library(Clogger::lib ALIAS Clogger_lib)

target_include_directories(Clogger_lib
    INTERFACE
        ${PROJECT_SOURCE_DIR}/clogger
)

target_link_libraries(Clogger_lib
    INTERFACE
        scope_guard::lib
)

# -------------------------------------
# build test target
# -------------------------------------
add_executable(thread_test
    test/thread.test.cpp
)

target_link_libraries(thread_test
    PRIVATE
        Clogger::lib
        Threads::Threads
)

add_executable(thread_test_print
    test/thread.test.print.cpp
)

target_link_libraries(thread_test_print
    PRIVATE
        Clogger::lib
        Threads::Threads
)

# -------------------------------------
# export build database (ycm)
# -------------------------------------
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
