cmake_minimum_required(VERSION 3.23)
project(SFML)
set(CMAKE_CXX_STANDARD 17)

add_executable(SFML
        main.cpp
        Game.cpp Game.h States/State.cpp States/State.h States/GameState.cpp States/GameState.h Entities/Entity.cpp Entities/Entity.h States/MainMenuState.cpp States/MainMenuState.h "Gui/Button.cpp" "Gui/Button.h"
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
        Tile/TileData.h
        States/PauseMenuState.cpp
        States/PauseMenuState.h
        States/SettingsState.cpp
        States/SettingsState.h
        Gui/DropDownList.cpp
        Gui/DropDownList.h
        Map/Tilemap.cpp
        Map/Tilemap.h
        Settings/GraphicsSettings.cpp
        Settings/GraphicsSettings.h
        States/StateData.h
        Gui/TextureSelector.cpp
        Gui/TextureSelector.h
        enums/tile_types.cpp
        Entities/Components/MovementData.h
        Gui/PushButton.cpp
        Gui/PushButton.h
        Gui/CssColor.h
        Gui/SwitchButton.cpp
        Gui/SwitchButton.h
        Entities/Components/AttributeComponent.cpp
        Entities/Components/AttributeComponent.h
        Gui/PlayerGUI.cpp
        Gui/PlayerGUI.h
        Gui/ProgressBar.cpp
        Gui/ProgressBar.h
        Gui/Structs/ProgressBarData.h
        Gui/HealthBar.cpp
        Gui/HealthBar.h
        Gui/Utils.h
        Gui/Utils.cpp
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
        COMMAND ${CMAKE_COMMAND} -E remove_directory $<TARGET_FILE_DIR:SFML>/Resources/images
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Resources/images $<TARGET_FILE_DIR:SFML>/Resources/images
        #        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Resources/map $<TARGET_FILE_DIR:SFML>/Resources/map
)


target_link_libraries(SFML sfml-system sfml-window sfml-graphics sfml-audio)