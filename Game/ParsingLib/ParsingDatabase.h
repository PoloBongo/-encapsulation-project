#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include "DataExtraction.h"
#include "Parsing.h"

class ParsingDatabase
{
public:
	ParsingDatabase() {};
	ParsingDatabase(const std::string& filePath);

	bool LoadFile();

	std::unordered_map<std::string, std::string> GetItemsInformation(const std::string& _sectionName) const;
	void JointureFile(DataExtraction& _dataExtraction, std::unordered_map<std::string, std::function<void(const std::string&)>> _funcMap, Parsing& parsing, int _itemID);

private:
	std::unordered_map<std::string, std::unordered_map<std::string, std::string>> data;
	std::string Trim(const std::string& str);
	std::string filePath;
	std::vector<std::string> test;
	std::ifstream file;
	bool canExtract = false;
};

