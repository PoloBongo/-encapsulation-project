#pragma once

#define REGISTER_FIELD_INVENTORY(field, member) { field, [&](const std::string& value) { RegisterField(field, dataExtraction.member, value); } }
#define REGISTER_FIELD_DATABASE(field, member) { field, [&](const std::string& value) { _parsing.RegisterField(field, _dataExtraction.member, value); } }