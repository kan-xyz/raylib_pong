#pragma once

#include "rlut_state_manager.hpp"

class State_Paused : public BaseState {
public:

    State_Paused(StateManager* mgr);
    ~State_Paused();

    void onUpdate() override;
    void onRender() override;

private:
};
