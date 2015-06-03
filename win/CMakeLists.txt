cmake_minimum_required(VERSION 2.8)

project(WinSync)

set(SOURCE_LIB CCriticalSection.cpp
			   CEvent.cpp
			   CMutex.cpp
			   CSemaphore.cpp
)

add_library(WinSync STATIC ${SOURCE_LIB})