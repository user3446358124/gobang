#include "include.h"
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

extern int nonecount = 0;


std::vector<std::vector<int>>& Readers::read_map_from_file(const std::string& filename, std::vector<std::vector<int>>& map, int filenum)
{
    std::ifstream file(filename + std::to_string(filenum)+".txt");
    if (file.is_open()) 
    {
        for (int i = 0; i < 18; i++) 
        {
            for (int j = 0; j < 18; j++) 
            {
                file >> map[i][j];
            }
        }
        file.close();
    }

    for (int i = 0; i < 18; i++) 
    {
        for (int j = 0; j < 18; j++) 
        {
            if (map[i][j] != -1) 
            {
                nonecount++;
            }
        }
    }
    return map;
}
