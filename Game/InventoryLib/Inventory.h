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
	void PrintWeapon(const std::shared_ptr<Weapon>& _weapon, const int _quantity, const int _num);
	void PrintArmor(const std::shared_ptr<Armor>& _armor, const int _quantity, const int _num);
	void PrintItem(const std::shared_ptr<Item>& _item, const int _quantity, const int _num, const std::string _color);
	void PrintEquipment(const std::shared_ptr<Equipment>& _equip);
	std::unordered_map<std::string, std::function<void(const std::string&)>> functionMap;
	void CreateItem(std::vector<std::vector<std::pair<std::string, ParsingOption>>>& _listItems);

public:
	Inventory();
	~Inventory() = default;
	void ShowInventory();

	void AddItem(const std::shared_ptr<Item>& item, int _amount = 1);
	void RemoveItem(const std::shared_ptr<Item>& item, int _amount = 1);
	void LoadInventory(const std::string& _filePath);

	//Sort functions
	void SortByID(bool _ascending = true);
	void SortByName(bool _ascending = true);
	void SortByPrice(bool _ascending = true);
	void SortByLevel(bool _ascending = true);
	void SortByAttack(bool _ascending = true);
	void SortByDefense(bool _ascending = true);
	void SortByType(bool _ascending = true);
	void SortByWeaponType(bool _ascending = true);
	void SortByArmorType(bool _ascending = true);


};