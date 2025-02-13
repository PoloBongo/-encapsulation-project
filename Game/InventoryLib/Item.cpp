#include "Item.h"

Item::Item(int _type, int _id, std::string _name,std::string _desc , int _sell_price, bool _isStackable)
{
	type = static_cast<ItemType>(_type);
	id = _id;
	name = _name;
	description = _desc;
	sell_price = _sell_price;
	isStackable = _isStackable;
}

std::string Item::GetItemTypeString(int _item_type)
{
	switch (_item_type)
	{
	case 0:
		return "Weapon";
		break;
	case 1:
		return "Armor";
		break;
	case 2:
		return "Consumable";
		break;
	case 3:
		return "Miscellaneous";
		break;
	default:
		return "Unknown";
		break;
	}
}