#include "rlut_rng.hpp"

#include <chrono>

void RNG::init() {
    seed(std::chrono::duration_cast<std::chrono::duration<unsigned int, std::milli>>(std::chrono::steady_clock::now().time_since_epoch()).count());
}

void RNG::seed(const unsigned int seedVal) {
    m_rng.seed(seedVal);
}

int RNG::uniformDistribution(const int minVal, const int maxVal) {
    return std::uniform_int_distribution<int>{ minVal, maxVal }(m_rng);
}

float RNG::uniformDistribution(const float minVal, const float maxVal) {
    return std::uniform_real_distribution<float>{ minVal, maxVal }(m_rng);
}

int RNG::uniformOffsetDistribution(const int center, const int offset) {
    return uniformDistribution(center - offset, center + offset);
}

float RNG::uniformOffsetDistribution(const float center, const float offset) {
    return uniformDistribution(center - offset, center + offset);
}

int RNG::operator () (const int minVal, const int maxVal) {
    return uniformDistribution(minVal, maxVal);
}

float RNG::operator () (const float minVal, const float maxVal) {
    return uniformDistribution(minVal, maxVal);
}

std::mt19937& RNG::getEngine() {
    return m_rng;
}
