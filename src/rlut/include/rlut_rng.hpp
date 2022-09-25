#pragma once

#include <raylib.h>
#include <raymath.h>

#include <random>

class RNG {
public:

    RNG() = default;

    void init();
    void seed(const unsigned int seedVal);

    int uniformDistribution(const int minVal, const int maxVal);
    float uniformDistribution(const float minVal, const float maxVal);

    int uniformOffsetDistribution(const int center, const int offset);
    float uniformOffsetDistribution(const float center, const float offset);

    int operator () (const int minVal, const int maxVal);
    float operator () (const float minVal, const float maxVal);

    std::mt19937& getEngine();

private:
    std::mt19937 m_rng;
};
