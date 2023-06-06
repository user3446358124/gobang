#include "include.h"
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

extern int nonecount = 0;


std::vector<std::vector<int>>& Readers::read_map_from_file(const std::string& filename, std::vector<std::vector<int>>& map, int filenum)
{
    std::ifstream file(filename + std::to_string(filenum) + ".txt");  // ���ļ���Ϊ"filename+filenum.txt"���ı��ļ�
    if (file.is_open())  // ����ļ��ɹ���
    {
        for (int i = 0; i < 18; i++)  // ѭ����ȡ18������
        {
            for (int j = 0; j < 18; j++)  // ѭ����ȡÿ�е�18����������
            {
                file >> map[i][j];  // ���ļ��ж�ȡһ��������������map�Ķ�Ӧλ��
            }
        }
        file.close();  // �ر��ļ�
    }

    for (int i = 0; i < 18; i++)  // ͳ�Ʒǿո��ӵ�����
    {
        for (int j = 0; j < 18; j++)
        {
            if (map[i][j] != -1)  // ���map�е�Ԫ�ز�Ϊ-1����ʾ�ո��ӣ�
            {
                nonecount++;  // �ǿո���������1
            }
        }
    }
    return map;  // ���ض�ȡ���map
}