#include "include.h"

extern int nonecount = 0;

std::vector<std::vector<int>>& Readers::read_map_from_file(const std::string& filename, std::vector<std::vector<int>>& map) {
	// 打开文件
	std::ifstream file(filename);
	// 如果打开失败，抛出异常
	if (!file.is_open()) 
	{
		throw std::runtime_error("Failed to open file: " + filename);
	}
	std::string line;
	// 逐行读取文件内容
	while (std::getline(file, line)) 
	{
		// 创建一个整数向量表示当前行
		std::vector<int> row;
		// 使用 std::stringstream 将当前行分割为多个整数
		std::stringstream ss(line);
		int value;
		while (ss >> value) 
		{
			// 将整数添加到 row 中
			row.push_back(value);
		}
		// 将 row 添加到地图中
		map.push_back(row);
	}

	// 如果在读取文件过程中发生错误，抛出异常
	if (file.bad()) 
	{
		throw std::runtime_error("Error reading file: " + filename);
	}


	for (int i = 0; i < 18; i++) {
		for (int j = 0; j < 18; j++) {
			if (map[i][j] != -1) {
				nonecount++;
			}
		}
	}

	return map;
}