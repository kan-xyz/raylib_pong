#include "state_intro.hpp"

#include "rlut_draw.hpp"
#include "rlut_window.hpp"
#include "rlut_math.hpp"

State_Intro::State_Intro(StateManager* mgr) : BaseState(mgr) {}

State_Intro::~State_Intro() {}

void State_Intro::onUpdate() {
    m_timer += GetFrameTime();
    if (IsKeyPressed(KEY_SPACE)) {
        setUpdateStatus(false);
        setRenderStatus(false);
        getStateManager().pushState("MainMenu");
    }
}

void State_Intro::onRender() {
    const float x = oscillate(0.0f, 1.0f, 1.0f, 0.0f, m_timer);
    const Vector2 wSize = getWindowSize();
    drawTextCentered(GetFontDefault(), m_title.c_str(), Vector2{ 0.5f * wSize.x, 0.2f * wSize.y }, 60.0f, 5.0f, RAYWHITE);
    drawTextCentered(GetFontDefault(), m_instructions.c_str(), Vector2{ 0.5f * wSize.x, 0.5f * wSize.y }, 30.0f, 5.0f, x > 0.5f ? RAYWHITE : BLANK);
}
