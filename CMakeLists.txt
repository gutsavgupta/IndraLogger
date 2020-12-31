# minimum version required for cmake
# check `cmake --version` for ver info
cmake_minimum_required(VERSION 3.5)

# set the project name
project (QLogger)

# add dirs for external libs
add_subdirectory(../GitLibs ./GitLibs)

#find required packages
find_package(Threads)

# -------------------------------------
# qlogger static library
# -------------------------------------
add_library(QLogger_lib INTERFACE
)
add_library(QLogger::lib ALIAS QLogger_lib)

target_include_directories(QLogger_lib
    INTERFACE
        ${PROJECT_SOURCE_DIR}/qlogger
)

target_link_libraries(QLogger_lib
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
        QLogger::lib
        Threads::Threads
)

add_executable(thread_test_print
    test/thread.test.print.cpp
)

target_link_libraries(thread_test_print
    PRIVATE
        QLogger::lib
        Threads::Threads
)

# -------------------------------------
# export build database (ycm)
# -------------------------------------
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
