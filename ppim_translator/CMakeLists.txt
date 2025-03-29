cmake_minimum_required(VERSION 3.10)
project(ppim_translator)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(ppim_translator
    src/main.cpp
    src/PPIMFrontend.cpp
    src/PPIMBackend.cpp
    src/PPIMPatternMatcher.cpp
    src/PPIMTranslator.cpp
)
