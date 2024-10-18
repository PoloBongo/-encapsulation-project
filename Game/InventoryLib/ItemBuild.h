#pragma once
#include <memory>
#include "Parsing.h"
#include "Weapon.h"
#include "Armor.h"

class ItemBuild {
private:
    // const std::vector<std::pair<std::string, ParsingOption>> représente toutes les propriétés de l'item
    std::unordered_map<std::string, std::function<std::shared_ptr<Item>(const std::vector<std::pair<std::string, ParsingOption>>&)>>
        // chaque type d'item à une fonction lambda associé qui exécutera le constructeur de l'item en question
        createItem = {
            {"Consumable", [&](const auto& properties) {
                return std::make_shared<Item>(
                    GetValueOrDefault<int>("item_type", properties),
                    GetValueOrDefault<int>("id", properties),
                    GetValueOrDefault<std::string>("name", properties),
                    GetValueOrDefault<std::string>("description", properties),
                    GetValueOrDefault<int>("sell_price", properties),
                    GetValueOrDefault<bool>("isStackable", properties)
                );
            }},
            {"Weapon", [&](const auto& properties) {
                return std::make_shared<Weapon>(
                    GetValueOrDefault<int>("weapon_type", properties),
                    GetValueOrDefault<int>("id", properties),
                    GetValueOrDefault<std::string>("name", properties),
                    GetValueOrDefault<std::string>("description", properties),
                    GetValueOrDefault<int>("sell_price", properties),
                    GetValueOrDefault<bool>("isStackable", properties),
                    GetValueOrDefault<int>("level", properties),
                    GetValueOrDefault<int>("defense", properties),
                    GetValueOrDefault<std::string>("skill", properties),
                    GetValueOrDefault<int>("attack", properties),
                    GetValueOrDefault<int>("attack_speed", properties),
                    GetValueOrDefault<int>("crit_rate", properties),
                    GetValueOrDefault<int>("crit_damage", properties),
                    GetValueOrDefault<int>("accuracy", properties),
                    GetValueOrDefault<int>("cooldown_reduction", properties),
                    GetValueOrDefault<int>("life_steal", properties)
                );
            }},
            {"Armor", [&](const auto& properties) {
                return std::make_shared<Armor>(
                    GetValueOrDefault<int>("armor_type", properties),
                    GetValueOrDefault<int>("id", properties),
                    GetValueOrDefault<std::string>("name", properties),
                    GetValueOrDefault<std::string>("description", properties),
                    GetValueOrDefault<int>("sell_price", properties),
                    GetValueOrDefault<bool>("isStackable", properties),
                    GetValueOrDefault<int>("level", properties),
                    GetValueOrDefault<int>("defense", properties),
                    GetValueOrDefault<std::string>("skill", properties),
                    GetValueOrDefault<int>("health", properties),
                    GetValueOrDefault<int>("dodge_rate", properties),
                    GetValueOrDefault<int>("resitance", properties),
                    GetValueOrDefault<int>("health_regen", properties),
                    GetValueOrDefault<int>("luck", properties)
          );
        }}
    };

    // _key return le type de la valeur ( id, name, health ect... )
    // _item contient chaque propriété de l'item par exemple id = 1
    // _defaultValue permet de mettre une valeur par default au cas où le type n'est pas présent
    template <typename T>
    static T GetValueOrDefault(const std::string& _key, const std::vector<std::pair<std::string, ParsingOption>>& _item, T _defaultValue = T{}) {
        for (const auto& [propKey, propValue] : _item) {
            if (propKey == _key) {
                if (std::holds_alternative<T>(propValue)) {
                    return std::get<T>(propValue);
                }
            }
        }
        return _defaultValue;
    }

public:
    // _type permet d'obtenir la bonne lambda pour créer l'item
    // _item contient toutes les données nécessaires pour créer l'item via le lambda ( il contient clé = valeur )
    std::shared_ptr<Item> CreateItemByType(const std::string& _type, const std::vector<std::pair<std::string, ParsingOption>>& _item) {
        auto item = createItem.find(_type);
        if (item != createItem.end()) {
            return item->second(_item);
        }
        return nullptr;
    }
};


