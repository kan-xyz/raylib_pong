#include "state_paused.hpp"

#include "rlut_window.hpp"
#include "rlut_draw.hpp"

State_Paused::State_Paused(StateManager* mgr) : BaseState(mgr) {}

State_Paused::~State_Paused() {}

void State_Paused::onUpdate() {
    if (IsKeyPressed(KEY_SPACE)) {
        disableState();
        StateManager& mgr = getStateManager();
        mgr.pushState("Game");
    }
}

void State_Paused::onRender() {
    const Vector2 wSize = getWindowSize();
    DrawRectangleRec(Rectangle{ 0.0f, 0.0f, wSize.x, wSize.y }, Color{ 0, 0, 0, 172 });
    drawTextCentered(GetFontDefault(), "paused", Vector2{ 0.5f * wSize.x, 0.3f * wSize.y }, 30.0f, 5.0f, RAYWHITE);
    drawTextCentered(GetFontDefault(), "press space to resume", Vector2{ 0.5f * wSize.x, 0.5f * wSize.y }, 30.0f, 5.0f, RAYWHITE);
}
