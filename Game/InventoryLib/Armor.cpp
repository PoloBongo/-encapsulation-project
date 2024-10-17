#include "Armor.h"

Armor::Armor(ArmorType _armor_type, int _ID, std::string _name, std::string _desc, int _sell_price, int _level,
	int _defense, std::string _skill, int _health, int _dodge_rate, int _resistance, int _health_regen,
	int _luck)
	: Equipment(ItemType::item_Armor, _ID, _name, _desc, _sell_price, _level, _defense, _skill)
{
	armor_type = _armor_type;
	health = _health;
	dodge_rate = _dodge_rate;
	resistance = _resistance;
	health_regen = _health_regen;
	luck = _luck;
}

std::string Armor::GetArmorType() const
{
	switch (armor_type)
	{
		case ArmorType::Helmet:
			return "Helmet";
		case ArmorType::Chestplate:
			return "Chestplate";
		case ArmorType::Gloves:
			return "Gloves";
		case ArmorType::Leggings:
			return "Leggings";
		case ArmorType::Boots:
			return "Boots";
		default:
			return "Unknown";
	}
}
