#include "rlut_font_manager.hpp"

FontManager::~FontManager() {
    clearFonts();
    clearFiles();
}

bool FontManager::addFile(const std::string& id, const std::string& filename) {
    return m_files.try_emplace(id, filename).second;
}

void FontManager::removeFile(const std::string& id) {
    m_files.erase(id);
}

const std::string& FontManager::getFile(const std::string& id) const {
    return m_files.at(id);
}

void FontManager::clearFiles() {
    m_files.clear();
}

bool FontManager::addFont(const std::string& id) {
    if (m_fonts.contains(id)) { return true; }
    const std::string file = m_files.at(id);
    Font ft = LoadFont(file.c_str());
    return m_fonts.try_emplace(id, ft).second;
}

void FontManager::removeFont(const std::string& id) {
    m_fonts.erase(id);
}

const Font& FontManager::getFont(const std::string& id) const {
    return m_fonts.at(id);
}

void FontManager::clearFonts() {
    m_fonts.clear();
}

void FontManager::clear() {
    clearFonts();
    clearFiles();
}
