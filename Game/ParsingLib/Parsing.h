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
    Parsing(const std::string& _filePath);
    bool LoadFile();

    std::vector<std::string> GetAllCategory() const;
    std::unordered_map<std::string, std::string> GetItemsInformation(const std::string& _categoryName) const;
    std::string GetValueOfItem(const std::string& _categoryName, const std::string& _key) const;

    void AddNewData(const std::string& _category, const std::string& _key, const std::string& _value);
    void Modify(const std::string& _category, const std::string& _key, const std::string& _value);

    std::unordered_map<std::string, DataExtraction> GetAllDataFromInventory();

    void SetItemDetail(const DataExtraction& _item);
    void ShowTargetItem(const std::unordered_map<std::string, DataExtraction>& _items, const std::string& _itemName);
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
    int newID;
    std::ifstream file;
};