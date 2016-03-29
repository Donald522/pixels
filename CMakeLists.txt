cmake_minimum_required (VERSION 2.8)

project (pixels)

#DEBUG by default
if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_DEBUG_POSTFIX "_d")

set(EXECUTABLE_NAME "pixels")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -coverage -std=c++11 -O3")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

IF (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_LINUX")
ENDIF (${CMAKE_SYSTEM_NAME} MATCHES "Linux")

include_directories(${PROJECT_SOURCE_DIR}/include/)
include_directories(deps/pugixml/src)



#set(SRC_LIST src/app/Application.cpp)

#file(GLOB SOURCES src/*.cpp)
SET(SOURCES
src/world/World.cpp
src/music/MusicPlayer.cpp
src/music/SoundPlayer.cpp
src/util/Utility.cpp
src/animation/Animation.cpp
src/nodes/TextNode.cpp
src/nodes/SceneNode.cpp
src/nodes/EmitterNode.cpp
src/nodes/SoundNode.cpp
src/nodes/SpriteNode.cpp
src/nodes/ParticleNode.cpp
src/app/Application.cpp
src/entity/Pickup.cpp
src/entity/BossCreature.cpp
src/entity/Projectile.cpp
src/entity/Entity.cpp
src/entity/Creature.cpp
src/gui/Container.cpp
src/gui/Component.cpp
src/gui/Label.cpp
src/gui/Button.cpp
src/states/StateStack.cpp
src/states/PauseState.cpp
src/states/MenuState.cpp
src/states/State.cpp
src/states/LoadingState.cpp
src/states/GameOverState.cpp
src/states/LevelSelectState.cpp
src/states/TitleState.cpp
src/states/SettingsState.cpp
src/states/GameState.cpp
src/resource/DataTables.cpp
src/log/Log.cpp
src/system/SceneGrid.cpp
src/system/CommandQueue.cpp
src/system/Command.cpp
src/effects/PixelateEffect.cpp
src/effects/PostEffect.cpp
src/effects/BloomEffect.cpp
src/player/Player.cpp
src/states/State.cpp
src/log/Log.cpp
        src/world/Level.cpp include/world/Level.h)


set(PIXEL_LIB_NAME "game")
add_library(${PIXEL_LIB_NAME} ${SOURCES} ${PROJECT_SOURCE_DIR}/include/)
add_executable(${EXECUTABLE_NAME} "src/pixels/Main.cpp")
target_link_libraries(${EXECUTABLE_NAME}  ${PIXEL_LIB_NAME})




# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()

target_link_libraries(${PIXEL_LIB_NAME}  ${SFML_LIBRARIES})



# CPack packaging
#include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
include(CPack)


# tests
set(TESTS
 TestEntity
 TestResource
)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


foreach(TEST ${TESTS})
  add_executable(${TEST} tests/${TEST}.cpp )
  #set_property(TARGET ${TEST} PROPERTY DEBUG_POSTFIX _d)
  target_link_libraries(
        ${TEST}
        ${GTEST_LIBRARIES}
        ${SFML_LIBRARIES}
        ${PIXEL_LIB_NAME}
        pthread
    )
    install(TARGETS ${TEST} DESTINATION bin)
endforeach(TEST)


# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)
