#include "Parsing.h"

Parsing::Parsing(const std::string& filePath) : filePath(filePath) {
    try {
        file.open(filePath);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what();
    }
};

std::string Parsing::Trim(std::string const &str) {
    std::string trim = str;
    trim.erase(std::remove_if(trim.begin(), trim.end(), ::isspace), trim.end());
    return trim;
}

bool Parsing::LoadFile() {
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

std::vector<std::string> Parsing::GetAllCategory() const {
    std::vector<std::string> categories;
    for (const auto& pair : data) {
        categories.push_back(pair.first);
    }
    return categories;
}

std::unordered_map<std::string, std::string> Parsing::GetItemsInformation(const std::string& sectionName) const {
    auto getItemsInfo = data.find(sectionName);
    if (getItemsInfo != data.end()) {
        return getItemsInfo->second;
    }
    else {
        return {};
    }
}

std::string Parsing::GetValueOfItem(const std::string& sectionName, const std::string& key) const {
    auto targetItemCategory = data.find(sectionName);
    if (targetItemCategory != data.end()) {
        auto keyIt = targetItemCategory->second.find(key);
        if (keyIt != targetItemCategory->second.end()) {
            return keyIt->second;
        }
    }
    return "";
}

void Parsing::AddNewData(const std::string& category, const std::string& key, const std::string& value) {

    std::ifstream file(filePath);
    std::vector<std::string> lines;
    std::string line;
    bool categoryFound = false;
    bool keyWritten = false;

    if (file.is_open())
    {
        while (std::getline(file, line)) {
            if (line == "[" + category + "]") {
                categoryFound = true;
            }
            // catégorie trouvé mais la clé existe pas encore, on l'écrit
            else if (line.find("[") == 0 && categoryFound) {
                if (!keyWritten) {
                    lines.push_back(key + " = " + value);
                    keyWritten = true;
                }
                categoryFound = false;
            }

            lines.push_back(line);
        }

        file.close();
    }

    // créer la catégorie si elle n'existe pas
    if (!categoryFound && !keyWritten) {
        lines.push_back("\n[" + category + "]");
        lines.push_back(key + " = " + value);
    }

    // ré-écrire dans le fichier les nouvelles data
    std::ofstream fileWrite(filePath, std::ios::trunc);
    if (fileWrite.is_open()) {
        for (const auto& outputLine : lines) {
            fileWrite << outputLine << "\n";
        }
        fileWrite.close();
    }
    
}

void Parsing::Modify(const std::string& _category, const std::string& _key, const std::string& _value) {
    std::ifstream file(filePath);
    std::vector<std::string> lines;
    std::string line;
    bool categoryFound = false;

    if (file.is_open())
    {
        while (std::getline(file, line)) {
            if (line == "[" + _category + "]") {
                categoryFound = true;
            }
            // si la catégorie est valide alors il update la clé et/ou sa valeur
            else if (categoryFound && line.find(_key + " =") == 0) {
                line = _key + " = " + _value;
                categoryFound = false;
            }
            lines.push_back(line);
        }

        file.close();
    }

    std::ofstream writeFile(filePath, std::ios::trunc);
    if (writeFile.is_open()) {
        for (const auto& outputLine : lines) {
            writeFile << outputLine << "\n";
        }
        writeFile.close();
    }
}

template<typename T>
void Parsing::RegisterField(const std::string& key, T& field, const std::string& value) {
    try {
        if constexpr (std::is_same_v<T, int>) {
            field = std::stoi(value);
        }
        else if constexpr (std::is_same_v<T, float>) {
            field = std::stof(value);
        }
        else if constexpr (std::is_same_v<T, std::string>) {
            field = value;
        }
        else {
            throw std::invalid_argument("Type non supporte");
        }
        std::cout << key << " = " << field << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Erreur lors de la conversion du champ '" << key << "' : " << e.what() << std::endl;
    }
}

std::unordered_map<std::string, DataExtraction> Parsing::GetAllDataFromInventory() {

    std::unordered_map<std::string, DataExtraction> items;
    if (!data.empty()) {
        for (const auto& datas : data) {
            std::cout << "Categorie: " << datas.first << std::endl;
            auto extractItem = GetItemsInformation(datas.first);
            if (!extractItem.empty()) {
                DataExtraction dataExtraction;

                functionMap = {
                    { "type", [&](const std::string& value) { RegisterField("type", dataExtraction.type, value); } },
                    { "id", [&](const std::string& value) { RegisterField("id", dataExtraction.id, value); }},
                    { "quantity", [&](const std::string& value) { RegisterField("quantity", dataExtraction.quantity, value); } },
                    { "damage", [&](const std::string& value) { RegisterField("damage", dataExtraction.damage, value); } },
                    { "durability", [&](const std::string& value) { RegisterField("durability", dataExtraction.durability, value); } },
                    { "resistance", [&](const std::string& value) { RegisterField("resistance", dataExtraction.resistance, value); } }
                };

                for (const auto& item : extractItem) {
                    const std::string& key = item.first;
                    const std::string& value = item.second;

                    if (functionMap.find(key) != functionMap.end()) {
                        functionMap[key](value);
                    }
                    else {
                        std::cout << "Cle inconnue: " << key << std::endl;
                    }
                }

                items[datas.first] = dataExtraction;
            }
        }
    }
    else {
        std::cout << "data vide" << std::endl;
    }

    return items;
}

void Parsing::ShowItemDetail(const DataExtraction& _item) {
    item.clear();
    std::cout << "Item details:" << std::endl;
    if (!_item.type.empty()) item.emplace_back("Type", _item.type);
    if (_item.id != -1) item.emplace_back("ID", _item.id);
    if (_item.quantity != -1) item.emplace_back("Quantity", _item.quantity);
    if (_item.damage != -0.f) item.emplace_back("Damage", _item.damage);
    if (_item.durability != -0.f) item.emplace_back("Durability", _item.durability);
    if (_item.resistance != -0.0f) item.emplace_back("Resitance", _item.resistance);

    listItems.push_back(item);
}

void Parsing::ShowTargetItem(const std::unordered_map<std::string, DataExtraction>& items, const std::string& itemName) {
    auto item = items.find(itemName);
    if (item != items.end()) {
        std::cout << "Item trouve : " << itemName << std::endl;
        ShowItemDetail(item->second);
    }
    else {
        std::cout << "Item " << itemName << " pas trouve" << std::endl;
    }
}

void Parsing::ShowTargetItems()
{
    if (LoadFile()) {

        std::unordered_map<std::string, DataExtraction> items = GetAllDataFromInventory();
        std::vector<std::string> sections = GetAllCategory();
        std::cout << "Toutes les catégories:" << std::endl;
        for (const auto& section : sections) {
            ShowTargetItem(items, section);
        }
    }
    else {
        std::cout << "fichier ini pas trouvé" << std::endl;
    }
}

std::vector<std::vector<std::pair<std::string, ParsingOption>>> Parsing::GetListItems() {
    return listItems;
}

void Parsing::Test()
{
    if (LoadFile()) {

        std::vector<std::string> sections = GetAllCategory();
        std::cout << "Toutes les catégories:" << std::endl;
        for (const auto& section : sections) {
            std::cout << "  " << section << std::endl;
        }

        std::string inventoryName = "inventory_1.item1";
        auto items = GetItemsInformation(inventoryName);

        if (!items.empty()) {
            std::cout << "\nInformations sur l'item " << inventoryName << ":" << std::endl;
            for (const auto& item : items) {
                std::cout << "  " << item.first << " = " << item.second << std::endl;
            }
        }

        std::cout << "\nInformation precise sur l'item " << inventoryName << " pour la cle 'type' : " << GetValueOfItem(inventoryName, "type") << std::endl;

        AddNewData("inventory_1.item3", "type", "ignite");
        Modify("inventory_1.item3", "damage", "10");
    }
    else {
        std::cout << "fichier ini pas trouvé" << std::endl;
    }
}