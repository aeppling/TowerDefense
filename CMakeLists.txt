cmake_minimum_required(VERSION 3.23)
project(untitled1)
set(CMAKE_CXX_STANDARD 14)
add_executable(untitled1 main.cpp mapParser.hpp TDMap.hpp mapParser.cpp TDMap.cpp MapCell.hpp MapCell.cpp AStarPathFinding.hpp AStarPathFinding.cpp TDUnit.cpp TDUnit.hpp RetrieveLevel.cpp RetrieveLevel.hpp SFMLLoader.hpp)
## If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)
include_directories(include)
## In most cases better set in the CMake cache
set(SFML_DIR "lib/cmake/SFML")
find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)
target_link_libraries(untitled1 sfml-graphics sfml-audio)