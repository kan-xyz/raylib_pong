#include "state_game.hpp"

#include "pong/core/components.hpp"
#include "pong/core/service_locator.hpp"
#include "pong/states/state_game_over.hpp"

#include "rlut_window.hpp"
#include "rlut_math.hpp"
#include "rlut_rng.hpp"
#include "rlut_physics.hpp"

State_Game::State_Game(StateManager* mgr) : BaseState(mgr) {
    const Vector2 wSize = getWindowSize();
    const Vector2 pSize = { 200.0f, 30.0f };

    m_player = m_registry.create();
    m_registry.emplace<RectComponent>(m_player, Rectangle{ 0.5f * wSize.x - 0.5f * pSize.x, 0.8f * wSize.y - 0.5f * pSize.y, pSize.x, pSize.y });
}

State_Game::~State_Game() {
    m_registry.clear();
}

void State_Game::onUpdate() {
    updatePlayer();
    updateBalls();
    checkCollission();
    if (IsKeyPressed(KEY_SPACE)) {
        setUpdateStatus(false);
        getStateManager().pushState("Paused");
    }
}

void State_Game::onRender() {
    drawPlayer();
    drawBalls();
    const std::string text = "score: " + std::to_string(m_score);
    DrawTextEx(GetFontDefault(), text.c_str(), Vector2{ 10.0f, 10.0f }, 30.0f, 5.0f, RAYWHITE);
}

void State_Game::setDifficulty(const std::string& difficulty) {
    if (difficulty == "easy") { m_maxBallCount = 3; }
    else if (difficulty == "normal") { m_maxBallCount = 6; }
    else if (difficulty == "hard") { m_maxBallCount = 9; }
    else if (difficulty == "lunatic") { m_maxBallCount = 12; }
    restartGame();
}

void State_Game::restartGame() {
    const Vector2 wSize = getWindowSize();
    const Vector2 pSize = { 200.0f, 30.0f };

    m_registry.get<RectComponent>(m_player).rect = { 0.5f * wSize.x - 0.5f * pSize.x, 0.8f * wSize.y - 0.5f * pSize.y, pSize.x, pSize.y };
    auto view = m_registry.view<CircleComponent>();
    m_registry.destroy(view.begin(), view.end());
    m_ballCount = 0;
    m_timer = 0.0f;
    m_score = 0;
}

void State_Game::updatePlayer() {
    const Vector2 wSize = getWindowSize();
    const float dt = GetFrameTime();
    const float speed = 1500.0f;
    const float slowFactor = 0.3f;
    auto view = m_registry.view<RectComponent>();
    for (auto entity : view) {
        Rectangle& r = view.get<RectComponent>(entity).rect;
        if (IsKeyDown(KEY_LEFT_SHIFT)) {
            if (IsKeyDown(KEY_LEFT)) { r.x -= dt * slowFactor * speed; }
            if (IsKeyDown(KEY_RIGHT)) { r.x += dt * slowFactor * speed; }
        }
        else {
            if (IsKeyDown(KEY_LEFT)) { r.x -= dt * speed; }
            if (IsKeyDown(KEY_RIGHT)) { r.x += dt * speed; }
        }
        r.x = Clamp(r.x, 0.0f, wSize.x - r.width);
    }
}

void State_Game::updateBalls() {
    const Vector2 wSize = getWindowSize();
    const float dt = GetFrameTime();
    RNG& rng = *getStateManager().getServiceLocator<ServiceLocator>().rng;

    if (m_ballCount < m_maxBallCount) {
        m_timer += dt;
        if (m_timer > m_timerLimit) {
            entt::entity b = m_registry.create();
            m_registry.emplace<CircleComponent>(b, Vector2{ 0.5f * wSize.x, 0.5f * wSize.y }, 10.0f);
            m_registry.emplace<VelocityComponent>(b, unitVec2(500.0f, DEG2RAD * rng.uniformOffsetDistribution(270.0f, 30.0f)));
            m_timer = 0.0f;
            ++m_ballCount;
        }
    }

    auto group = m_registry.group<CircleComponent, VelocityComponent>();
    for (auto entity : group) {
        auto [cir, vel] = group.get<CircleComponent, VelocityComponent>(entity);
        cir.position = calculateKinematics(cir.position, vel.velocity, dt);
        if (cir.position.x > (wSize.x - cir.radius)) {
            cir.position.x = wSize.x - cir.radius;
            vel.velocity.x = -vel.velocity.x;
        }
        else if (cir.position.x < cir.radius) {
            cir.position.x = cir.radius;
            vel.velocity.x = -vel.velocity.x;
        }
        if (cir.position.y < cir.radius) {
            cir.position.y = cir.radius;
            vel.velocity.y = -vel.velocity.y;
        }
        else if (cir.position.y > wSize.y) {
            disableState();
            StateManager& mgr = getStateManager();
            mgr.pushState("GameOver");
            State_GameOver& st = mgr.getState<State_GameOver>("GameOver");
            st.setScore(m_score);
        }
    }
}

void State_Game::checkCollission() {
    Rectangle& r = m_registry.get<RectComponent>(m_player).rect;
    auto group = m_registry.group<CircleComponent, VelocityComponent>();
    for (auto entity : group) {
        auto [cir, vel] = group.get<CircleComponent, VelocityComponent>(entity);
        if (CheckCollisionCircleRec(cir.position, cir.radius, r)) {
            cir.position.y = r.y - cir.radius;
            vel.velocity.y = -vel.velocity.y;
            ++m_score;
        }
    }
}

void State_Game::drawPlayer() {
    auto view = m_registry.view<RectComponent>();
    for (auto entity : view) {
        DrawRectangleRec(view.get<RectComponent>(entity).rect, SKYBLUE);
    }
}

void State_Game::drawBalls() {
    auto view = m_registry.view<CircleComponent>();
    for (auto entity : view) {
        const CircleComponent& c = view.get<CircleComponent>(entity);
        DrawCircleV(c.position, c.radius, ORANGE);
    }
}

