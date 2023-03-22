cmake_minimum_required(VERSION 3.23)
project(untitled1)
set(CMAKE_CXX_STANDARD 14)
add_executable(untitled1 main.cpp mapParser.hpp TDMap.hpp mapParser.cpp TDMap.cpp MapCell.hpp MapCell.cpp AStarPathFinding.hpp AStarPathFinding.cpp TDUnit.cpp TDUnit.hpp RetrieveLevel.cpp RetrieveLevel.hpp)
