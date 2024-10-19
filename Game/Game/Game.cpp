#include <iostream>
#include "Game.h"
#include "Inventory.h"

int main()
{
	Parsing parsing("inventory.ini");
	std::shared_ptr<Inventory> inventory_test = std::shared_ptr<Inventory>(new Inventory());

	inventory_test->LoadInventory(parsing);

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
	inventory_test->ShowInventory();;
	std::cout << "\nSorting by ArmorType in ascending order.\n\n";
	inventory_test->SortByArmorType();
	inventory_test->ShowInventory();

	inventory_test->ModifyValueOfItem("inventory_1.item5", "crit_damage", "30", parsing);

	return 0;
}