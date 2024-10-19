#pragma once

#define REGISTER_FIELD(field, member) { field, [&](const std::string& _value) { RegisterField(field, dataExtraction.member, _value); } }