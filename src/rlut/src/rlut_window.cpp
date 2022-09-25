#include "rlut_window.hpp"

Vector2 getWindowSize() {
    return Vector2{ static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()) };
}
