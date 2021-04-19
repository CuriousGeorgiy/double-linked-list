cmake_minimum_required(VERSION 3.17)
project(doubly-linked-list)

set(CMAKE_CXX_STANDARD 11)

add_executable(DoublyLinkedArrayList)
target_sources(DoublyLinkedArrayList PUBLIC DoublyLinkedArrayListMain.cpp)
target_include_directories(DoublyLinkedArrayList PUBLIC ${PROJECT_SOURCE_DIR})

add_executable(DoublyLinkedPointerList)
target_sources(DoublyLinkedPointerList PUBLIC DoublyLinkedPointerListMain.cpp)
target_include_directories(DoublyLinkedPointerList PUBLIC ${PROJECT_SOURCE_DIR})

