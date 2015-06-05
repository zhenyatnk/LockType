cmake_minimum_required(VERSION 2.8)

project(EmptySync)

set(SOURCE_LIB CEmptySync.cpp
               CLockerFactory.cpp
)

add_library(EmptySync STATIC ${SOURCE_LIB})