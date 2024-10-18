#include <iostream>
#include "Game.h"
#include "Inventory.h"

int main()
{
	//parsing.ShowTargetItems();
	//auto sections = parsing.GetListItems();
	//for (const auto& section : sections) {
	//	std::cout << "Item details:" << std::endl;
	//	for (const auto& [key, value] : section) {
	//		std::cout << key << ": ";
	//		std::visit([](auto&& arg) {
	//			std::cout << arg << std::endl;
	//			}, value);
	//	}
	//}
  
  
	std::shared_ptr<Item> HealPot = std::shared_ptr<Item>(new Item(ItemType::item_Consumable, 1, "Health Potion", "Heal 5 health.", 10));
	std::shared_ptr<Weapon> WoodenSword = std::shared_ptr<Weapon>(new Weapon(WeaponType::Sword, 2, "Wooden Sword", "A basic wooden sword.", 19,2,0,"",5,2,0,0,0,0,0));
	std::shared_ptr<Armor> LeatherChestplate = std::shared_ptr<Armor>(new Armor(ArmorType::Chestplate, 4, "Leather Chestplate", "A leather chestplate.", 20, 4, 5, "", 10, 0, 1, 1, 0));
	std::shared_ptr<Weapon> WoodenAxe = std::shared_ptr<Weapon>(new Weapon(WeaponType::Axe, 3, "Wooden Axe", "A basic wooden axe.", 18, 1, 0, "", 8, 1, 0, 0, 0, 0, 0));

	std::shared_ptr<Inventory> inventory_test = std::shared_ptr<Inventory>(new Inventory());

	inventory_test->AddItem(HealPot);
	inventory_test->AddItem(WoodenSword);
	inventory_test->AddItem(LeatherChestplate);
	inventory_test->AddItem(WoodenAxe);

	inventory_test->LoadInventory("test.ini");

	inventory_test->ShowInventory();
	std::cout << "\nSorting by name.\n\n";
	inventory_test->SortByName();
	inventory_test->ShowInventory();
	std::cout << "\nSorting by ID in descending order.\n\n";
	inventory_test->SortByID(false);
	inventory_test->ShowInventory();
	std::cout << "\nSorting by ID in ascending order.\n\n";
	inventory_test->SortByID();
	inventory_test->ShowInventory();
	std::cout << "\nSorting by SellPrice in ascending order.\n\n";
	inventory_test->SortByPrice();
	inventory_test->ShowInventory();
	std::cout << "\nSorting by Levels in descending order.\n\n";
	inventory_test->SortByLevel(false);
	inventory_test->ShowInventory();
	std::cout << "\nSorting by Attack in ascending order.\n\n";
	inventory_test->SortByAttack();
	inventory_test->ShowInventory();
	std::cout << "\nSorting by Defense in descending order.\n\n";
	inventory_test->SortByDefense(false);
	inventory_test->ShowInventory();
	std::cout << "\nSorting by Type in ascending order.\n\n";
	inventory_test->SortByType();
	inventory_test->ShowInventory();
	std::cout << "\nSorting by WeaponType in descending order.\n\n";
	inventory_test->SortByWeaponType(false);
	inventory_test->ShowInventory();
	std::cout << "\nSorting by ArmorType in ascending order.\n\n";
	inventory_test->SortByArmorType();
	inventory_test->ShowInventory();
	std::cout << "\nSorting by Attack Speed in ascending order.\n\n";
	inventory_test->SortByAttackSpeed();
	inventory_test->ShowInventory();
	std::cout << "\nSorting by Critical Rate in descending order.\n\n";
	inventory_test->SortByCritRate(false);
	inventory_test->ShowInventory();
	std::cout << "\nSorting by Critical Damage in ascending order.\n\n";
	inventory_test->SortByCritDamage();
	inventory_test->ShowInventory();
	std::cout << "\nSorting by Accuracy in descending order.\n\n";
	inventory_test->SortByAccuracy(false);
	inventory_test->ShowInventory();
	std::cout << "\nSorting by Cooldown Reduction in ascending order.\n\n";
	inventory_test->SortByCooldownReduction();
	inventory_test->ShowInventory();
	std::cout << "\nSorting by Life Steal in descending order.\n\n";
	inventory_test->SortByLifeSteal(false);
	inventory_test->ShowInventory();
	std::cout << "\nSorting by Health Regen in ascending order.\n\n";
	inventory_test->SortByHealthRegen();
	inventory_test->ShowInventory();
	std::cout << "\nSorting by Luck in ascending order.\n\n";
	inventory_test->SortByLuck();
	inventory_test->ShowInventory();
	return 0;
}