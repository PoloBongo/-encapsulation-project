#include "Parsing.h"
#include "ParsingDatabase.h"

Parsing::Parsing(const std::string& _filePath) : filePath(_filePath) {
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

std::string Parsing::Trim(std::string const &_str) {
    std::string trim = _str;
    trim.erase(std::remove_if(trim.begin(), trim.end(), ::isspace), trim.end());
    return trim;
}

bool Parsing::LoadFile() {
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

std::vector<std::string> Parsing::GetAllCategory() const {
    std::vector<std::string> categories;
    for (const auto& pair : data) {
        categories.push_back(pair.first);
    }
    return categories;
}

std::unordered_map<std::string, std::string> Parsing::GetItemsInformation(const std::string& _categoryName) const {
    auto getItemsInfo = data.find(_categoryName);
    if (getItemsInfo != data.end()) {
        return getItemsInfo->second;
    }
    else {
        std::cerr << "La category <" << _categoryName << "> n'a pas ete trouve" << std::endl;
        return {};
    }
}

std::string Parsing::GetValueOfItem(const std::string& _categoryName, const std::string& _key) const {
    auto targetItemCategory = data.find(_categoryName);
    if (targetItemCategory != data.end()) {
        auto keyIt = targetItemCategory->second.find(_key);
        if (keyIt != targetItemCategory->second.end()) {
            return keyIt->second;
        }
    }
    return "";
}

std::unordered_map<std::string, DataExtraction> Parsing::GetAllDataFromInventory() {
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
            { "attack_speed", [&](const std::string& value) { RegisterField("attack_speed", dataExtraction.attack_speed, value); } },
            { "item_type", [&](const std::string& value) { RegisterField("item_type", dataExtraction.item_type, value); } },
            { "weapon_type", [&](const std::string& value) { RegisterField("weapon_type", dataExtraction.weapon_type, value); } },
            { "armor_type", [&](const std::string& value) { RegisterField("armor_type", dataExtraction.armor_type, value); } }
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

void Parsing::SetItemDetail(const DataExtraction& _item) {
    item.clear();
    if (!_item.type.empty()) item.emplace_back("type", _item.type);
    if (_item.id != -1) item.emplace_back("id", _item.id);
    if (_item.quantity != -1) item.emplace_back("quantity", _item.quantity);
    if (_item.damage != -1) item.emplace_back("damage", _item.damage);
    if (_item.durability != -1) item.emplace_back("durability", _item.durability);
    if (_item.resistance != -1) item.emplace_back("resistance", _item.resistance);
    if (!_item.name.empty()) item.emplace_back("name", _item.name);
    if (!_item.description.empty()) item.emplace_back("description", _item.description);
    if (_item.sell_price != -1) item.emplace_back("sell_price", _item.sell_price);
    if (_item.level != -1) item.emplace_back("level", _item.level);
    if (_item.defense != -1) item.emplace_back("defense", _item.defense);
    if (!_item.skill.empty()) item.emplace_back("skill", _item.skill);
    if (_item.attack != -1) item.emplace_back("attack", _item.attack);
    if (_item.attack_speed != -1) item.emplace_back("attack_speed", _item.attack_speed);
    if (_item.crit_rate != -1) item.emplace_back("crit_rate", _item.crit_rate);
    if (_item.crit_damage != -1) item.emplace_back("crit_damage", _item.crit_damage);
    if (_item.accuracy != -1) item.emplace_back("accuracy", _item.accuracy);
    if (_item.cooldown_reduction != -1) item.emplace_back("cooldown_reduction", _item.cooldown_reduction);
    if (_item.life_steal != -1) item.emplace_back("life_steal", _item.life_steal);
    if (_item.item_type != -1) item.emplace_back("item_type", _item.item_type);
    if (_item.weapon_type != -1) item.emplace_back("weapon_type", _item.weapon_type);
    if (_item.armor_type != -1) item.emplace_back("armor_type", _item.armor_type);
    if (_item.items_count != -1) item.emplace_back("items_count", _item.items_count);
    if (_item.health != -1) item.emplace_back("health", _item.health);
    if (_item.dodge_rate != -1) item.emplace_back("dodge_rate", _item.dodge_rate);
    if (_item.health_regen != -1) item.emplace_back("health_regen", _item.health_regen);
    if (_item.luck != -1) item.emplace_back("luck", _item.luck);
    item.emplace_back("isStackable", _item.isStackable);

    listItems.push_back(item);
}

void Parsing::ShowTargetItem(const std::unordered_map<std::string, DataExtraction>& _items, const std::string& _itemName) {
    auto item = _items.find(_itemName);
    if (item != _items.end()) {
        SetItemDetail(item->second);
    }
    else {
        std::cerr << "Item " << _itemName << " pas trouve" << std::endl;
    }
}

void Parsing::ShowTargetItems()
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

std::vector<std::vector<std::pair<std::string, ParsingOption>>> Parsing::GetListItems() {
    return listItems;
}