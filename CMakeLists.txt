cmake_minimum_required(VERSION 3.23)
project(SFML)
set(CMAKE_CXX_STANDARD 17)
# Include FetchContent module
include(FetchContent)

# Fetch the nlohmann json library
FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.2 # Specify the version you want to use
)
FetchContent_MakeAvailable(nlohmann_json)

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
        enums/behaviour_types.cpp
        enums/skill_enum.cpp
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
        Gui/Sidebar.cpp
        Gui/Sidebar.h
        Gui/Structs/SidebarButton.h
        Items/Item.cpp
        Items/Item.h
        Items/Weapons/MeleeWeapon/MeleeWeapon.cpp
        Items/Weapons/MeleeWeapon/MeleeWeapon.h
        Items/Weapons/MeleeWeapon/Sword.cpp
        Items/Weapons/MeleeWeapon/Sword.h
        Items/Weapons/RangeWeapon/RangedWeapon.cpp
        Items/Weapons/RangeWeapon/RangedWeapon.h
        Items/Weapons/RangeWeapon/Bow.cpp
        Items/Weapons/RangeWeapon/Bow.h
        Entities/Components/SkillComponent.cpp
        Entities/Components/SkillComponent.h
        Entities/Components/Skill.cpp
        Entities/Components/Skill.h
        Entities/Enemies/Enemy.cpp
        Entities/Enemies/Enemy.h
        Entities/EntityDimensionData.h
        Entities/EnemySpawner.cpp
        Entities/EnemySpawner.h
        Helper/Json/Serializable.h
        Helper/Json/Struct/MapData.h
        enums/enemy_types.cpp
        enums/tile_types.cpp
        enums/directions.cpp
        Entities/Enemies/Wisp.cpp
        Entities/Enemies/Wisp.h
        Entities/Enemies/Thief.cpp
        Entities/Enemies/Thief.h
        enums/player_animations.cpp Items/Weapons/Weapon.cpp Items/Weapons/Weapon.h)

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

# Link the nlohmann json library
target_link_libraries(SFML PRIVATE sfml-system sfml-window sfml-graphics sfml-audio nlohmann_json::nlohmann_json)