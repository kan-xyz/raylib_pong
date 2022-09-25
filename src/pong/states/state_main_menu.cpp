#include "state_main_menu.hpp"
#include "state_game.hpp"

#include "rlut_draw.hpp"
#include "rlut_window.hpp"

State_MainMenu::State_MainMenu(StateManager* mgr) : BaseState(mgr) {}

State_MainMenu::~State_MainMenu() {}

void State_MainMenu::onUpdate() {
    if (IsKeyPressed(KEY_DOWN)) { ++m_index; }
    if (IsKeyPressed(KEY_UP)) { --m_index; }
    m_index = (int)Clamp((float)m_index, 1.0f, 4.0f);
    if (IsKeyPressed(KEY_SPACE)) {
        StateManager& mgr = getStateManager();
        mgr.pushState("Game");
        disableState();
        State_Game& stateGame = mgr.getState<State_Game>("Game");
        stateGame.setDifficulty(m_text[(std::size_t)m_index]);
        stateGame.enableState();
    }
}

void State_MainMenu::onRender() {
    const Vector2 wSize = getWindowSize();
    float height = 0.2f;
    for (std::size_t i = 0; i < m_text.size(); ++i) {
        drawTextCentered(
            GetFontDefault(), 
            m_text[i].c_str(), 
            Vector2{ 0.5f * wSize.x, height * wSize.y },
            (i == 0 ? 50.0f : (i == 5 ? 30.0f : ((int)i == m_index ? 30.0f : 20.0f))),
            5.0f,
            ((int)i == m_index ? RED : RAYWHITE)
        );
        height += 0.1f;
    }
}
