#pragma once

#include "rlut_state_manager.hpp"

#include <string>

class State_Intro : public BaseState {
public:

    State_Intro(StateManager* mgr);
    ~State_Intro();

    void onUpdate() override;
    void onRender() override;

private:
    std::string m_title = "pong";
    std::string m_instructions = "press space to continue";
    float m_timer = 0.0f;
};
