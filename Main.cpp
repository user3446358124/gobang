#include "include.h"

using namespace std;

constexpr int Width = 800;
constexpr int High = 640;
vector<vector<int>> map(18, vector<int>(18, -1)), cop(map);		//map是棋盘，-1空，0电脑，1友方
stack<pair<int, int>> stk;			//用以控制悔棋-待删除
double myPos = 0, aiPos = 0;		//我方和电脑棋局得分
int aiset;							//记录电脑上一步下的位置

int main()
{
	MyChess mychs;
	Show s;
	AiChess ai;
	Users user;                     //正常创建

	std::mutex mt;                  //windows api 控制声音
	user.Read();                    //信息

	map = cop;
	mychs.steps = 0;
	initgraph(Width, High);

	bool isRunning = true;          //增加一个控制循环的变量
	while (isRunning)
	{
		ai.Get_key_Setchess(mychs);	//Al回合
		s.show(mychs, user);		//展示地图
		if (ai.gameOver(s, user))	//判断是否胜利
		{
			map = cop;              //重置地图
			mychs.steps = 0;        //重置步数
			continue;               //跳过本次循环，重新开始
		}

		mychs.now = true;			//你的回合 set now = true
		s.Mouse(mychs, user);		//鼠标确定选择,set now = false
		s.show(mychs, user);        //展示地图
		if (mychs.gameOver(s, user))//判断是否胜利	
		{
			map = cop;              //重置地图
			mychs.steps = 0;        //重置步数
			continue;               //跳过本次循环，重新开始
		}
	}

	return 0;
}