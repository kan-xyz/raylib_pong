#pragma once

#include <raylib.h>
#include <raymath.h>

class RectComponent {
public:

    RectComponent() = default;
    RectComponent(const Rectangle rec) : rect(rec) {}

public:
    Rectangle rect{ 0.0f, 0.0f, 0.0f, 0.0f };
};

class CircleComponent {
public:

    CircleComponent() = default;
    CircleComponent(const Vector2 pos, const float rad) : position(pos), radius(rad) {}

public:
    Vector2 position{ 0.0f, 0.0f };
    float radius = 0.0f;
};

class ColorComponent {
public:

    ColorComponent() = default;
    ColorComponent(const Color col) : color(col) {}

public:
    Color color = RAYWHITE;
};

class VelocityComponent {
public:

    VelocityComponent() = default;
    VelocityComponent(const Vector2 vel) : velocity(vel) {}

public:
    Vector2 velocity{ 0.0f, 0.0f };
};
