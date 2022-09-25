#pragma once

#include "rlut_state_manager.hpp"

#include <entt/entt.hpp>

class State_Game : public BaseState {
public:

    State_Game(StateManager* mgr);
    ~State_Game();

    void onUpdate() override;
    void onRender() override;

    void setDifficulty(const std::string& difficulty);
    void restartGame();

    void updatePlayer();
    void updateBalls();
    void checkCollission();

    void drawPlayer();
    void drawBalls();

private:
    entt::registry m_registry;
    entt::entity m_player;
    std::size_t m_ballCount = 0;
    std::size_t m_maxBallCount = 0;
    float m_timer = 0.0f;
    float m_timerLimit = 1.0f;
    int m_score = 0;
};
