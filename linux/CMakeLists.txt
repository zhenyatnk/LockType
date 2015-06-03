cmake_minimum_required(VERSION 2.8)

project(LinuxSync)

set(SOURCE_LIB CCriticalSection.cpp
			   CEvent.cpp
			   CMutex.cpp
			   CSemaphore.cpp
)

add_library(LinuxSync STATIC ${SOURCE_LIB})