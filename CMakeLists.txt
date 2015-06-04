cmake_minimum_required(VERSION 2.8)

project(LockType)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_EXE test_sync.cpp)
add_executable(LockType ${SOURCE_EXE})

IF(WIN32)
   add_subdirectory(win)
   target_link_libraries(LockType WinSync)
ELSE(LINUX)
   add_definitions(-DLINUX)
   add_subdirectory(linux)
   target_link_libraries(LockType LinuxSync pthread)
ENDIF()