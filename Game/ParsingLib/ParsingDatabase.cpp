#include "ParsingDatabase.h"
#include "FunctionMacro.h"
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
        line = Trim(line);

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
                std::string value = Trim(line.substr(pos + 1));
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

void ParsingDatabase::JointureFile(DataExtraction& dataExtraction, std::unordered_map<std::string, std::function<void(const std::string&)>> _funcMap, int _itemID)
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
                REGISTER_FIELD("id", id),
                REGISTER_FIELD("name", name),
                REGISTER_FIELD("description", description),
                REGISTER_FIELD("isStackable", isStackable)
        };
#undef REGISTER_FIELD_DATABASE

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
