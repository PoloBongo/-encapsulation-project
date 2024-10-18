#include "Parsing.h"
#include "ParsingDatabase.h"
#include "FunctionMacro.h"

Parsing::Parsing(const std::string& _filePath) : filePath(_filePath) {
    try {
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
        std::cerr << "le fichier n'a pas ete pre-alablement ouvert dans le constructeur" << std::endl;
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

void Parsing::AddNewData(const std::string& _category, const std::string& _key, const std::string& _value) {

    std::ifstream file(filePath);
    std::vector<std::string> lines;
    std::string line;
    bool categoryFound = false;
    bool keyWritten = false;

    if (!file.is_open())
    {
        throw std::runtime_error("Un soucis est survenue lors de l'ouverture du fichier " + filePath);
    }

    while (std::getline(file, line)) {
        if (line == "[" + _category + "]") {
            categoryFound = true;
        }
        // cat�gorie trouv� mais la cl� existe pas encore, on l'�crit
        else if (line.find("[") == 0 && categoryFound) {
            if (!keyWritten) {
                lines.push_back(_key + " = " + _value);
                keyWritten = true;
            }
            categoryFound = false;
        }

        lines.push_back(line);
    }

    file.close();

    // cr�er la cat�gorie si elle n'existe pas
    if (!categoryFound && !keyWritten) {
        lines.push_back("\n[" + _category + "]");
        lines.push_back(_key + " = " + _value);
    }

    // r�-�crire dans le fichier les nouvelles data
    std::ofstream fileWrite(filePath, std::ios::trunc);
    if (!fileWrite.is_open())
    {
        throw std::runtime_error("Un soucis est survenue lors de l'ouverture du fichier pour ecrire dans " + filePath);
    }

    for (const auto& outputLine : lines) {
        fileWrite << outputLine << "\n";
    }
    fileWrite.close();
    
}

void Parsing::Modify(const std::string& _category, const std::string& _key, const std::string& _value) {
    std::ifstream file(filePath);
    std::vector<std::string> lines;
    std::string line;
    bool categoryFound = false;

    if (!file.is_open())
    {
        throw std::runtime_error("Un soucis est survenue lors de l'ouverture du fichier " + filePath);
    }

    while (std::getline(file, line)) {
        if (line == "[" + _category + "]") {
            categoryFound = true;
        }
        // si la cat�gorie est valide alors il update la cl� et/ou sa valeur
        else if (categoryFound && line.find(_key + " =") == 0) {
            line = _key + " = " + _value;
            categoryFound = false;
        }
        lines.push_back(line);
    }

    file.close();

    std::ofstream fileWrite(filePath, std::ios::trunc);
    if (!fileWrite.is_open())
    {
        throw std::runtime_error("Un soucis est survenue lors de l'ouverture du fichier pour ecrire dans " + filePath);
    }
    for (const auto& outputLine : lines) {
        fileWrite << outputLine << "\n";
    }
    fileWrite.close();
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
            REGISTER_FIELD_INVENTORY("type", type),
            REGISTER_FIELD_INVENTORY("id", id),
            REGISTER_FIELD_INVENTORY("quantity", quantity),
            REGISTER_FIELD_INVENTORY("damage", damage),
            REGISTER_FIELD_INVENTORY("durability", durability),
            REGISTER_FIELD_INVENTORY("resistance", resistance),
            REGISTER_FIELD_INVENTORY("sell_price", sell_price),
            REGISTER_FIELD_INVENTORY("level", level),
            REGISTER_FIELD_INVENTORY("defense", defense),
            REGISTER_FIELD_INVENTORY("skill", skill),
            REGISTER_FIELD_INVENTORY("attack", attack),
            REGISTER_FIELD_INVENTORY("crit_rate", crit_rate),
            REGISTER_FIELD_INVENTORY("crit_damage", crit_damage),
            REGISTER_FIELD_INVENTORY("accuracy", accuracy),
            REGISTER_FIELD_INVENTORY("cooldown_reduction", cooldown_reduction),
            REGISTER_FIELD_INVENTORY("life_steal", life_steal),
            REGISTER_FIELD_INVENTORY("attack_speed", attack_speed),
            REGISTER_FIELD_INVENTORY("item_type", item_type),
            REGISTER_FIELD_INVENTORY("weapon_type", weapon_type),
            REGISTER_FIELD_INVENTORY("armor_type", armor_type),
            REGISTER_FIELD_INVENTORY("items_count", items_count),
            REGISTER_FIELD_INVENTORY("health", health),
            REGISTER_FIELD_INVENTORY("dodge_rate", dodge_rate),
            REGISTER_FIELD_INVENTORY("health_regen", health_regen),
            REGISTER_FIELD_INVENTORY("luck", luck)
        };
#undef REGISTER_FIELD_INVENTORY


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
    if (_item.id != -0) item.emplace_back("id", _item.id);
    if (_item.quantity != -0) item.emplace_back("quantity", _item.quantity);
    if (_item.damage != -0) item.emplace_back("damage", _item.damage);
    if (_item.durability != -0) item.emplace_back("durability", _item.durability);
    if (_item.resistance != -0) item.emplace_back("resistance", _item.resistance);
    if (!_item.name.empty()) item.emplace_back("name", _item.name);
    if (!_item.description.empty()) item.emplace_back("description", _item.description);
    if (_item.sell_price != -0) item.emplace_back("sell_price", _item.sell_price);
    if (_item.level != -0) item.emplace_back("level", _item.level);
    if (_item.defense != -0) item.emplace_back("defense", _item.defense);
    if (!_item.skill.empty()) item.emplace_back("skill", _item.skill);
    if (_item.attack != -0) item.emplace_back("attack", _item.attack);
    if (_item.attack_speed != -0) item.emplace_back("attack_speed", _item.attack_speed);
    if (_item.crit_rate != -0) item.emplace_back("crit_rate", _item.crit_rate);
    if (_item.crit_damage != -0) item.emplace_back("crit_damage", _item.crit_damage);
    if (_item.accuracy != -0) item.emplace_back("accuracy", _item.accuracy);
    if (_item.cooldown_reduction != -0) item.emplace_back("cooldown_reduction", _item.cooldown_reduction);
    if (_item.life_steal != -0) item.emplace_back("life_steal", _item.life_steal);
    if (_item.item_type != -0) item.emplace_back("item_type", _item.item_type);
    if (_item.weapon_type != -0) item.emplace_back("weapon_type", _item.weapon_type);
    if (_item.armor_type != -0) item.emplace_back("armor_type", _item.armor_type);
    if (_item.items_count != -0) item.emplace_back("items_count", _item.items_count);
    if (_item.health != -0) item.emplace_back("health", _item.health);
    if (_item.dodge_rate != -0) item.emplace_back("dodge_rate", _item.dodge_rate);
    if (_item.health_regen != -0) item.emplace_back("health_regen", _item.health_regen);
    if (_item.luck != -0) item.emplace_back("luck", _item.luck);
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
        std::cerr << "fichier ini pas trouv�" << std::endl;
    }
}

std::vector<std::vector<std::pair<std::string, ParsingOption>>> Parsing::GetListItems() {
    return listItems;
}