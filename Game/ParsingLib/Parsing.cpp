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
                std::cout << key << " : " << value << std::endl;
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

std::map<std::string, std::string> Parsing::GetItemsInformation(const std::string& sectionName) const {
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

DataExtraction Parsing::GetAllDataFromInventory()
{
    std::string currentSection;
    std::string line;
    DataExtraction* dataExtraction = new DataExtraction();
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

    return DataExtraction();
}

void Parsing::Test()
{
    Parsing parsing("test.ini");

    if (parsing.LoadFile()) {

        std::vector<std::string> sections = parsing.GetAllCategory();
        std::cout << "Toutes les catégories:" << std::endl;
        for (const auto& section : sections) {
            std::cout << "  " << section << std::endl;
        }

        std::string inventoryName = "inventory_1.item1";
        auto items = parsing.GetItemsInformation(inventoryName);

        if (!items.empty()) {
            std::cout << "\nInformations sur l'item " << inventoryName << ":" << std::endl;
            for (const auto& item : items) {
                std::cout << "  " << item.first << " = " << item.second << std::endl;
            }
        }

        std::cout << "\nInformation precise sur l'item " << inventoryName << " pour la cle 'type' : " << parsing.GetValueOfItem(inventoryName, "type") << std::endl;

        parsing.AddNewData("inventory_1.item3", "type", "ignite");
        parsing.Modify("inventory_1.item3", "damage", "10");
    }
    else {
        std::cout << "fichier ini pas trouvé" << std::endl;
    }
}