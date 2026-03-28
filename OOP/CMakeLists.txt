cmake_minimum_required(VERSION 3.10)
project(OOP_Project)

set(CMAKE_CXX_STANDARD 17)

find_package(Threads REQUIRED)

# Add source files
add_executable(main
    main.cpp
    BankAccount.cpp
    BankAccount.h
)

# Include directories
include_directories(${CMAKE_SOURCE_DIR})

target_link_libraries(main Threads::Threads)
