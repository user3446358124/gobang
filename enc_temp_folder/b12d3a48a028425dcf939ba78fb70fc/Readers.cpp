#include "include.h"

extern int nonecount = 0;

std::vector<std::vector<int>>& Readers::read_map_from_file(const std::string& filename, std::vector<std::vector<int>>& map) {
	// ���ļ�
	std::ifstream file(filename);
	// �����ʧ�ܣ��׳��쳣
	if (!file.is_open()) 
	{
		throw std::runtime_error("Failed to open file: " + filename);
	}
	std::string line;
	// ���ж�ȡ�ļ�����
	while (std::getline(file, line)) 
	{
		// ����һ������������ʾ��ǰ��
		std::vector<int> row;
		// ʹ�� std::stringstream ����ǰ�зָ�Ϊ�������
		std::stringstream ss(line);
		int value;
		while (ss >> value) 
		{
			// ��������ӵ� row ��
			row.push_back(value);
		}
		// �� row ��ӵ���ͼ��
		map.push_back(row);
	}

	// ����ڶ�ȡ�ļ������з��������׳��쳣
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