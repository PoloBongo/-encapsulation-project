#include "Armor.h"

Armor::Armor(int _armor_type, int _ID, std::string _name, std::string _desc, int _sell_price, int _level,
	int _defense, std::string _skill, int _health, int _dodge_rate, int _resistance, int _health_regen,
	int _luck)
	: Equipment(ItemType::item_Armor, _ID, _name, _desc, _sell_price, _level, _defense, _skill)
{
	armor_type = static_cast<ArmorType>(_armor_type);
	health = _health;
	dodge_rate = _dodge_rate;
	resistance = _resistance;
	health_regen = _health_regen;
	luck = _luck;
}
