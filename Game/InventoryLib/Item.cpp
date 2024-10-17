#include "Item.h"

Item::Item(ItemType _type, int _id, std::string _name,std::string _desc , int _sell_price)
{
	type = _type;
	id = _id;
	name = _name;
	description = _desc;
	sell_price = _sell_price;
}