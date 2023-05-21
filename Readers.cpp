#include "include.h"

vector<vector<int>> Readers::read_map_from_file(const std::string& filename, vector<vector<int>> map)
{
    ifstream file(filename);
    string line;

    while (getline(file, line))
    {
        vector<int> row;
        stringstream ss(line);
        int value;
        while (ss >> value) {
            row.push_back(value);
        }
        map.push_back(row);
    }
    return map;
}