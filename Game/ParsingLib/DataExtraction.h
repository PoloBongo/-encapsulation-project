#pragma once
#include <string>

struct DataExtraction {
    std::string type = "";
    std::string name = "";
    std::string description = "";
    std::string skill = "";
    bool isStackable;
    int id = -1;
    int quantity = -1;
    int damage = -1;
    int durability = -1;
    int resistance = -1;
    int sell_price = -1;
    int level = -1;
    int defense = -1;
    int attack = -1;
    int attack_speed = -1;
    int crit_rate = -1;
    int crit_damage = -1;
    int accuracy = -1;
    int cooldown_reduction = -1;
    int life_steal = -1;
    int item_type = -1;
    int weapon_type = -1;
    int armor_type = -1;
    int items_count = -1;
    int health = -1;
    int dodge_rate = -1;
    int health_regen = -1;
    int luck = -1;
};