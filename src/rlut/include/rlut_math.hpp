#pragma once

#include <raylib.h>
#include <raymath.h>

#include <cmath>

float oscillate(const float minVal, const float maxVal, const float frequency, const float phase, const float t);

Vector2 unitVec2(const float length, const float angle);
