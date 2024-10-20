#pragma once
#include <string>

#define DATA_FIELDS(Type) \
    Type(std::string, type, "") \
    Type(std::string, name, "") \
    Type(std::string, description, "") \
    Type(std::string, skill, "") \
    Type(bool, isStackable, false) \
    Type(int, id, -1) \
    Type(int, quantity, -1) \
    Type(int, damage, -1) \
    Type(int, durability, -1) \
    Type(int, resistance, -1) \
    Type(int, sell_price, -1) \
    Type(int, level, -1) \
    Type(int, defense, -1) \
    Type(int, attack, -1) \
    Type(int, attack_speed, -1) \
    Type(int, crit_rate, -1) \
    Type(int, crit_damage, -1) \
    Type(int, accuracy, -1) \
    Type(int, cooldown_reduction, -1) \
    Type(int, life_steal, -1) \
    Type(int, item_type, -1) \
    Type(int, weapon_type, -1) \
    Type(int, armor_type, -1) \
    Type(int, items_count, -1) \
    Type(int, health, -1) \
    Type(int, dodge_rate, -1) \
    Type(int, health_regen, -1) \
    Type(int, luck, -1)

struct DataExtraction {
#define DECLARE_FIELD(type, name, default_value) type name = default_value;
    DATA_FIELDS(DECLARE_FIELD)
#undef DECLARE_FIELD
};