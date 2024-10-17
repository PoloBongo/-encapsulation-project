#pragma once
#include <iostream>

enum ItemType
{
	item_Weapon,
	item_Armor,
	item_Consumable,
	item_Miscellaneous
};

class Item
{
private:
	ItemType type;
	int id = 0;
	std::string name = "default_name";
	std::string description = "default_description";
	int sell_price = 0;

public:
	Item(ItemType _type, int _id, std::string _name, std::string _desc, int _sell_price);
	~Item() = default;
	int GetID() const { return id; }
	std::string GetName() const { return name; }
	std::string GetDescription() const { return description; }
	int GetSellPrice() const { return sell_price; }
	ItemType GetItemType() const { return type; }
};