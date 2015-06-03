cmake_minimum_required(VERSION 2.8)

project(LockType)

set(SOURCE_EXE test_sync.cpp)
add_executable(LockType ${SOURCE_EXE})

add_subdirectory(win)

target_link_libraries(LockType WinSync)