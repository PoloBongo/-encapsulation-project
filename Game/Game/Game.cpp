#include "Game.h"
#include "Parsing.h"

int main()
{
	Parsing parsing("test.ini");
	/*std::unordered_map<std::string, DataExtraction> items = parsing.GetAllDataFromInventory();

	std::vector<std::string> sections = parsing.GetAllCategory();
	std::cout << "Toutes les catégories:" << std::endl;
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
	return 0;
}