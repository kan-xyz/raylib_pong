#include "rlut_texture_manager.hpp"

TextureManager::~TextureManager() {
    clearTextures();
    clearFiles();
}

bool TextureManager::addFile(const std::string& id, const std::string& filename) {
    return m_files.try_emplace(id, filename).second;
}

void TextureManager::removeFile(const std::string& id) {
    m_files.erase(id);
}

const std::string& TextureManager::getFile(const std::string& id) const {
    return m_files.at(id);
}

void TextureManager::clearFiles() {
    m_files.clear();
}

bool TextureManager::addTexture(const std::string& id) {
    if (m_textures.contains(id)) { return true; }
    const std::string file = m_files.at(id);
    Texture2D ft = LoadTexture(file.c_str());
    return m_textures.try_emplace(id, ft).second;
}

void TextureManager::removeTexture(const std::string& id) {
    m_textures.erase(id);
}

const Texture& TextureManager::getTexture(const std::string& id) const {
    return m_textures.at(id);
}

void TextureManager::clearTextures() {
    m_textures.clear();
}

void TextureManager::clear() {
    clearTextures();
    clearFiles();
}
