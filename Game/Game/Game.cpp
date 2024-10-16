#include <iostream>
#include "Game.h"
#include "Inventory.h"

int main()
{
	std::shared_ptr<Inventory> inventory_test = std::shared_ptr<Inventory>(new Inventory());
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
}