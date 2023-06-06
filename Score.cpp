#include "include.h"

const int INF = 1000000000000;                //Alpha,beta
const int MAXN = 18;                          // 棋盘大小
const int MAXM = 324;                         // 棋盘格子数

extern std::vector<vector<int>> map;          //抽象后的地图
extern int aiset;                             //ai决策结果
extern double aiPos, myPos;                   //我方和电脑棋局得分






/*评测等级*/
void MyChess::get_grade(Users user, wchar_t*& wstr)
{
	int w = user.wincnt;
	int f = user.failcnt;

	if (w < 10) //const_cast 类型转化
	{
		if (f < 10)
			wstr = const_cast<wchar_t*>(L"默默无闻");
		else if (f < 30)
			wstr = const_cast<wchar_t*>(L"逆境之旅");
		else if (f < 60)
			wstr = const_cast<wchar_t*>(L"饥寒交迫");
		else if (f < 100)
			wstr = const_cast<wchar_t*>(L"露宿街头");
		else
			wstr = const_cast<wchar_t*>(L"心如死灰");
	}
	else if (w < 30)
	{
		if (f < 10)
			wstr = const_cast<wchar_t*>(L"小有成色");
		else if (f < 30)
			wstr = const_cast<wchar_t*>(L"英勇之士");
		else if (f < 50)
			wstr = const_cast<wchar_t*>(L"心怀希望");
		else
			wstr = const_cast<wchar_t*>(L"不屈不饶");
	}
	else if (w < 50)
	{
		if (f < 10)
			wstr = const_cast<wchar_t*>(L"黎明之日");
		else if (f < 50)
			wstr = const_cast<wchar_t*>(L"年少有为");
		else
			wstr = const_cast<wchar_t*>(L"探索者");
	}
	else if (w < 100)
	{
		if (f < 10)
			wstr = const_cast<wchar_t*>(L"闪耀之星");
		else if (f < 50)
			wstr = const_cast<wchar_t*>(L"大放光彩");
		else
			wstr = const_cast<wchar_t*>(L"才华横溢");
	}

	else if (w < 180)
	{

		if (f < 10)
			wstr = const_cast<wchar_t*>(L"常胜将军");
		else if (f < 50)
			wstr = const_cast<wchar_t*>(L"登峰造极");
		else if (f < 200)
			wstr = const_cast<wchar_t*>(L"春风得意");
		else
			wstr = const_cast<wchar_t*>(L"万众瞩目");
	}
	else
		wstr = const_cast<wchar_t*>(L"群星之巅");
}






/*胜率评级*/
void MyChess::get_assuse(wchar_t*& wstr)
{
	double ai = aiPos;
	double my = myPos;

	if (ai > my + 8000)
		wstr = const_cast<wchar_t*>(L"毫无胜算");
	else if (ai > my + 5000)
		wstr = const_cast<wchar_t*>(L"危在旦夕");
	else if (ai > my + 2000)
		wstr = const_cast<wchar_t*>(L"措不及防");
	else if (ai > my + 600)
		wstr = const_cast<wchar_t*>(L"略显被动");
	else if (ai > my)
		wstr = const_cast<wchar_t*>(L"均势");
	else if (my > ai + 8000)
		wstr = const_cast<wchar_t*>(L"锁定胜局");
	else if (my > ai + 5000)
		wstr = const_cast<wchar_t*>(L"胜券在握");
	else if (my > ai + 2000)
		wstr = const_cast<wchar_t*>(L"遥遥领先");
	else if (my > ai + 600)
		wstr = const_cast<wchar_t*>(L"小有优势");
	else
		wstr = const_cast<wchar_t*>(L"均势");

	return;
}