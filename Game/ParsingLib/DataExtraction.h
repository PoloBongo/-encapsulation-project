#pragma once
#include <string>

struct DataExtraction {
    std::string type = "";
    std::string name = "";
    std::string description = "";
    std::string skill = "";
    bool isStackable;
    int id = -0;
    int quantity = -0;
    int damage = -0;
    int durability = -0;
    int resistance = -0;
    int sell_price = -0;
    int level = -0;
    int defense = -0;
    int attack = -0;
    int attack_speed = -0;
    int crit_rate = -0;
    int crit_damage = -0;
    int accuracy = -0;
    int cooldown_reduction = -0;
    int life_steal = -0;
    int item_type = -0;
    int weapon_type = -0;
    int armor_type = -0;
};