#include "include.h"
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

extern int nonecount = 0;


std::vector<std::vector<int>>& Readers::read_map_from_file(const std::string& filename, std::vector<std::vector<int>>& map, int filenum)
{
    std::ifstream file(filename + std::to_string(filenum) + ".txt");  // 打开文件名为"filename+filenum.txt"的文本文件
    if (file.is_open())  // 如果文件成功打开
    {
        for (int i = 0; i < 18; i++)  // 循环读取18行数据
        {
            for (int j = 0; j < 18; j++)  // 循环读取每行的18个整数数据
            {
                file >> map[i][j];  // 从文件中读取一个整数，并存入map的对应位置
            }
        }
        file.close();  // 关闭文件
    }

    for (int i = 0; i < 18; i++)  // 统计非空格子的数量
    {
        for (int j = 0; j < 18; j++)
        {
            if (map[i][j] != -1)  // 如果map中的元素不为-1（表示空格子）
            {
                nonecount++;  // 非空格子数量加1
            }
        }
    }
    return map;  // 返回读取后的map
}