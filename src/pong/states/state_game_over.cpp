#include "state_game_over.hpp"

#include "state_game.hpp"

#include "rlut_draw.hpp"
#include "rlut_window.hpp"

State_GameOver::State_GameOver(StateManager* mgr) : BaseState(mgr) {}

State_GameOver::~State_GameOver() {}

void State_GameOver::onUpdate() {
    if (IsKeyPressed(KEY_DOWN)) { ++m_index; }
    if (IsKeyPressed(KEY_UP)) { --m_index; }
    m_index = (int)Clamp((float)m_index, 2.0f,  3.0f);

    if (IsKeyPressed(KEY_SPACE)) {
        const std::string& x = m_text[(std::size_t)m_index];
        StateManager& mgr = getStateManager();
        disableState();
        if (x == "restart") {
            mgr.pushState("Game");
            mgr.getState<State_Game>("Game").restartGame();
        }
        else if (x == "main menu") {
            mgr.pushState("MainMenu");
        }
    }
}

void State_GameOver::onRender() {
    const Vector2 wSize = getWindowSize();
    float height = 0.2f;
    int idx = 0;
    for (const std::string s : m_text) {
        drawTextCentered(
            GetFontDefault(),
            s.c_str(),
            Vector2{ 0.5f * wSize.x, height * wSize.y },
            (idx == 0 || idx == 1 ? 50.0f : (idx == 4 ? 30.0f : (idx == m_index ? 30.0f : 20.0f))),
            5.0f,
            (idx == 1 ? SKYBLUE : (idx == m_index ? RED : RAYWHITE))
        );
        ++idx;
        height += 0.1f;
    }
}

void State_GameOver::setScore(const int score) {
    m_text[1] = "score: " + std::to_string(score);
}
