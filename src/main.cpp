#include <raylib.h>

#include "pong/core/service_locator.hpp"

#include "pong/states/state_intro.hpp"
#include "pong/states/state_main_menu.hpp"
#include "pong/states/state_game.hpp"
#include "pong/states/state_paused.hpp"
#include "pong/states/state_game_over.hpp"

#include "rlut_rng.hpp"

bool initStateManager(StateManager& mgr) {
    bool result = true;

    result = mgr.registerState<State_Intro>("Intro");
    result = mgr.registerState<State_MainMenu>("MainMenu");
    result = mgr.registerState<State_Game>("Game");
    result = mgr.registerState<State_Paused>("Paused");
    result = mgr.registerState<State_GameOver>("GameOver");
    mgr.pushState("Intro");

    return result;
}

int main() {
    InitWindow(600, 800, "pong game");
    SetTargetFPS(60);

    StateManager stateManager;
    initStateManager(stateManager);

    RNG rng;
    rng.init();

    ServiceLocator locator;
    locator.rng = &rng;

    stateManager.setServiceLocator(&locator);

    while (!WindowShouldClose()) {
        stateManager.update();
        BeginDrawing();
        ClearBackground(BLACK);
        stateManager.render();
        EndDrawing();
    }

    stateManager.clearStates();

    CloseWindow();
    return 0;
}
