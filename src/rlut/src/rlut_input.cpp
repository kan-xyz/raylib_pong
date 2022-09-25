#include "rlut_input.hpp"

#include <cmath>

Vector2 getVec2KeyDown(const float length, const KeyboardKey up, const KeyboardKey down, const KeyboardKey left, const KeyboardKey right) {
    Vector2 v{ 0.0f, 0.0f };
    if (IsKeyDown(up)) { v.y += length; }
    if (IsKeyDown(down)) { v.y -= length; }
    if (IsKeyDown(left)) { v.x -= length; }
    if (IsKeyDown(right)) { v.x += length; }
    return v;
}
