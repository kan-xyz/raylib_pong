
add_executable(
    pong
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/pong/states/state_intro.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/pong/states/state_main_menu.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/pong/states/state_game.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/pong/states/state_paused.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/pong/states/state_game_over.cpp
    ${RLUT_DIR}/src/rlut_draw.cpp
    ${RLUT_DIR}/src/rlut_math.cpp
    ${RLUT_DIR}/src/rlut_physics.cpp
    ${RLUT_DIR}/src/rlut_rng.cpp
    ${RLUT_DIR}/src/rlut_state_manager.cpp
    ${RLUT_DIR}/src/rlut_window.cpp
)

target_compile_features(
    pong
    PUBLIC
    cxx_std_20
)

target_include_directories(
    pong
    PUBLIC
    ${SOURCE_DIR}
    ${RLUT_DIR}/include
    ${ENTT_DIR}/include
    ${RAYLIB_DIR}/include
)

target_link_libraries(
    pong
    ${RAYLIB_DIR}/lib/raylib.lib
    winmm.lib
)
