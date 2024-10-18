#pragma once
#include <iostream>

enum ItemType
{
	item_Weapon = 0,
	item_Armor = 1,
	item_Consumable = 2,
	item_Miscellaneous = 3
};

class Item
{
private:
	ItemType type;
	int id = 0;
	std::string name = "default_name";
	std::string description = "default_description";
	int sell_price = 0;
	bool isStackable = true;

public:
	Item(int _type, int _id, std::string _name, std::string _desc, int _sell_price, bool _isStackable = true);
	virtual ~Item() = default;
	int GetID() const { return id; }
	bool GetStackable() const { return isStackable; }
	std::string GetName() const { return name; }
	std::string GetDescription() const { return description; }
	int GetSellPrice() const { return sell_price; }
	ItemType GetItemType() const { return type; }
};