#pragma once
#include <vector>
#include <algorithm>
#include "ItemBuild.h"

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      
#define RED     "\033[31m"      
#define GREEN   "\033[32m"      
#define YELLOW  "\033[33m"    
#define BLUE    "\033[34m"     
#define MAGENTA "\033[35m"    
#define CYAN    "\033[36m"     
#define WHITE   "\033[37m"     

class Inventory
{
private:
	std::vector<std::pair<std::shared_ptr<Item>, int>> items;
	std::vector<std::pair<std::shared_ptr<Item>, int>> items_filtered;
	std::vector<ItemType> filters;

	std::unordered_map<std::string, std::function<void(const std::string&)>> functionMap;
	void CreateItem(std::vector<std::vector<std::pair<std::string, ParsingOption>>>& _listItems);

	void PrintWeapon(const std::shared_ptr<Weapon>& _weapon, const int _quantity, const int _num);
	void PrintArmor(const std::shared_ptr<Armor>& _armor, const int _quantity, const int _num);
	void PrintItem(const std::shared_ptr<Item>& _item, const int _quantity, const int _num, const std::string _color);
	void PrintEquipment(const std::shared_ptr<Equipment>& _equip);
	void RemoveFilteredItemFromInventory(std::shared_ptr<Item>&);
public:
	Inventory();
	~Inventory() = default;
	void ShowInventory();
	void ShowInventoryTemp();

	void AddItem(const std::shared_ptr<Item>& item, int _amount = 1);
	void RemoveItem(const std::shared_ptr<Item>& item, int _amount = 1);
	void LoadInventory(Parsing& _parsing);
	void ModifyValueOfItem(const std::string& _category, const std::string& _key, const std::string& _value, Parsing& _parsing);

	//Filter functions
	void AddItemTypeFilter(ItemType _itemType);
	void RemoveItemTypeFilter(ItemType _itemType);
	void FilterInventory();

	//Sort functions
	void SortByID(bool _ascending = true);
	void SortByName(bool _ascending = true);
	void SortByType(bool _ascending = true);
	void SortByWeaponType(bool _ascending = true);
	void SortByArmorType(bool _ascending = true);
	void SortByPrice(bool _ascending = true);
	void SortByLevel(bool _ascending = true);
	void SortByDefense(bool _ascending = true);
	void SortByAttack(bool _ascending = true);
	void SortByAttackSpeed(bool _ascending = true);
	void SortByCritRate(bool _ascending = true);
	void SortByCritDamage(bool _ascending = true);
	void SortByAccuracy(bool _ascending = true);
	void SortByCooldownReduction(bool _ascending = true);
	void SortByLifeSteal(bool _ascending = true);
	void SortByHealth(bool _ascending = true);
	void SortByDodgeRate(bool _ascending = true);
	void SortByResistance(bool _ascending = true);
	void SortByHealthRegen(bool _ascending = true);
	void SortByLuck(bool _ascending = true);
	void SortByQuantity(bool _ascending = true);

};