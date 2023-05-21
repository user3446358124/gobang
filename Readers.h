#pragma once
#include "class.h"

class Readers
{
public:
    vector<vector<int>> read_map_from_file(const std::string& filename, vector<vector<int>> map);
};