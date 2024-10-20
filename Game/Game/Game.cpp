#include <iostream>
#include "Game.h"
#include "Inventory.h"

int main()
{
	ParsingInventory parsing("inventory.ini");
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
	std::cout << "\nAdd filter by Katana.\n\n";
	inventory_test->AddItemFilter(ItemType::item_Weapon,WeaponType::Katana);
	inventory_test->FilterInventory();
	inventory_test->ShowInventory();
	std::cout << "\nSorting by Attack in Descending order.\n\n";
	inventory_test->SortByAttack(false);
	inventory_test->ShowInventory();
	std::cout << "\nAdd filter by Armor.\n\n";
	inventory_test->AddItemFilter(ItemType::item_Armor);
	inventory_test->FilterInventory();
	inventory_test->ShowInventory();
	inventory_test->PrintFilterList();
	std::cout << "\nRemove filter by Katana.\n\n";
	inventory_test->RemoveItemFilter(ItemType::item_Weapon, WeaponType::Katana);
	inventory_test->FilterInventory();
	inventory_test->ShowInventory();
	std::cout << "\nReset All Filters.\n\n";
	inventory_test->ResetAllFilters();
	inventory_test->ShowInventory();

	inventory_test->ModifyValueOfItem("inventory_1.item5", "crit_damage", "30", parsing);

	return 0;
}