#include <iostream>
#include "Game.h"
#include "Parsing.h"
#include "Inventory.h"

int main()
{
	Parsing parsing("test.ini");
	/*std::unordered_map<std::string, DataExtraction> items = parsing.GetAllDataFromInventory();

	std::vector<std::string> sections = parsing.GetAllCategory();
	std::cout << "Toutes les cat�gories:" << std::endl;
	for (const auto& section : sections) {
		std::cout << "good" << std::endl;
		parsing.ShowTargetItem(items, section);
	}*/

	//parsing.Test();
	//std::string type = parsing.GetAllDataFromInventory().typeValue;
	//float damage = parsing.GetAllDataFromInventory().damageValue;
	//std::cout << "TYPE : " << type << std::endl;
	//std::cout << "DAMAGE : " << damage << std::endl;

	parsing.ShowTargetItems();
	auto sections = parsing.GetListItems();
	for (const auto& section : sections) {
		std::cout << "Item details:" << std::endl;
		for (const auto& [key, value] : section) {
			std::cout << key << ": ";
			std::visit([](auto&& arg) {
				std::cout << arg << std::endl;
				}, value);
		}
	}
  
  
  std::shared_ptr<Item> HealPot = std::shared_ptr<Item>(new Item(ItemType::item_Consumable, 1, "Health Potion", "Heal 5 health.", 10));
	std::shared_ptr<Weapon> WoodenSword = std::shared_ptr<Weapon>(new Weapon(WeaponType::Sword, 2, "Wooden Sword", "A basic wooden sword.", 19,2,0,"",5,2,0,0,0,0,0));
	std::shared_ptr<Armor> LeatherChestplate = std::shared_ptr<Armor>(new Armor(ArmorType::Chestplate, 4, "Leather Chestplate", "A leather chestplate.", 20, 4, 5, "", 10, 0, 1, 1, 0));
	std::shared_ptr<Weapon> WoodenAxe = std::shared_ptr<Weapon>(new Weapon(WeaponType::Axe, 3, "Wooden Axe", "A basic wooden axe.", 18, 1, 0, "", 8, 1, 0, 0, 0, 0, 0));

	std::shared_ptr<Inventory> inventory_test = std::shared_ptr<Inventory>(new Inventory());
	inventory_test->AddItem(HealPot);
	inventory_test->AddItem(WoodenSword);
	inventory_test->AddItem(LeatherChestplate);
	inventory_test->AddItem(WoodenAxe);

	inventory_test->ShowInventory();
	std::cout << "Sorting by name.\n\n";
	inventory_test->SortByName();
	inventory_test->ShowInventory();
	std::cout << "Sorting by ID in descending order.\n\n";
	inventory_test->SortByID(false);
	inventory_test->ShowInventory();
	std::cout << "Sorting by ID in ascending order.\n\n";
	inventory_test->SortByID();
	inventory_test->ShowInventory();
	return 0;
}