#include "Weapon.h"

Weapon::Weapon(WeaponType _weapon_type, int _ID, std::string _name, std::string _desc, int _sell_price, int _level,
	int _defense, std::string _skill, int _attack, int _attack_speed, int _crit_rate, int _crit_damage,
	int _accuracy, int _cooldown_reduction , int _life_steal)
	: Equipment(ItemType::item_Weapon, _ID, _name, _desc, _sell_price, _level, _defense, _skill)
{
	weapon_type = _weapon_type;
	attack = _attack;
	attack_speed = attack_speed;
	crit_rate = _crit_rate;
	crit_damage = _crit_damage;
	accuracy = _accuracy;
	cooldown_reduction = _cooldown_reduction;
	life_steal = _life_steal;
}
