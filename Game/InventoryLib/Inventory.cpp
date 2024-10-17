#include "Inventory.h"

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

Inventory::Inventory()
{
	items = std::vector<std::pair<std::shared_ptr<Item>, int>>();
}


void Inventory::ShowInventory() const
{
	std::cout << "Inventory: " << std::endl;
	for (int i = 0; i < items.size(); i++)
	{
		std::cout << items[i].first->GetName() << " x" << items[i].second << std::endl << std::endl;
	}
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
