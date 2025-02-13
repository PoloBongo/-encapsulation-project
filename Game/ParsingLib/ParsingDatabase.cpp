#include "ParsingDatabase.h"
#include <functional>

ParsingDatabase::ParsingDatabase(const std::string& _filePath, bool _canExtract) : filePath(_filePath), canExtract(_canExtract) {
    try {
        file.open(filePath);
        if (!file.is_open())
        {
            throw std::runtime_error("Un soucis est survenue lors de l'ouverture du fichier" + filePath);
        }
        LoadFile();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what();
    }
};

std::string ParsingDatabase::Trim(std::string const& _str) {
    std::string trim = _str;
    trim.erase(std::remove_if(trim.begin(), trim.end(), ::isspace), trim.end());
    return trim;
}

bool ParsingDatabase::LoadFile() {
    if (!file.is_open()) {
        std::cerr << "le fichier n'a pas ete pre-alablement ouvert dans le constructeur" << std::endl;
        return false;
    }

    std::string currentType;
    std::string line;
    while (std::getline(file, line)) {
        line = line;

        if (line.empty() || line[0] == ';' || line[0] == '#') {
            continue;
        }

        if (line[0] == '(' && line.back() == ')') {
            currentType = line.substr(1, line.size() - 2);
        }
        else if (!currentType.empty()) {
            size_t pos = line.find('=');
            if (pos != std::string::npos) {
                std::string key = Trim(line.substr(0, pos));
                std::string value = line.substr(pos + 1);
                value = value.erase(0, value.find_first_not_of(' '));
                data[currentType][key] = value;
            }
        }
    }

    file.close();
    return true;
}

std::unordered_map<std::string, std::string> ParsingDatabase::GetItemsInformation(const std::string& _categoryName) const {
    auto getItemsInfo = data.find(_categoryName);
    if (getItemsInfo != data.end()) {
        return getItemsInfo->second;
    }
    else {
        std::cerr << "La category <" << _categoryName << "> n'a pas ete trouve" << std::endl;
        return {};
    }
}

void ParsingDatabase::JointureFile(DataExtraction& _dataExtraction, std::unordered_map<std::string, std::function<void(const std::string&)>> _funcMap, int _itemID)
{
    if (data.empty()) {
        std::cerr << "Aucune donnee n'a ete extrait de la database" << std::endl;
    }

    for (const auto& datas : data) {
        auto extractItem = GetItemsInformation(datas.first);
        if (extractItem.empty()) {
            std::cerr << "aucun item trouve pour la category <" << datas.first << ">" << std::endl;
            continue;
        }

        _funcMap = {
            { "id", [&](const std::string& value) { RegisterField("id", _dataExtraction.id, value); }},
            { "name", [&](const std::string& value) { RegisterField("name", _dataExtraction.name, value); } },
            { "description", [&](const std::string& value) { RegisterField("description", _dataExtraction.description, value); } },
            { "isStackable", [&](const std::string& value) { RegisterField("isStackable", _dataExtraction.isStackable, value); } },
            { "item_type", [&](const std::string& value) { RegisterField("item_type", _dataExtraction.item_type, value); } },
            { "weapon_type", [&](const std::string& value) { RegisterField("weapon_type", _dataExtraction.weapon_type, value); } },
            { "armor_type", [&](const std::string& value) { RegisterField("armor_type", _dataExtraction.armor_type, value); } }
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
                std::cerr << "Cle inconnue: " << key << std::endl;
            }
        }
    }
}
