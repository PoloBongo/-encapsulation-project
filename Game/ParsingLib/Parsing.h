#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <functional>
#include <variant>
#include "DataExtraction.h"

using ParsingOption = std::variant<int, float, std::string, bool>;

class Parsing {
public:
    Parsing() {};
    Parsing(const std::string& filePath);
    bool LoadFile();

    std::vector<std::string> GetAllCategory() const;
    std::unordered_map<std::string, std::string> GetItemsInformation(const std::string& sectionName) const;
    std::string GetValueOfItem(const std::string& sectionName, const std::string& key) const;

    void AddNewData(const std::string& category, const std::string& key, const std::string& value);
    void Modify(const std::string& category, const std::string& key, const std::string& value);

    std::unordered_map<std::string, DataExtraction> GetAllDataFromInventory();

    template<typename T>
    void RegisterField(const std::string& key, T& field, const std::string& value) {
        try {
            if constexpr (std::is_same_v<T, int>) {
                field = std::stoi(value);
            }
            else if constexpr (std::is_same_v<T, float>) {
                field = std::stof(value);
            }
            else if constexpr (std::is_same_v<T, bool>) {
                if (value == "true") {
                    field = true;
                }
                else if (value == "false") {
                    field = false;
                }
                else {
                    throw std::invalid_argument("Valeur non valide pour un booléen");
                }
            }
            else if constexpr (std::is_same_v<T, std::string>) {
                field = value;
            }
            else {
                throw std::invalid_argument("Type non supporté");
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Erreur lors de la conversion du champ '" << key << "' : " << e.what() << std::endl;
        }
    }

    void SetItemDetail(const DataExtraction& item);
    void ShowTargetItem(const std::unordered_map<std::string, DataExtraction>& items, const std::string& itemName);
    void ShowTargetItems();

    std::vector<std::vector<std::pair<std::string, ParsingOption>>> GetListItems();
private:
    std::vector<std::vector<std::pair<std::string, ParsingOption>>> listItems;
    std::vector<std::pair<std::string, ParsingOption>> item;
    std::unordered_map<std::string, std::function<void(const std::string&)>> functionMap;
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> data;
    std::string Trim(const std::string &str);
    std::string filePath;
    std::string newType;
    std::ifstream file;
};
