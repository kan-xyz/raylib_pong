#include "rlut_draw.hpp"

void drawTextCentered(const Font font, const char* text, const Vector2 position, const float fontSize, const float spacing, const Color color) {
    const Vector2 tSize = MeasureTextEx(font, text, fontSize, spacing);
    DrawTextEx(font, text, Vector2Subtract(position, Vector2Scale(tSize, 0.5f)), fontSize, spacing, color);
}
