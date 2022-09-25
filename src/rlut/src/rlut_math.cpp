#include "rlut_math.hpp"

float oscillate(const float minVal, const float maxVal, const float frequency, const float phase, const float t) {
    return Lerp(minVal, maxVal, 0.5f * (1.0f - std::cos(2.0f * PI * frequency * t + phase)));
}

Vector2 unitVec2(const float length, const float angle) {
    return Vector2{ length * std::cos(angle), length * std::sin(angle) };
}
