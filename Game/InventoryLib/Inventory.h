#pragma once
#include <vector>
#include <algorithm>
#include "ItemBuild.h"

class Inventory
{
private:
	std::vector<std::pair<std::shared_ptr<Item>, int>> items;
	std::unordered_map<std::string, std::function<void(const std::string&)>> functionMap;
	void CreateItem(std::vector<std::vector<std::pair<std::string, ParsingOption>>>& _listItems);

public:
	Inventory();
	~Inventory() = default;
	void ShowInventory() const;

	void AddItem(const std::shared_ptr<Item>& item, int _amount = 1);
	void RemoveItem(const std::shared_ptr<Item>& item, int _amount = 1);
	void SortByID(bool _ascending = true);
	void SortByName(bool _ascending = true);

	void LoadInventory(const std::string& _filePath);
};