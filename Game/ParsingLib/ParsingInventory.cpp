#include "ParsingInventory.h"
#include "ParsingDatabase.h"

ParsingInventory::ParsingInventory(const std::string& _filePath) : filePath(_filePath) {
    try {
        SetFilePath(_filePath);
        file.open(_filePath);
        if (!file.is_open())
        {
            throw std::runtime_error("Un soucis est survenue lors de l'ouverture du fichier" + filePath);
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what();
    }
};

std::string ParsingInventory::Trim(std::string const &_str) {
    std::string trim = _str;
    trim.erase(std::remove_if(trim.begin(), trim.end(), ::isspace), trim.end());
    return trim;
}

bool ParsingInventory::LoadFile() {
    if (!file.is_open()) {
        std::cerr << "le fichier n'a pas ete prealablement ouvert dans le constructeur" << std::endl;
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

std::vector<std::string> ParsingInventory::GetAllCategory() const {
    std::vector<std::string> categories;
    for (const auto& pair : data) {
        categories.push_back(pair.first);
    }
    return categories;
}

std::unordered_map<std::string, std::string> ParsingInventory::GetItemsInformation(const std::string& _categoryName) const {
    auto getItemsInfo = data.find(_categoryName);
    if (getItemsInfo != data.end()) {
        return getItemsInfo->second;
    }
    else {
        std::cerr << "La category <" << _categoryName << "> n'a pas ete trouve" << std::endl;
        return {};
    }
}

std::string ParsingInventory::GetValueOfItem(const std::string& _categoryName, const std::string& _key) const {
    auto targetItemCategory = data.find(_categoryName);
    if (targetItemCategory != data.end()) {
        auto keyIt = targetItemCategory->second.find(_key);
        if (keyIt != targetItemCategory->second.end()) {
            return keyIt->second;
        }
    }
    return "";
}

std::unordered_map<std::string, DataExtraction> ParsingInventory::GetAllDataFromInventory() {
    ParsingDatabase parsingDatabase("database.ini");
    std::unordered_map<std::string, DataExtraction> items;
    if (data.empty()) {
        std::cerr << "Aucune donnee n'a ete extrait de la database" << std::endl;
    }
    for (const auto& datas : data) {
        const std::string& categoryName = datas.first;
        auto extractItem = GetItemsInformation(categoryName);
        if (extractItem.empty()) {
            std::cerr << "aucun item trouve pour la category <" << datas.first << ">" << std::endl;
            continue;
        }

        DataExtraction dataExtraction;

        functionMap = {
            { "type", [&](const std::string& value) { RegisterField("type", dataExtraction.type, value); } },
            { "id", [&](const std::string& value) { RegisterField("id", dataExtraction.id, value); }},
            { "quantity", [&](const std::string& value) { RegisterField("quantity", dataExtraction.quantity, value); } },
            { "damage", [&](const std::string& value) { RegisterField("damage", dataExtraction.damage, value); } },
            { "durability", [&](const std::string& value) { RegisterField("durability", dataExtraction.durability, value); } },
            { "resistance", [&](const std::string& value) { RegisterField("resistance", dataExtraction.resistance, value); } },
            { "name", [&](const std::string& value) { RegisterField("name", dataExtraction.name, value); } },
            { "description", [&](const std::string& value) { RegisterField("description", dataExtraction.description, value); } },
            { "sell_price", [&](const std::string& value) { RegisterField("sell_price", dataExtraction.sell_price, value); } },
            { "level", [&](const std::string& value) { RegisterField("level", dataExtraction.level, value); } },
            { "defense", [&](const std::string& value) { RegisterField("defense", dataExtraction.defense, value); } },
            { "skill", [&](const std::string& value) { RegisterField("skill", dataExtraction.skill, value); } },
            { "attack", [&](const std::string& value) { RegisterField("attack", dataExtraction.attack, value); } },
            { "crit_rate", [&](const std::string& value) { RegisterField("crit_rate", dataExtraction.crit_rate, value); } },
            { "crit_damage", [&](const std::string& value) { RegisterField("crit_damage", dataExtraction.crit_damage, value); } },
            { "accuracy", [&](const std::string& value) { RegisterField("accuracy", dataExtraction.accuracy, value); } },
            { "cooldown_reduction", [&](const std::string& value) { RegisterField("cooldown_reduction", dataExtraction.cooldown_reduction, value); } },
            { "life_steal", [&](const std::string& value) { RegisterField("life_steal", dataExtraction.life_steal, value); } },
            { "attack_speed", [&](const std::string& value) { RegisterField("attack_speed", dataExtraction.attack_speed, value); } }
        };

        for (const auto& item : extractItem) {
            const std::string& key = item.first;
            const std::string& value = item.second;

            if (functionMap.find(key) != functionMap.end()) {
                if (key == "type") {
                    newType = value;
                }
                if (key == "id" && !newType.empty())
                {
                    newID = std::stoi(value);
                    parsingDatabase.JointureFile(dataExtraction, functionMap, newID);
                }
                functionMap[key](value);
            }
            else {
                std::cout << "Cle inconnue: " << key << std::endl;
            }
        }

        items[categoryName] = dataExtraction;
    }

    return items;
}

void ParsingInventory::SetItemDetail(const DataExtraction& _item) {
    item.clear();
    // la macro permet de simplement ajouter un nouveau type/attribut dans la struct DataExtraction
    // et rien besoin de faire, elle sera automatiquement pris en compte
    #define HANDLE_FIELD(type, name, default_value) \
        if (_item.name != default_value) { \
            item.emplace_back(#name, _item.name); \
        }

    DATA_FIELDS(HANDLE_FIELD)

    #undef HANDLE_FIELD
    item.emplace_back("isStackable", _item.isStackable);

    listItems.push_back(item);
}

void ParsingInventory::ShowTargetItem(const std::unordered_map<std::string, DataExtraction>& _items, const std::string& _itemName) {
    auto item = _items.find(_itemName);
    if (item != _items.end()) {
        SetItemDetail(item->second);
    }
    else {
        std::cerr << "Item " << _itemName << " pas trouve" << std::endl;
    }
}

void ParsingInventory::ShowTargetItems()
{
    if (LoadFile()) {

        std::unordered_map<std::string, DataExtraction> items = GetAllDataFromInventory();
        std::vector<std::string> sections = GetAllCategory();
        for (const auto& section : sections) {
            ShowTargetItem(items, section);
        }
    }
    else {
        std::cerr << "fichier ini pas trouvé" << std::endl;
    }
}

std::vector<std::vector<std::pair<std::string, ParsingOption>>> ParsingInventory::GetListItems() {
    return listItems;
}