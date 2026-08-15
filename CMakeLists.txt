cmake_minimum_required(VERSION 3.23)
project(SpaceDefender)
set(CMAKE_CXX_STANDARD 14)

# Set the executable output location
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

# If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)
## In most cases, it's better to set it in the CMake cache
set(SFML_STATIC_LIBRARIES TRUE)



# Define the compiler for Windows

if(WIN32)
    set(CMAKE_CXX_COMPILER "C:/msys64/mingw64/bin/g++.exe")


endif()




# Set the build type
set(CMAKE_BUILD_TYPE Release)

# Define the directory containing libwinpthread-1.dll on Windows

set(LIBWINPTHREAD_DIR "lib/")


# Copy libwinpthread-1.dll to the executable output directory on Windows

set(CMAKE_CXX_FLAGS "-static-libgcc -static-libstdc++")


# Get the build date and time
string(TIMESTAMP BUILD_TIME "+%Y-%m-%d %H:%M:%S")
message("Build time: ${BUILD_TIME}")
add_definitions(-DBUILD_TIME="${BUILD_TIME}")

# Search for SFML
set(CMAKE_EXE_LINKER_FLAGS "-static")
set(SFML_DIR "lib/cmake/SFML")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mwindows")

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio REQUIRED)

add_executable(SpaceDefender main.cpp src/TDMap/mapParser.hpp src/TDMap/TDMap.hpp src/TDMap/mapParser.cpp src/TDMap/TDMap.cpp src/TDMap/MapCell.hpp src/TDMap/MapCell.cpp src/TDMap/AStarPathFinding.hpp src/TDMap/AStarPathFinding.cpp src/TDUnits/TDUnit.cpp src/TDUnits/TDUnit.hpp src/TDGame/RetrieveLevel.cpp src/TDGame/RetrieveLevel.hpp src/TDGraphics/SFMLLoader.hpp src/TDGraphics/SFMLLoader.cpp src/TDGame/SizeRatioCalculator.cpp src/TDGame/SizeRatioCalculator.hpp src/TDTowers/Tower.cpp src/TDTowers/Tower.hpp src/TDGame/Game.cpp src/TDGame/Game.hpp src/TDGame/usefullStruct.hpp src/TDGame/Buildable.hpp src/TDGame/Buildable.cpp src/TDGraphics/SpritesHolder.cpp src/TDGraphics/SpritesHolder.hpp src/TDGraphics/SFMLSprite.cpp src/TDGraphics/SFMLSprite.hpp src/TDGraphics/SFMLMapReloader.cpp src/TDGraphics/SFMLMapReloader.hpp src/TDUnits/Drone.hpp src/TDUnits/Missile.hpp src/TDGraphics/SFMLEnemiesLoader.cpp src/TDGraphics/SFMLEnemiesLoader.hpp src/TDGraphics/SFMLTowerLoader.cpp src/TDGraphics/SFMLTowerLoader.hpp src/TDTowers/AntiAirTower.hpp src/TDTowers/AntiAirTower.cpp src/TDTowers/AttackSpeedTower.hpp src/TDTowers/AttackSpeedTower.cpp src/TDTowers/BasicTower.cpp src/TDTowers/BasicTower.hpp src/TDGame/AnimationsMaths.cpp src/TDGame/AnimationsMaths.hpp src/TDGraphics/SFMLMissileLoader.cpp src/TDGraphics/SFMLMissileLoader.hpp src/TDTowers/MissileLauncher.cpp src/TDTowers/MissileLauncher.hpp src/TDTowers/MissileThread.cpp src/TDTowers/MissileThread.hpp src/TDGraphics/SFMLCoinAnimation.hpp src/TDGraphics/SFMLCoinAnimation.cpp src/TDGraphics/SFMLHud.cpp src/TDSounds/SFMainSoundLoader.hpp src/TDSounds/SFMainSoundLoader.cpp src/TDSounds/SFMainSoundPlayer.hpp src/TDSounds/SFMainSoundPlayer.cpp src/TDTowers/SlowTower.hpp src/TDTowers/SlowTower.cpp src/TDTowers/SniperTower.hpp src/TDTowers/SniperTower.cpp src/TDTowers/SplashTower.hpp src/TDTowers/SplashTower.cpp src/TDUnits/FlyingDrone.hpp src/TDGraphics/SFMLDecorationLoader.hpp src/TDGraphics/SFMLDecorationLoader.cpp src/TDSounds/SFTowerSoundLoader.hpp src/TDSounds/SFTowerSoundLoader.cpp src/TDUnits/RegenerateDrone.hpp src/TDTowers/SpeedAuraTower.hpp src/TDTowers/SpeedAuraTower.cpp src/TDGame/NetworkController.hpp src/TDGame/NetworkController.cpp src/TDGame/MenusButton.hpp src/TDGame/MenusButton.cpp src/TDGame/Menus.hpp src/TDGame/Menus.cpp src/TDGraphics/SFMLLoaderPlanet1.hpp src/TDGraphics/SFMLLoaderPlanet2.hpp src/TDGraphics/SFMLLoaderPlanet3.hpp src/TDPlayer/TDPlayerSave.hpp src/TDPlayer/TDPlayerSave.cpp)
#AntiAirTower.cpp AntiAirTower.hpp AttackSpeedTower.cpp AttackSpeedTower.hpp SlowTower.cpp SlowTower.hpp SplashTower.cpp SplashTower.hpp SniperTower.cpp SniperTower.hpp

target_link_libraries(SpaceDefender sfml-system sfml-window sfml-graphics sfml-network sfml-audio -static-libgcc -static-libstdc++)



add_custom_command(TARGET SpaceDefender POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/ressources
    $<TARGET_FILE_DIR:SpaceDefender>/ressources)

add_custom_command(TARGET SpaceDefender POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/lib/openal32.dll
    $<TARGET_FILE_DIR:SpaceDefender>/openal32.dll)
