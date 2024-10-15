#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>

struct DataExtraction {
    int id;
    int quantity;
    std::string type;
    float damage;
    float resistance;
    float durability;
};

class Parsing {
public:
    Parsing() {};
    Parsing(const std::string& filePath);
    bool LoadFile();

    std::vector<std::string> GetAllCategory() const;
    std::map<std::string, std::string> GetItemsInformation(const std::string& sectionName) const;
    std::string GetValueOfItem(const std::string& sectionName, const std::string& key) const;

    void AddNewData(const std::string& category, const std::string& key, const std::string& value);
    void Modify(const std::string& category, const std::string& key, const std::string& value);

    DataExtraction GetAllDataFromInventory();

    void Test();

private:
    std::map<std::string, std::map<std::string, std::string>> data;
    std::string Trim(const std::string &str);
    std::string filePath;
    std::ifstream file;
};
