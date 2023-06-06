#include "include.h"

const int INF = 1000000000000;                //Alpha,beta
const int MAXN = 18;                          // ���̴�С
const int MAXM = 324;                         // ���̸�����

extern std::vector<vector<int>> map;          //�����ĵ�ͼ
extern int aiset;                             //ai���߽��
extern double aiPos, myPos;                   //�ҷ��͵�����ֵ÷�






/*����ȼ�*/
void MyChess::get_grade(Users user, wchar_t*& wstr)
{
	int w = user.wincnt;
	int f = user.failcnt;

	if (w < 10) //const_cast ����ת��
	{
		if (f < 10)
			wstr = const_cast<wchar_t*>(L"ĬĬ����");
		else if (f < 30)
			wstr = const_cast<wchar_t*>(L"�澳֮��");
		else if (f < 60)
			wstr = const_cast<wchar_t*>(L"��������");
		else if (f < 100)
			wstr = const_cast<wchar_t*>(L"¶�޽�ͷ");
		else
			wstr = const_cast<wchar_t*>(L"��������");
	}
	else if (w < 30)
	{
		if (f < 10)
			wstr = const_cast<wchar_t*>(L"С�г�ɫ");
		else if (f < 30)
			wstr = const_cast<wchar_t*>(L"Ӣ��֮ʿ");
		else if (f < 50)
			wstr = const_cast<wchar_t*>(L"�Ļ�ϣ��");
		else
			wstr = const_cast<wchar_t*>(L"��������");
	}
	else if (w < 50)
	{
		if (f < 10)
			wstr = const_cast<wchar_t*>(L"����֮��");
		else if (f < 50)
			wstr = const_cast<wchar_t*>(L"������Ϊ");
		else
			wstr = const_cast<wchar_t*>(L"̽����");
	}
	else if (w < 100)
	{
		if (f < 10)
			wstr = const_cast<wchar_t*>(L"��ҫ֮��");
		else if (f < 50)
			wstr = const_cast<wchar_t*>(L"��Ź��");
		else
			wstr = const_cast<wchar_t*>(L"�Ż�����");
	}

	else if (w < 180)
	{

		if (f < 10)
			wstr = const_cast<wchar_t*>(L"��ʤ����");
		else if (f < 50)
			wstr = const_cast<wchar_t*>(L"�Ƿ��켫");
		else if (f < 200)
			wstr = const_cast<wchar_t*>(L"�������");
		else
			wstr = const_cast<wchar_t*>(L"������Ŀ");
	}
	else
		wstr = const_cast<wchar_t*>(L"Ⱥ��֮��");
}






/*ʤ������*/
void MyChess::get_assuse(wchar_t*& wstr)
{
	double ai = aiPos;
	double my = myPos;

	if (ai > my + 8000)
		wstr = const_cast<wchar_t*>(L"����ʤ��");
	else if (ai > my + 5000)
		wstr = const_cast<wchar_t*>(L"Σ�ڵ�Ϧ");
	else if (ai > my + 2000)
		wstr = const_cast<wchar_t*>(L"�벻����");
	else if (ai > my + 600)
		wstr = const_cast<wchar_t*>(L"���Ա���");
	else if (ai > my)
		wstr = const_cast<wchar_t*>(L"����");
	else if (my > ai + 8000)
		wstr = const_cast<wchar_t*>(L"����ʤ��");
	else if (my > ai + 5000)
		wstr = const_cast<wchar_t*>(L"ʤȯ����");
	else if (my > ai + 2000)
		wstr = const_cast<wchar_t*>(L"ңң����");
	else if (my > ai + 600)
		wstr = const_cast<wchar_t*>(L"С������");
	else
		wstr = const_cast<wchar_t*>(L"����");

	return;
}