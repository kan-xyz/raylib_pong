#pragma once

#include <raylib.h>
#include <raymath.h>

#include <unordered_map>
#include <string>

class FontManager {
public:

    FontManager() = default;
    ~FontManager();

    bool addFile(const std::string& id, const std::string& filename);
    void removeFile(const std::string& id);
    const std::string& getFile(const std::string& id) const;
    void clearFiles();

    bool addFont(const std::string& id);
    void removeFont(const std::string& id);
    const Font& getFont(const std::string& id) const;
    void clearFonts();

    void clear();

private:
    std::unordered_map<std::string, std::string> m_files;
    std::unordered_map<std::string, Font> m_fonts;
};
