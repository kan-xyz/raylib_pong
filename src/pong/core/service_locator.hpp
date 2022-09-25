#pragma once

class TextureManager;
class FontManager;
class RNG;

struct ServiceLocator {
    TextureManager* texMgr = nullptr;
    FontManager* fontMgr = nullptr;
    RNG* rng = nullptr;
};
