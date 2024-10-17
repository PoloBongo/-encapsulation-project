#include "Inventory.h"

template <typename T>
void AppendIfNotZero(std::ostream& os, const std::string& label, T value) {
	if (value != 0) {
		os << " " << label << ": " << value << " ";
	}
}

struct CompareByID {
	bool ascending = true;
	CompareByID(bool _ascending) : ascending(_ascending) {};
	bool operator()(const std::pair<std::shared_ptr<Item>, int>& a, const std::pair<std::shared_ptr<Item>, int>& b)
	{
		return ascending ? (a.first->GetID() < b.first->GetID()) : (a.first->GetID() > b.first->GetID());
	};
};

struct CompareByName {
	bool ascending = true;
	CompareByName(bool _ascending) : ascending(_ascending) {};
	bool operator()(const std::pair<std::shared_ptr<Item>, int>& a, const std::pair<std::shared_ptr<Item>, int>& b)
	{
		return ascending ? (a.first->GetName() < b.first->GetName()) : (a.first->GetName() > b.first->GetName());
	};
};

struct CompareByPrice {
	bool ascending = true;
	CompareByPrice(bool _ascending) : ascending(_ascending) {};
	bool operator()(const std::pair<std::shared_ptr<Item>, int>& a, const std::pair<std::shared_ptr<Item>, int>& b)
	{
		return ascending ? (a.first->GetSellPrice() < b.first->GetSellPrice()) : (a.first->GetSellPrice() > b.first->GetSellPrice());
	};
};

struct CompareByLevel {
	bool ascending;
	CompareByLevel(bool _ascending) : ascending(_ascending) {}

	bool operator()(const std::pair<std::shared_ptr<Item>, int>& a, const std::pair<std::shared_ptr<Item>, int>& b) {
		auto equipA = std::dynamic_pointer_cast<Equipment>(a.first);
		auto equipB = std::dynamic_pointer_cast<Equipment>(b.first);
		if (equipA && equipB) {
			return ascending ? (equipA->GetLevel() < equipB->GetLevel()) : (equipA->GetLevel() > equipB->GetLevel());
		}
		if (equipA) return true;

		return false; // If either is not Equipment, they are considered equal for sorting purposes
	}
};

Inventory::Inventory()
{
	items = std::vector<std::pair<std::shared_ptr<Item>, int>>();
}


void Inventory::ShowInventory() 
{
	std::cout << "Inventory: " << std::endl;
	for (int i = 0; i < items.size(); i++)
	{
		switch (items[i].first->GetItemType())
		{
			case ItemType::item_Weapon:
				PrintWeapon(std::dynamic_pointer_cast<Weapon>(items[i].first),items[i].second,i);
				break;
			case ItemType::item_Armor:
				PrintArmor(std::dynamic_pointer_cast<Armor>(items[i].first), items[i].second,i);
				break;
			default:
				PrintItem(items[i].first, items[i].second,i,WHITE);
				break;
		}
		std::cout << std::endl;
	}
}

void Inventory::PrintWeapon(const std::shared_ptr<Weapon>& _weapon,const int _quantity, const int _num)
{
	PrintItem(_weapon, _quantity, _num,RED);
	PrintEquipment(_weapon);

	std::cout << " WeaponType: " << _weapon->GetWeaponType() << " ; ";
	AppendIfNotZero(std::cout, "Attack", _weapon->GetAttack());
	AppendIfNotZero(std::cout, "Attack Speed", _weapon->GetAttackSpeed());
	AppendIfNotZero(std::cout, "Critical Rate", _weapon->GetCritRate());
	AppendIfNotZero(std::cout, "Critical Damage", _weapon->GetCritDamage());
	AppendIfNotZero(std::cout, "Accuracy", _weapon->GetAccuracy());
	AppendIfNotZero(std::cout, "Cooldown Reduction", _weapon->GetCooldownReduction());
	AppendIfNotZero(std::cout, "Life Steal", _weapon->GetLifeSteal());
	std::cout << std::endl;
}

void Inventory::PrintArmor(const std::shared_ptr<Armor>& _armor, const int _quantity, const int _num)
{
	PrintItem(_armor, _quantity, _num,BLUE);
	PrintEquipment(_armor);

	std::cout << " ArmorType: " << _armor->GetArmorType() << " ; ";
	AppendIfNotZero(std::cout, "Health", _armor->GetHealth());
	AppendIfNotZero(std::cout, "Dodge Rate", _armor->GetDodgeRate());
	AppendIfNotZero(std::cout, "Resistance", _armor->GetResistance());
	AppendIfNotZero(std::cout, "Health Regen", _armor->GetHealthRegen());
	AppendIfNotZero(std::cout, "Luck", _armor->GetLuck());
	std::cout << std::endl;
	
}

void Inventory::PrintItem(const std::shared_ptr<Item>& _item, const int _quantity, const int _num, const std::string _color)
{
	std::cout << _num << ") " << "ID: " << _item->GetID() << _color <<" Name: " << _item->GetName() << RESET << std::endl << " Description: " << _item->GetDescription() << std::endl
		<< " Amount: " << _quantity << " Price: " << _item->GetSellPrice() << std::endl;
}

void Inventory::PrintEquipment(const std::shared_ptr<Equipment>& _equipment)
{
	AppendIfNotZero(std::cout, "Level", _equipment->GetLevel());
	AppendIfNotZero(std::cout, "Defense", _equipment->GetDefense());
	std::cout << " Skill :" << _equipment->GetSkill() << std::endl;
}



void Inventory::AddItem(const std::shared_ptr<Item>& _item, int _amount)
{
	for (int i = 0; i < items.size(); i++)
	{
		if (items[i].first->GetID() == _item->GetID())
		{
			items[i].second += _amount;
			return;
		}
	}
	items.push_back(std::make_pair(_item, _amount));
}

void Inventory::RemoveItem(const std::shared_ptr<Item>& _item, int _amount)
{
	for (int i = 0; i < items.size(); i++)
	{
		if (items[i].first->GetID() == _item->GetID())
		{
			items[i].second -= _amount;
			if (items[i].second == 0)
			{
				items.erase(items.begin() + i);
			}
			return;
		}
	}
}

void Inventory::SortByID(bool _ascending)
{
	std::sort(items.begin(), items.end(), CompareByID(_ascending));
}

void Inventory::SortByName(bool _ascending)
{
	std::sort(items.begin(), items.end(), CompareByName(_ascending));
}

void Inventory::SortByPrice(bool _ascending)
{
	std::sort(items.begin(), items.end(), CompareByPrice(_ascending));
}

void Inventory::SortByLevel(bool _ascending)
{
	std::sort(items.begin(), items.end(), CompareByLevel(_ascending));
}
void Inventory::LoadInventory(const std::string& _filePath)
{
	Parsing parsing(_filePath);

	parsing.ShowTargetItems();
	auto sections = parsing.GetListItems();

	CreateItem(sections);
}

void Inventory::CreateItem(std::vector<std::vector<std::pair<std::string, ParsingOption>>>& _listItems) {
	ItemBuild itemBuild;
    for (const auto& listItem : _listItems) {
        std::string type;

		// stock le type pour le transmettre � "ItemBuild" qui pourra d�terminer c'est quel type d'item
		// puis traiter en fonction du type d'item les valeurs � attribu�
        for (const auto& [key, value] : listItem) {
            std::visit([&](auto&& arg) {
                if (key == "type") {
                    if constexpr (std::is_same_v<std::decay_t<decltype(arg)>, std::string>) {
                        type = arg;
                    }
                }
            }, value);
        }

		auto item = itemBuild.CreateItemByType(type, listItem);
		if (item) {
			AddItem(item);
		}
    }
}