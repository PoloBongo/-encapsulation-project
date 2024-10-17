#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>

class ParsingDatabase
{
public:
	ParsingDatabase() {};
	ParsingDatabase(const std::string& filePath);

	bool LoadFile();

private:
	std::unordered_map<std::string, std::unordered_map<std::string, std::string>> data;
	std::string Trim(const std::string& str);
	std::string filePath;
	std::ifstream file;
};

