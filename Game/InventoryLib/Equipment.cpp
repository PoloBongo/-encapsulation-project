#include "Equipment.h"

Equipment::Equipment(int _type, int _ID, std::string _name, std::string _desc, int _sell_price, bool _isStackable, int _level, int _defense, std::string _skill)
	: Item(_type, _ID, _name, _desc, _sell_price, _isStackable)
{
	level = _level;
	defense = _defense;
	skill = _skill;
}

