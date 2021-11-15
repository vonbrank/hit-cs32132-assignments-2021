cmake_minimum_required(VERSION 3.20)
project(graph_traversal)

set(CMAKE_CXX_STANDARD 14)

add_executable(graph_traversal main.cpp Graph.cpp Graph.h)
