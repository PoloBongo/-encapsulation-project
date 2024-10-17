#pragma once
#include "Equipment.h"

enum ArmorType
{
	Helmet,
	Chestplate,
	Gloves,
	Leggings,
	Boots
};

class Armor : public Equipment
{
private:
	ArmorType armor_type;
	int health = 0;
	int dodge_rate = 0;
	int resistance = 0;
	int health_regen = 0;
	int luck = 0;

public:
	Armor(ArmorType _armor_type, int _ID, std::string _name, std::string _desc, int _sell_price = 0, int _level = 1,
		int _defense = 0, std::string _skill = "", int _health = 0, int _dodge_rate = 0, int _resistance = 0, int _health_regen = 0,
		int _luck = 0);
	ArmorType GetArmorType() const { return armor_type; }
	int GetHealth() const { return health; }
	int GetDodgeRate() const { return dodge_rate; }
	int GetResistance() const { return resistance; }
	int GetHealthRegen() const { return health_regen; }
	int GetLuck() const { return luck; }
};