//������� �ӿڵĴ

#pragma once

#ifndef CHESS_H
#define CHESS_H

#include <graphics.h>
#include <time.h>
#include <vector>
#include "Class.h"

#pragma comment(lib,"Winmm.lib")         //����ʱ���libname�⵽�������б��У�Winmm.lib��һ��Windows��ý��⣬���ṩ��һЩ��Ƶ����Ƶ�Ͷ�ʱ���Ĺ���

using namespace std;

class Chess
{
public:

	/*�ĸ��ӿڣ����ڹ�ȥ����x,y���ĸ��������Ԫ����������ص����������*/
	vector<int> Get_Nums1(int x, int y);
	vector<int> Get_Nums2(int x, int y);
	vector<int> Get_Nums3(int x, int y);
	vector<int> Get_Nums4(int x, int y);

	int  Get_Points(int x, int y, int ch);				//��ȡ�õ�ĵ÷�
	int  xy_Points(vector<int> nums, int ch);			//���ݵ������������ȡ�÷�

	bool is_Ok(int x, int y)		                    //�жϸõ��Ƿ������̷�Χ��
	{
		return x >= 0 && y >= 0 && x < 18 && y < 18;
	}

	virtual bool win(int x, int y) = 0;                 //�Ƿ�Ӯ
	virtual bool gameOver(Show s, Users& user) = 0;		//�ж��Ƿ������Ϸ
	double GetNowPoints(int ch);
};


class MyChess : public Chess
{
public:
	MyChess() : steps(0), now(false) {};

	int Get_xy(int& x, int& y);		                    //�жϸõ��Ƿ��ڿս��㷶Χ��
	int steps;						                    //�ߵĲ���
	bool now;						                    //�Ƿ��ֵ���������

	bool win(int x, int y) override                     //����ʤ������ �ж��Ƿ�Ӯ
	{
		return (!Get_Nums1(x, y).empty() && Get_Nums1(x, y)[1] == 5) || (!Get_Nums2(x, y).empty() && Get_Nums2(x, y)[1] == 5) || (!Get_Nums3(x, y).empty() && Get_Nums3(x, y)[1] == 5) || (!Get_Nums4(x, y).empty() && Get_Nums4(x, y)[1] == 5);
	}
	bool gameOver(Show s, Users& user) override;        //�ж��Ƿ������Ϸ
	void get_grade(Users user, wchar_t*& wstr);         //�жϵȼ�
	void get_assuse(wchar_t*& wstr);                    //����
};


class AiChess : public Chess
{
public:
	bool is_Ok(int x, int y)                           //�жϸõ��Ƿ������̷�Χ��
	{
		return x >= 0 && y >= 0 && x < 18 && y < 18;
	}
	void Get_key_Setchess(MyChess& mychs);             //��ȡ�÷���ߵ�λ�ã�������
	bool win(int x, int y) override                    //����ʤ������ �ж��Ƿ�Ӯ
	{
		return (!Get_Nums1(x, y).empty() && Get_Nums1(x, y)[0] == 5) || (!Get_Nums2(x, y).empty() && Get_Nums2(x, y)[0] == 5) || (!Get_Nums3(x, y).empty() && Get_Nums3(x, y)[0] == 5) || (!Get_Nums4(x, y).empty() && Get_Nums4(x, y)[0] == 5);
	}
	bool gameOver(Show s, Users& user) override;       //����gameOver����
	int AlphaBetaSearch(vector<vector<int>>& map, int depth, int alpha, int beta, bool maximizingPlayer, int& best_x, int& best_y);
};

#endif // !CHESS_H



