#pragma once
#include "Equipment.h"

enum WeaponType
{
	Sword = 0,
	Axe = 1,
	Katana = 2,
	Mace = 3,
	Dagger = 4
};

class Weapon : public Equipment
{
private:
	WeaponType weapon_type;
	int attack = 0;
	int attack_speed = 0;
	int crit_rate = 0;
	int crit_damage = 0;
	int accuracy = 0;
	int cooldown_reduction = 0;
	int life_steal = 0;
public:
	Weapon(int _weapon_type, int _ID, std::string _name, std::string _desc, int _sell_price = 0, int _level = 1,
		int _defense = 0, std::string _skill = "", int _attack = 0, int _attack_speed = 0, int _crit_rate = 0, int _crit_damage = 0,
		int _accuracy = 0, int _cooldown_reduction = 0, int _life_steal = 0);
	~Weapon() = default;
	std::string GetWeaponType() const;
	int GetAttack() const { return attack; }
	int GetAttackSpeed() const { return attack_speed; }
	int GetCritRate() const { return crit_rate; }
	int GetCritDamage() const { return crit_damage; }
	int GetAccuracy() const { return accuracy; }
	int GetCooldownReduction() const { return cooldown_reduction; }
	int GetLifeSteal() const { return life_steal; }
};
