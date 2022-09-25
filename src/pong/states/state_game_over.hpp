#pragma once

#include "rlut_state_manager.hpp"

#include <array>
#include <string>

class State_GameOver : public BaseState {
public:

    State_GameOver(StateManager* mgr);
    ~State_GameOver();

    void onUpdate() override;
    void onRender() override;

    void setScore(const int score);

private:
    int m_score = 0;
    int m_index = 2;
    std::array<std::string, 5> m_text = {
        "game over",
        "score: ",
        "restart",
        "main menu",
        "press space to select"
    };
};
