#pragma once

#include <string>
#include <vector>
#include <variant>
#include <iostream>

class FieldRegistrar {
public:
    template<typename T>
    void RegisterFieldFunc(const std::string& key, T& field, const std::string& value);

    template<typename T>
    void AddValueToItem(std::vector<std::pair<std::string, ParsingOption>>& item, const std::string& key, const T& value, const T& defaultValue);
};

#include "RegisterField.inl"
