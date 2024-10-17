#pragma once
#include <vector>
#include <algorithm>
#include "Weapon.h"
#include "Armor.h"

class Inventory
{
private:
	std::vector<std::pair<std::shared_ptr<Item>, int>> items;

public:
	Inventory();
	~Inventory() = default;
	void ShowInventory() const;

	void AddItem(const std::shared_ptr<Item>& item, int _amount = 1);
	void RemoveItem(const std::shared_ptr<Item>& item, int _amount = 1);
	void SortByID(bool _ascending = true);
	void SortByName(bool _ascending = true);
};