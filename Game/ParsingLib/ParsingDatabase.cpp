#include "ParsingDatabase.h"
#include <functional>

ParsingDatabase::ParsingDatabase(const std::string& filePath) : filePath(filePath) {
    try {
        file.open(filePath);
        LoadFile();
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
    std::string currentType;
    std::string line;
    while (std::getline(file, line)) {
        line = Trim(line);

        if (line.empty() || line[0] == ';' || line[0] == '#') {
            continue;
        }

        if (line[0] == '[' && line.back() == ']') {
            currentSection = line.substr(1, line.size() - 2);
        }

        if (line[0] == '(' && line.back() == ')') {
            currentType = line.substr(1, line.size() - 2);
            test.push_back(currentType);
        }
        else if (!currentType.empty()) {
            size_t pos = line.find('=');
            if (pos != std::string::npos) {
                std::string key = Trim(line.substr(0, pos));
                std::string value = Trim(line.substr(pos + 1));
                data[currentType][key] = value;
            }
        }
    }

    file.close();
    return true;
}

std::unordered_map<std::string, std::string> ParsingDatabase::GetItemsInformation(const std::string& sectionName) const {
    auto getItemsInfo = data.find(sectionName);
    if (getItemsInfo != data.end()) {
        return getItemsInfo->second;
    }
    else {
        return {};
    }
}

void ParsingDatabase::JointureFile(DataExtraction& _dataExtraction, std::unordered_map<std::string, std::function<void(const std::string&)>> _funcMap, Parsing& _parsing, int _itemID)
{
    if (!data.empty()) {
        for (const auto& datas : data) {
            auto extractItem = GetItemsInformation(datas.first);
            if (!extractItem.empty()) {
                _funcMap = {
                    { "id", [&](const std::string& value) { _parsing.RegisterField("id", _dataExtraction.id, value); } },
                    { "name", [&](const std::string& value) { _parsing.RegisterField("name", _dataExtraction.name, value); } },
                    { "description", [&](const std::string& value) { _parsing.RegisterField("description", _dataExtraction.description, value); }},
                    { "isStackable", [&](const std::string& value) { _parsing.RegisterField("isStackable", _dataExtraction.isStackable, value); }},
                };

                canExtract = false;

                for (const auto& item : extractItem) {
                    const std::string& key = item.first;
                    const std::string& value = item.second;

                    if (_funcMap.find(key) != _funcMap.end()) {
                        if (key == "id")
                        {
                            if (std::stoi(value) == _itemID)
                            {
                                canExtract = true;
                            }
                        }
                        if (canExtract) _funcMap[key](value);
                    }
                    else {
                        std::cout << "Cle inconnue: " << key << std::endl;
                    }
                }
            }
        }
    }    
}
