cmake_minimum_required(VERSION 2.8)

project(LinuxSync)

set(SOURCE_LIB CCriticalSection.cpp
               CLockerFactory.cpp
			   CEvent.cpp
			   CMutex.cpp
			   CSemaphore.cpp
                           CThread.cpp
)

add_library(LinuxSync STATIC ${SOURCE_LIB})