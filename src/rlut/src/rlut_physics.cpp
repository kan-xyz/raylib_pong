#include "rlut_physics.hpp"

Vector2 calculateKinematics(const Vector2 v0, const Vector2 v, const float dt) {
    return Vector2Add(v0, Vector2Scale(v, dt));
}
