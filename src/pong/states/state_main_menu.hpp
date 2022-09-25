#pragma once

#include "rlut_state_manager.hpp"

#include <array>

class State_MainMenu : public BaseState {
public:

    State_MainMenu(StateManager* mgr);
    ~State_MainMenu();

    void onUpdate() override;
    void onRender() override;

private:
    std::array<std::string, 6> m_text = {
        "select a difficulty",
        "easy",
        "normal",
        "hard",
        "lunatic",
        "press space to continue"
    };
    int m_index = 1;
};
