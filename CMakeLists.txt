cmake_minimum_required(VERSION 3.23)
project(untitled1)
set(CMAKE_CXX_STANDARD 14)
## If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)
## In most cases better set in the CMake cache
set(SFML_STATIC_LIBRARIES TRUE)
set(CMAKE_BUILD_TYPE Release)
set(SFML_DIR "lib/cmake/SFML")
#set(GLEW_STATIC TRUE)
#set(GLEW_INCLUDE_DIR "include/")
#find_package(GLEW REQUIRED)
#set(GLEW_LIBRARIES "lib/")
include_directories(include)
find_package(SFML 2.5.1 COMPONENTS system window graphics network audio REQUIRED)
add_executable(untitled1 main.cpp src/TDMap/mapParser.hpp src/TDMap/TDMap.hpp src/TDMap/mapParser.cpp src/TDMap/TDMap.cpp src/TDMap/MapCell.hpp src/TDMap/MapCell.cpp src/TDMap/AStarPathFinding.hpp src/TDMap/AStarPathFinding.cpp src/TDUnits/TDUnit.cpp src/TDUnits/TDUnit.hpp src/TDGame/RetrieveLevel.cpp src/TDGame/RetrieveLevel.hpp src/TDGraphics/SFMLLoader.hpp src/TDGraphics/SFMLLoader.cpp src/TDGame/SizeRatioCalculator.cpp src/TDGame/SizeRatioCalculator.hpp src/TDTowers/Tower.cpp src/TDTowers/Tower.hpp src/TDGame/Game.cpp src/TDGame/Game.hpp src/TDGame/usefullStruct.hpp src/TDGame/Buildable.hpp src/TDGame/Buildable.cpp src/TDGraphics/SpritesHolder.cpp src/TDGraphics/SpritesHolder.hpp src/TDGraphics/SFMLSprite.cpp src/TDGraphics/SFMLSprite.hpp src/TDGraphics/SFMLMapReloader.cpp src/TDGraphics/SFMLMapReloader.hpp src/TDUnits/Drone.hpp src/TDUnits/Missile.hpp src/TDGraphics/SFMLEnemiesLoader.cpp src/TDGraphics/SFMLEnemiesLoader.hpp src/TDGraphics/SFMLTowerLoader.cpp src/TDGraphics/SFMLTowerLoader.hpp src/TDTowers/AntiAirTower.hpp src/TDTowers/AntiAirTower.cpp src/TDTowers/AttackSpeedTower.hpp src/TDTowers/AttackSpeedTower.cpp)
#AntiAirTower.cpp AntiAirTower.hpp AttackSpeedTower.cpp AttackSpeedTower.hpp SlowTower.cpp SlowTower.hpp SplashTower.cpp SplashTower.hpp SniperTower.cpp SniperTower.hpp
target_link_libraries(untitled1 sfml-system sfml-window sfml-graphics sfml-network sfml-audio)