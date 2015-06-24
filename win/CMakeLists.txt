cmake_minimum_required(VERSION 2.8)

project(WinSync)

set(SOURCE_LIB CCriticalSection.cpp
                           CLockerFactory.cpp
                           CEvent.cpp
                           CMutex.cpp
                           CSemaphore.cpp
                           CThread.cpp
                           CSocket.cpp
)

add_library(WinSync STATIC ${SOURCE_LIB})