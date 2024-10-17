#include "ParsingDatabase.h"

ParsingDatabase::ParsingDatabase(const std::string& filePath) : filePath(filePath) {
    try {
        file.open(filePath);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what();
    }
};

std::string ParsingDatabase::Trim(std::string const& str) {
    std::string trim = str;
    trim.erase(std::remove_if(trim.begin(), trim.end(), ::isspace), trim.end());
    return trim;
}

bool ParsingDatabase::LoadFile() {
    if (!file.is_open()) {
        return false;
    }

    std::string currentSection;
    std::string line;
    while (std::getline(file, line)) {
        line = Trim(line);

        if (line.empty() || line[0] == ';' || line[0] == '#') {
            continue;
        }

        if (line[0] == '[' && line.back() == ']') {
            currentSection = line.substr(1, line.size() - 2);
        }
        else if (!currentSection.empty()) {
            size_t pos = line.find('=');
            if (pos != std::string::npos) {
                std::string key = Trim(line.substr(0, pos));
                std::string value = Trim(line.substr(pos + 1));
                data[currentSection][key] = value;
            }
        }
    }

    file.close();
    return true;
}