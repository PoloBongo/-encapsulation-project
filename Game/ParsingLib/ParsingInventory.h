#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <functional>
#include <variant>
#include "DataExtraction.h"

using ParsingOption = std::variant<int, float, std::string, bool, double>;

class ParsingInventory {
public:
    ParsingInventory() {};
    ParsingInventory(const std::string& _filePath);
    bool LoadFile();

    std::vector<std::string> GetAllCategory() const;
    std::unordered_map<std::string, std::string> GetItemsInformation(const std::string& _categoryName) const;
    std::string GetValueOfItem(const std::string& _categoryName, const std::string& _key) const;

    std::unordered_map<std::string, DataExtraction> GetAllDataFromInventory();

    void SetItemDetail(const DataExtraction& _item);
    void ShowTargetItem(const std::unordered_map<std::string, DataExtraction>& _items, const std::string& _itemName);
    void ShowTargetItems();

    std::vector<std::vector<std::pair<std::string, ParsingOption>>> GetListItems();
    std::string GetFilePath() { return filePath; }
private:
    std::vector<std::vector<std::pair<std::string, ParsingOption>>> listItems;
    std::vector<std::pair<std::string, ParsingOption>> item;
    std::unordered_map<std::string, std::function<void(const std::string&)>> functionMap;
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> data;
    std::string filePath;
    std::string newType;
    int newID;
    std::ifstream file;

    std::string Trim(const std::string& str);
    void SetFilePath(const std::string _filePath) { filePath = _filePath; }
};