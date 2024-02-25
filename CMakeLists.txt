cmake_minimum_required(VERSION 3.23)
project(SFML)
set(CMAKE_CXX_STANDARD 14)

add_executable(SFML
        main.cpp
        Game.cpp Game.h States/State.cpp States/State.h States/GameState.cpp States/GameState.h Entities/Entity.cpp Entities/Entity.h States/MainMenuState.cpp States/MainMenuState.h "Resource Files/Button.cpp" "Resource Files/Button.h"
        Entities/Player.cpp
        Entities/Player.h
        Entities/Components/MovementComponent.cpp
        Entities/Components/MovementComponent.h
        Entities/Components/AnimationComponent.cpp
        Entities/Components/AnimationComponent.h
        Entities/Components/Animation.cpp
        Entities/Components/Animation.h
        enums/movement_states.cpp
        States/EditorState.cpp
        States/EditorState.h
        Entities/Components/HitboxComponent.cpp
        Entities/Components/HitboxComponent.h
        Tile/Tile.cpp
        Tile/Tile.h
        States/PauseMenuState.cpp
        States/PauseMenuState.h
        States/SettingsState.cpp
        States/SettingsState.h
        "Resource Files/DropDownList.cpp"
        "Resource Files/DropDownList.h"
        Map/Tilemap.cpp
        Map/Tilemap.h
        Settings/GraphicsSettings.cpp
        Settings/GraphicsSettings.h
)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/libs/SFML-2.6.1/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/libs/SFML-2.6.1/include/SFML)

# Copy .ini files from Config directory to the build directory
# Make sure to add this code to your CMakeLists.txt file after your add_executable and before any target_link_libraries.
add_custom_command(
        TARGET SFML POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove_directory $<TARGET_FILE_DIR:SFML>/Config
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Config $<TARGET_FILE_DIR:SFML>/Config
        COMMAND ${CMAKE_COMMAND} -E remove_directory $<TARGET_FILE_DIR:SFML>/Fonts
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Fonts $<TARGET_FILE_DIR:SFML>/Fonts
        COMMAND ${CMAKE_COMMAND} -E remove_directory $<TARGET_FILE_DIR:SFML>/Resources
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Resources $<TARGET_FILE_DIR:SFML>/Resources
)


target_link_libraries(SFML sfml-system sfml-window sfml-graphics sfml-audio)