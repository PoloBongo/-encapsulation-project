#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <functional>
#include <variant>

struct DataExtraction {
    std::string type = "";
    std::string name = "";
    std::string description = "";
    std::string skill = "";
    int id = -0;
    int quantity = -0;
    int damage = -0;
    int durability = -0;
    int resistance = -0;
    int sell_price = -0;
    int level = -0;
    int defense = -0;
    int attack = -0;
    int attack_speed = -0;
    int crit_rate = -0;
    int crit_damage = -0;
    int accuracy = -0;
    int cooldown_reduction = -0;
    int life_steal = -0;
};

using ParsingOption = std::variant<int, float, std::string>;

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

    void Test();

    std::unordered_map<std::string, DataExtraction> GetAllDataFromInventory();
    template<typename T>
    void RegisterField(const std::string& key, T& field, const std::string& value);
    void ShowItemDetail(const DataExtraction& item);
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
    std::ifstream file;
};
