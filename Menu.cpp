#include "include.h"

#define _CRT_SECURE_NO_WARNINGS

constexpr int Width = 800;
constexpr int High = 640;
vector<vector<int>> map(18, vector<int>(18, -1)), cop(map);		//map是棋盘，-1空，0电脑，1友方
stack<pair<int, int>> stk;			//用以控制悔棋-待删除
double myPos = 0, aiPos = 0;		//我方和电脑棋局得分
int aiset;							//记录电脑上一步下的位置
bool firstorsecond=1;
time_t first, second;
bool a, b, c, d, e, f;					//控制显示
extern bool flag = 1;
extern int nonecount;
int filenum = 1;

std::wstring stringToWideString(const std::string& str) {
	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), NULL, 0);
	std::wstring wstr(len, L'\0');
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), &wstr[0], len);
	return wstr;
}

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

#include <graphics.h>

void selectLevelWindow()
{
	initgraph(Width, High+100); // 初始化绘图窗口大小

	while (true)
	{
		BeginBatchDraw(); // 开始一批次的绘制

		setbkcolor(WHITE); // 设置背景颜色为白色
		cleardevice();    // 清空屏幕并用当前背景色填充整个屏幕
		setcolor(BLACK);  // 设置画笔颜色为黑色

		MOUSEMSG m;       // 定义鼠标消息对象
		m = GetMouseMsg(); // 获取鼠标消息
		int x = m.x, y = m.y; // 获取鼠标位置

		switch (m.uMsg) // 根据消息类型做出不同的处理
		{
		case WM_MOUSEMOVE: // 鼠标移动事件
			if (x >= 340 && x <= 460 && y >= 200 && y <= 240)
			{
				setcolor(RED);
				rectangle(340, 200, 460, 240);
				outtextxy(370, 210, L"第二关");
			}
			if (x >= 340 && x <= 460 && y >= 300 && y <= 340)
			{
				setcolor(RED);
				rectangle(340, 300, 460, 340);
				outtextxy(370, 310, L"第三关");
			}
			if (x >= 340 && x <= 460 && y >= 400 && y <= 440)
			{
				setcolor(RED);
				rectangle(340, 400, 460, 440);
				outtextxy(370, 410, L"第四关");
			}
			if (x >= 340 && x <= 460 && y >= 500 && y <= 540)
			{
				setcolor(RED);
				rectangle(340, 500, 460, 540);
				outtextxy(370, 510, L"第五关");
			}
			if (x >= 340 && x <= 460 && y >= 600 && y <= 640)
			{
				setcolor(RED);
				rectangle(340, 600, 460, 640);
				outtextxy(370, 610, L"第六关");
			}
			if (x >= 340 && x <= 460 && y >= 100 && y <= 140)
			{
				setcolor(RED);
				rectangle(340, 100, 460, 140);
				outtextxy(370, 110, L"第一关");
			}
			else
			{
				setcolor(BLACK);
				rectangle(340, 100, 460, 140);
				outtextxy(370, 110, L"第一关");
				rectangle(340, 200, 460, 240);
				outtextxy(370, 210, L"第二关");
				rectangle(340, 300, 460, 340);
				outtextxy(370, 310, L"第三关");
				rectangle(340, 400, 460, 440);
				outtextxy(370, 410, L"第四关");
				rectangle(340, 500, 460, 540);
				outtextxy(370, 510, L"第五关");
				rectangle(340, 600, 460, 640);
				outtextxy(370, 610, L"第六关");
			}
			break;
		case WM_LBUTTONUP:
			if (x >= 340 && x <= 460 && y >= 200 && y <= 240)
			{
				filenum = 2;
				closegraph(); // 关闭绘图窗口
				return;       // 返回选择的关卡
			}
			else if (x >= 340 && x <= 460 && y >= 300 && y <= 340)
			{
				filenum = 3;
				closegraph(); // 关闭绘图窗口
				return;       // 返回选择的关卡
			}
			else if (x >= 340 && x <= 460 && y >= 400 && y <= 440)
			{
				filenum = 4;
				closegraph(); // 关闭绘图窗口
				return;       // 返回选择的关卡
			}
			else if (x >= 340 && x <= 460 && y >= 500 && y <= 540)
			{
				filenum = 5;
				closegraph(); // 关闭绘图窗口
				return;       // 返回选择的关卡
			}
			else if (x >= 340 && x <= 460 && y >= 600 && y <= 640)
			{
				filenum = 6;
				closegraph(); // 关闭绘图窗口
				return;       // 返回选择的关卡
			}
			else if (x >= 340 && x <= 460 && y >= 100 && y <= 140)
			{
				filenum = 1;
				closegraph(); // 关闭绘图窗口
				return;       // 返回选择的关卡
			}
			break;
		}

		FlushBatchDraw(); // 刷新绘图窗口
		EndBatchDraw();   // 结束一批次的绘制
	}
}




std::atomic<bool> isRunning{ true };
std::atomic<int> global_duration{ 0 };
std::atomic<int> last_turn_duration{ 0 };
std::chrono::time_point<std::chrono::steady_clock> last_turn_start;

void timer_thread() {
	auto start = std::chrono::steady_clock::now();
	last_turn_start = start;
	while (isRunning) {
		auto now = std::chrono::steady_clock::now();
		global_duration = std::chrono::duration_cast<std::chrono::seconds>(now - start).count();
		last_turn_duration = std::chrono::duration_cast<std::chrono::seconds>(now - last_turn_start).count();

		// Display global timer and last turn duration
		std::wstring global_timer_text = L"全局时间： " + std::to_wstring(global_duration) + L"s";
		std::wstring turn_timer_text = L"轮次时间： " + std::to_wstring(last_turn_duration) + L"s";
		outtextxy(590, 540, global_timer_text.c_str());
		outtextxy(590, 570, turn_timer_text.c_str());


		// Sleep for 1 second
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

int computer_and_player(void) {
	MyChess mychs;
	Show s;
	AiChess ai;
	Users user;
	std::mutex mt;
	user.Read();
	map = cop;
	mychs.steps = 0;
	initgraph(Width, High);
	char turntimeshow[20] = "0:0";

	// Start timer thread
	std::thread timer(timer_thread);

	while (isRunning) {
		first = time(NULL);
		if (!firstorsecond)
			ai.Get_key_Setchess(mychs);
		s.show(mychs, user);
		BeginBatchDraw();
		outtextxy(570, 530, wchar_t((turntimeshow)));
		FlushBatchDraw();
		EndBatchDraw();

		if (ai.gameOver(s, user)) {
			map = cop;
			mychs.steps = 0;
			continue;
		}
		firstorsecond = 0;
		mychs.now = true;
		s.Mouse(mychs, user);

		// Update last turn start time
		last_turn_start = std::chrono::steady_clock::now();

		second = time(NULL);
		s.show(mychs, user);
		BeginBatchDraw();
		double time_diff = difftime(second, first);
		int minutes = static_cast<int>((int)time_diff / 60);
		int seconds = static_cast<int>((int)time_diff % 60);
		std::string turntimeshow = std::to_string(minutes) + "min: " + std::to_string(seconds) + "s";
		FlushBatchDraw();
		EndBatchDraw();
		if (mychs.gameOver(s, user)) {
			map = cop;
			mychs.steps = 0;
			continue;
		}
	}

	// Stop timer thread
	isRunning = false;
	timer.join();

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


int end_game(void) {
	MyChess mychs;
	Show s;
	AiChess ai;
	Users user;
	Readers readers;
	std::mutex mt;
	user.Read();
	int filenum = 1;
	selectLevelWindow();
	map = readers.read_map_from_file("level", map, filenum);
	mychs.steps = 0;
	initgraph(Width, High);
	char turntimeshow[20] = "0:0";

	// Start timer thread
	std::thread timer(timer_thread);

	while (isRunning) {
		first = time(NULL);
		if (!firstorsecond)
			ai.Get_key_Setchess(mychs);
		s.show(mychs, user);
		BeginBatchDraw();
		outtextxy(570, 530, wchar_t((turntimeshow)));
		FlushBatchDraw();
		EndBatchDraw();

		if (ai.gameOver(s, user)) {
			map = cop;
			mychs.steps = 0;
			continue;
		}
		firstorsecond = 0;
		mychs.now = true;
		s.Mouse(mychs, user);

		// Update last turn start time
		last_turn_start = std::chrono::steady_clock::now();

		second = time(NULL);
		s.show(mychs, user);
		BeginBatchDraw();
		double time_diff = difftime(second, first);
		int minutes = static_cast<int>((int)time_diff / 60);
		int seconds = static_cast<int>((int)time_diff % 60);
		std::string turntimeshow = std::to_string(minutes) + "min: " + std::to_string(seconds) + "s";
		FlushBatchDraw();
		EndBatchDraw();
		if (mychs.gameOver(s, user)) {
			map = cop;
			mychs.steps = 0;
			continue;
		}
	}

	// Stop timer thread
	isRunning = false;
	timer.join();

	return 0;
}



int online_player(void)
{
	MyChess mychs;
	Show s;
	AiChess ai;
	Users user;                     //正常创建
	Readers readers;

	std::mutex mt;                  //windows api 控制声音
	user.Read();                    //信息

	BeginBatchDraw();                                 //函数表示开始一批次的绘制，可以将多个图形一次性绘制出来，提高绘制效率。
	setbkcolor(WHITE);                            //设置背景颜色为白色
	cleardevice();                                    //清空屏幕并用当前背景色填充整个屏幕。
	setcolor(BLACK);                              //函数将当前画笔颜色设置为黑色。
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
			/*if (x >= 340 && x <= 460 && y >= 400 && y <= 440)
			{
				setcolor(RED);                              //函数将当前画笔颜色设置为黑色。
				rectangle(340, 200, 460, 240);              // 绘制矩形
				outtextxy(370, 210, L"玩家对战");            // 输出文本// 在鼠标位置处画一个圆圈，表示可以下
			}*/
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
			if (x >= 340 && x <= 460 && y >= 300 && y <= 340)
			{
				setcolor(RED);                              //函数将当前画笔颜色设置为黑色。
				rectangle(340, 300, 460, 340);              // 绘制矩形
				outtextxy(370, 310, L"残局闯关");            // 输出文本// 在鼠标位置处画一个圆圈，表示可以下
			}
			if (x >= 340 && x <= 460 && y >= 100 && y <= 140)
			{
				setcolor(RED);                              //函数将当前画笔颜色设置为黑色。
				rectangle(340, 100, 460, 140);              // 绘制矩形
				outtextxy(370, 110, L"联网对战");            // 输出文本// 在鼠标位置处画一个圆圈，表示可以下
			}
			else
			{
				setcolor(BLACK);                             //函数将当前画笔颜色设置为黑色。
				if (a)
				{
					rectangle(340, 100, 460, 140); // 绘制矩形
					outtextxy(370, 110, L"联网对战"); // 输出文本
				}
				if (b)
				{
					rectangle(340, 200, 460, 240); // 绘制矩形
					outtextxy(370, 210, L"人机对战"); // 输出文本
				}
				if (c)
				{
					rectangle(340, 300, 460, 340); // 绘制矩形
					outtextxy(370, 310, L"残局闯关"); // 输出文本
				}
				/*if (d)
				{
					rectangle(340, 400, 460, 440); // 绘制矩形
					outtextxy(370, 410, L"玩家对战"); // 输出文本
				}*/
				if (e)
				{
					rectangle(340, 500, 460, 540); // 绘制矩形
					outtextxy(370, 510, L"先手"); // 输出文本
				}
				if (f)
				{
					rectangle(340, 540, 460, 580); // 绘制矩形
					outtextxy(370, 550, L"后手"); // 输出文本下
				}
			}
			break;

		case WM_LBUTTONUP:
			if (x >= 340 && x <= 460 && y >= 540 && y <= 580)
			{
				f = 0;
				firstorsecond = 0;
			}
			else if (x >= 340 && x <= 460 && y >= 200 && y <= 240)
			{
				b = 0;
				int done = computer_and_player();
				return 0;
			}
			else if (x >= 340 && x <= 460 && y >= 400 && y <= 440)
			{
				d = 0;
				int done = player_and_player();
				return 0;
			}
			else if (x >= 340 && x <= 460 && y >= 300 && y <= 340)
			{
				c = 0;
				int done = end_game();
				return 0;
			}
			else if (x >= 340 && x <= 460 && y >= 100 && y <= 140)
			{
				a = 0;
				int done = online_player();
				return 0;
			}
			else if (x >= 340 && x <= 460 && y >= 500 && y <= 540)
			{
				e = 0;
			}
			break;
		}
	}
	FlushBatchDraw();
	EndBatchDraw(); //函数表示结束一批次的绘制，将缓冲区的图形一次性绘制出来。

	map = readers.read_map_from_file("level", map,1);
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
	a = b = c = d = e = f = 1;
	initgraph(Width, High);

	BeginBatchDraw();                                 //函数表示开始一批次的绘制，可以将多个图形一次性绘制出来，提高绘制效率。
	setbkcolor(WHITE);                            //设置背景颜色为白色
	cleardevice();                                    //清空屏幕并用当前背景色填充整个屏幕。
	setcolor(BLACK);                              //函数将当前画笔颜色设置为黑色。

	rectangle(340, 100, 460, 140); // 绘制矩形
	outtextxy(370, 110, L"联网对战"); // 输出文本

	rectangle(340, 200, 460, 240); // 绘制矩形
	outtextxy(370, 210, L"人机对战"); // 输出文本

	rectangle(340, 300, 460, 340); // 绘制矩形
	outtextxy(370, 310, L"残局闯关"); // 输出文本

	//rectangle(340, 400, 460, 440); // 绘制矩形
	//outtextxy(370, 410, L"玩家对战"); // 输出文本

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
			/*if (x >= 340 && x <= 460 && y >= 400 && y <= 440)
			{
				setcolor(RED);                              //函数将当前画笔颜色设置为黑色。
				rectangle(340, 200, 460, 240);              // 绘制矩形
				outtextxy(370, 210, L"玩家对战");            // 输出文本// 在鼠标位置处画一个圆圈，表示可以下
			}*/
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
			if (x >= 340 && x <= 460 && y >= 300 && y <= 340)
			{
				setcolor(RED);                              //函数将当前画笔颜色设置为黑色。
				rectangle(340, 300, 460, 340);              // 绘制矩形
				outtextxy(370, 310, L"残局闯关");            // 输出文本// 在鼠标位置处画一个圆圈，表示可以下
			}
			if (x >= 340 && x <= 460 && y >= 100 && y <= 140)
			{
				setcolor(RED);                              //函数将当前画笔颜色设置为黑色。
				rectangle(340, 100, 460, 140);              // 绘制矩形
				outtextxy(370, 110, L"联网对战");            // 输出文本// 在鼠标位置处画一个圆圈，表示可以下
			}
			else
			{
				setcolor(BLACK);                             //函数将当前画笔颜色设置为黑色。
				if (a)
				{
					rectangle(340, 100, 460, 140); // 绘制矩形
					outtextxy(370, 110, L"联网对战"); // 输出文本
				}
				if (b)
				{
					rectangle(340, 200, 460, 240); // 绘制矩形
					outtextxy(370, 210, L"人机对战"); // 输出文本
				}
				if (c)
				{
					rectangle(340, 300, 460, 340); // 绘制矩形
					outtextxy(370, 310, L"残局闯关"); // 输出文本
				}
				/*if (d)
				{
					rectangle(340, 400, 460, 440); // 绘制矩形
					outtextxy(370, 410, L"玩家对战"); // 输出文本
				}*/
				if (e)
				{
					rectangle(340, 500, 460, 540); // 绘制矩形
					outtextxy(370, 510, L"先手"); // 输出文本
				}
				if (f)
				{
					rectangle(340, 540, 460, 580); // 绘制矩形
					outtextxy(370, 550, L"后手"); // 输出文本下
				}
			}
			break;

		case WM_LBUTTONUP:
			if (x >= 340 && x <= 460 && y >= 540 && y <= 580)
			{
				f = 0;
				firstorsecond = 0;
			}
			else if (x >= 340 && x <= 460 && y >= 200 && y <= 240)
			{
				b = 0;
				int done = computer_and_player();
				return 0;
			}
			else if (x >= 340 && x <= 460 && y >= 400 && y <= 440)
			{
				d = 0;
				int done = player_and_player();
				return 0;
			}
			else if (x >= 340 && x <= 460 && y >= 300 && y <= 340)
			{
				c = 0;
				int done = end_game();
				return 0;
			}
			else if (x >= 340 && x <= 460 && y >= 100 && y <= 140)
			{
				a = 0;
				int done = online_player();
				return 0;
			}
			else if (x >= 340 && x <= 460 && y >= 500 && y <= 540)
			{
				e = 0;
			}
			break;
		}
	}
	return 0;
}


