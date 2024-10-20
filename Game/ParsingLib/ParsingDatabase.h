#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include "DataExtraction.h"
#include "ParsingInventory.h"

class ParsingDatabase
{
public:
	ParsingDatabase() {};
	ParsingDatabase(const std::string& _filePath, bool _canExtract = false);

	bool LoadFile();

	std::unordered_map<std::string, std::string> GetItemsInformation(const std::string& _categoryName) const;
	void JointureFile(DataExtraction& _dataExtraction, std::unordered_map<std::string, std::function<void(const std::string&)>> _funcMap, int _itemID);

private:
	std::unordered_map<std::string, std::unordered_map<std::string, std::string>> data;
	std::string Trim(const std::string& str);
	std::string filePath;
	std::ifstream file;
	bool canExtract;
};

#include "Parsing.inl"