#pragma once

#include <raylib.h>
#include <raymath.h>

#include <unordered_map>
#include <string>

class TextureManager {
public:

    TextureManager() = default;
    ~TextureManager();

    bool addFile(const std::string& id, const std::string& filename);
    void removeFile(const std::string& id);
    const std::string& getFile(const std::string& id) const;
    void clearFiles();

    bool addTexture(const std::string& id);
    void removeTexture(const std::string& id);
    const Texture2D& getTexture(const std::string& id) const;
    void clearTextures();

    void clear();

private:
    std::unordered_map<std::string, std::string> m_files;
    std::unordered_map<std::string, Texture2D> m_textures;
};
