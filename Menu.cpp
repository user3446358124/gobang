#include "include.h"

constexpr int Width = 800;
constexpr int High = 640;
vector<vector<int>> map(18, vector<int>(18, -1)), cop(map);		//map是棋盘，-1空，0电脑，1友方
stack<pair<int, int>> stk;			//用以控制悔棋-待删除
double myPos = 0, aiPos = 0;		//我方和电脑棋局得分
int aiset;							//记录电脑上一步下的位置
bool firstorsecond=1;

void playorder(void)
{
	initgraph(Width, High);

	BeginBatchDraw();                                 //函数表示开始一批次的绘制，可以将多个图形一次性绘制出来，提高绘制效率。
	setbkcolor(WHITE);                            //设置背景颜色为白色
	cleardevice();                                    //清空屏幕并用当前背景色填充整个屏幕。
	setcolor(BLACK);                              //函数将当前画笔颜色设置为黑色。

	rectangle(340, 100, 460, 140); // 绘制矩形
	outtextxy(370, 110, L"先手"); // 输出文本

	rectangle(340, 200, 460, 240); // 绘制矩形
	outtextxy(370, 210, L"后手"); // 输出文本

	FlushBatchDraw();
	EndBatchDraw();
	MOUSEMSG m; // 定义鼠标消息对象
	while (true) // 循环监听鼠标事件
	{
		TCHAR str[250];																 // 定义字符数组，用于存储要输出的字符串
		m = GetMouseMsg();															 // 获取鼠标消息
		int x = m.x, y = m.y;														 // 获取鼠标位置
		switch (m.uMsg)																 // 根据消息类型做出不同的处理
		{
		case WM_LBUTTONUP:                                                           // 鼠标移动事件
			if (x >= 340 && x <= 460 && y >= 200 && y <= 240)
			{
				setcolor(RED);                              //函数将当前画笔颜色设置为黑色。
				rectangle(340, 200, 460, 240);              // 绘制矩形
				outtextxy(370, 210, L"后手"); // 输出文本
				firstorsecond = 1;
				return;
			}
			else if (x >= 340 && x <= 460 && y >= 100 && y <= 140)
			{
				setcolor(RED);                              //函数将当前画笔颜色设置为黑色。
				rectangle(340, 200, 460, 240);              // 绘制矩形
				outtextxy(370, 210, L"先手"); // 输出文本
				firstorsecond = 0;
				return;
			}
			break;
		}
	}
	return;
}

int computer_and_player(void)
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
		if(!firstorsecond)
			ai.Get_key_Setchess(mychs);	//Al回合
			s.show(mychs, user);		//展示地图
			if (ai.gameOver(s, user))	//判断是否胜利
			{
				map = cop;              //重置地图
				mychs.steps = 0;        //重置步数
				continue;               //跳过本次循环，重新开始
			}
		
			firstorsecond = 1;
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

int player_and_player(void)
{
	MyChess mychs;
	Show s;
	Users user;                     //正常创建

	std::mutex mt;                  //windows api 控制声音
	user.Read();                    //信息

	map = cop;
	mychs.steps = 0;
	initgraph(Width, High);

	bool isRunning = true;          //增加一个控制循环的变量
	while (isRunning)
	{
		mychs.now = true;			//你的回合 set now = true
		s.Mouse(mychs, user);		//鼠标确定选择,set now = false
		s.show(mychs, user);        //展示地图
		if (mychs.gameOver(s, user))//判断是否胜利	
		{
			map = cop;              //重置地图
			mychs.steps = 0;        //重置步数
			continue;               //跳过本次循环，重新开始
		}

		mychs.now = false;			//你的回合 set now = true
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

int end_game(void)
{
	MyChess mychs;
	Show s;
	AiChess ai;
	Users user;                     //正常创建
	Readers readers;

	std::mutex mt;                  //windows api 控制声音
	user.Read();                    //信息

	map = readers.read_map_from_file("level1", map);
	mychs.steps = 0;
	initgraph(Width, High);

	bool isRunning = true;          //增加一个控制循环的变量
	bool flag = 0;
	while (isRunning)
	{
		if (flag)
			ai.Get_key_Setchess(mychs);	//Al回合
		s.show(mychs, user);		//展示地图
		if (ai.gameOver(s, user))	//判断是否胜利
		{
			map = cop;              //重置地图
			mychs.steps = 0;        //重置步数
			continue;               //跳过本次循环，重新开始
		}

		flag = 1;
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

int main()
{
	initgraph(Width, High);

	BeginBatchDraw();                                 //函数表示开始一批次的绘制，可以将多个图形一次性绘制出来，提高绘制效率。
	setbkcolor(WHITE);                            //设置背景颜色为白色
	cleardevice();                                    //清空屏幕并用当前背景色填充整个屏幕。
	setcolor(BLACK);                              //函数将当前画笔颜色设置为黑色。

	rectangle(340, 100, 460, 140); // 绘制矩形
	outtextxy(370, 110, L"联机对战"); // 输出文本

	rectangle(340, 200, 460, 240); // 绘制矩形
	outtextxy(370, 210, L"人机对战"); // 输出文本

	rectangle(340, 300, 460, 340); // 绘制矩形
	outtextxy(370, 310, L"残局闯关"); // 输出文本

	rectangle(340, 400, 460, 440); // 绘制矩形
	outtextxy(370, 410, L"玩家对战"); // 输出文本

	rectangle(340, 500, 460, 540); // 绘制矩形
	outtextxy(370, 510, L"先手"); // 输出文本

	rectangle(340, 540, 460, 580); // 绘制矩形
	outtextxy(370, 550, L"后手"); // 输出文本

	FlushBatchDraw();
	EndBatchDraw(); //函数表示结束一批次的绘制，将缓冲区的图形一次性绘制出来。
	MOUSEMSG m; // 定义鼠标消息对象
	while (true) // 循环监听鼠标事件
	{
		TCHAR str[250];																 // 定义字符数组，用于存储要输出的字符串
		m = GetMouseMsg();															 // 获取鼠标消息
		int x = m.x, y = m.y;														 // 获取鼠标位置
		switch (m.uMsg)																 // 根据消息类型做出不同的处理
		{
		case WM_MOUSEMOVE:                                                           // 鼠标移动事件
			if (x >= 340 && x <= 460 && y >= 200 && y <= 240)
			{
				setcolor(RED);                              //函数将当前画笔颜色设置为黑色。
				rectangle(340, 200, 460, 240);              // 绘制矩形
				outtextxy(370, 210, L"人机对战");            // 输出文本// 在鼠标位置处画一个圆圈，表示可以下
			}
			if (x >= 340 && x <= 460 && y >= 400 && y <= 440)
			{
				setcolor(RED);                              //函数将当前画笔颜色设置为黑色。
				rectangle(340, 200, 460, 240);              // 绘制矩形
				outtextxy(370, 210, L"玩家对战");            // 输出文本// 在鼠标位置处画一个圆圈，表示可以下
			}
			if (x >= 340 && x <= 460 && y >= 500 && y <= 540)
			{
				setcolor(RED);                              //函数将当前画笔颜色设置为黑色。
				rectangle(340, 500, 460, 540);              // 绘制矩形
				outtextxy(370, 510, L"先手");            // 输出文本// 在鼠标位置处画一个圆圈，表示可以下
			}
			if (x >= 340 && x <= 460 && y >= 540 && y <= 580)
			{
				setcolor(RED);                              //函数将当前画笔颜色设置为黑色。
				rectangle(340, 540, 460, 580);              // 绘制矩形
				outtextxy(370, 550, L"后手");            // 输出文本// 在鼠标位置处画一个圆圈，表示可以下
			}
			else if(firstorsecond)
			{
				setcolor(BLACK);                              //函数将当前画笔颜色设置为黑色。
				rectangle(340, 200, 460, 240);              // 绘制矩形
				outtextxy(370, 210, L"人机对战");            // 输出文本// 在鼠标位置处画一个圆圈，表示可以下
				rectangle(340, 400, 460, 440);              // 绘制矩形
				outtextxy(370, 410, L"玩家对战");            // 输出文本// 在鼠标位置处画一个圆圈，表示可以下
				rectangle(340, 500, 460, 540);              // 绘制矩形
				outtextxy(370, 510, L"先手");            // 输出文本// 在鼠标位置处画一个圆圈，表示可以下
				rectangle(340, 540, 460, 580);              // 绘制矩形
				outtextxy(370, 550, L"后手");            // 输出文本// 在鼠标位置处画一个圆圈，表示可以下
			}
			break;

		case WM_LBUTTONUP:
			if (x >= 340 && x <= 460 && y >= 540 && y <= 580)
			{
				firstorsecond = 0;
			}
			if (x >= 340 && x <= 460 && y >= 200 && y <= 240)
			{
				int done = computer_and_player();
				return 0;
			}
			if (x >= 340 && x <= 460 && y >= 400 && y <= 440)
			{
				int done = player_and_player();
				return 0;
			}
			break;
		}
	}
	return 0;
}


