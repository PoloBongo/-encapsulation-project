#pragma once
#include "Item.h"
//#include "Skill.h"

class Equipment : public Item
{
private:
	int level = 1;
	int defense = 0;
	std::string skill = ""; //Equipment can have
protected:
	//void SetSkill(std::string _skill) { skill = _skill; }
public:
	Equipment(ItemType _type, int _ID, std::string _name,std::string _desc, int _sell_price = 0, int _level = 1, int _defense = 0, std::string _skill = "");
	~Equipment() = default;
	int GetBonusLevel() const { return level; }
	int GetBonusDefense() const { return defense; }
	std::string GetSkill() const { return skill; }
};