#include "include.h"

#define _CRT_SECURE_NO_WARNINGS     //这是一个预处理指令，用于在 Visual Studio 中禁用警告。它用于抑制当使用某些函数（如 scanf() 和 strncpy()）时编译器生成的警告。

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
	// 获取转换后的字符串长度
	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), NULL, 0);
	/*这行代码使用了 MultiByteToWideChar 函数，它是一个 Windows API 函数，用于将多字节字符集（MBCS）字符串转换为宽字符集（Unicode）字符串。
	 *在这个例子中，函数的第一个参数 CP_ACP 表示使用系统默认的 Windows ANSI 代码页来执行转换。
	 *第二个参数为标志，这里设置为 0。
	 *第三个和第四个参数分别指定要转换的多字节字符串及其长度。
	 *第五个参数为接收转换后的宽字符集字符串的缓冲区，这里设置为 NULL，表示不接收转换后的字符串。
	 *最后一个参数指定缓冲区的大小，这里设置为 0。
		当 MultiByteToWideChar 函数的第五个参数设置为 NULL 且第六个参数设置为 0 时，函数返回所需缓冲区的大小（以宽字符为单位），而不执行实际的转换。在这个例子中，函数返回值被存储在名为 len 的 int 变量中，表示转换后的宽字符集字符串所需的缓冲区大小。*/
	// 创建一个 std::wstring 对象
	std::wstring wstr(len, L'\0');
	// 调用 MultiByteToWideChar 函数来完成转换
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), &wstr[0], len);
	/*这行代码再次调用了 `MultiByteToWideChar` 函数，用于将多字节字符集（MBCS）字符串转换为宽字符集（Unicode）字符串。
	 *与上一次调用相比，这次调用的第五个参数为 `&wstr[0]`，表示接收转换后的宽字符集字符串的缓冲区。
	 *第六个参数为 `len`，表示缓冲区的大小。
		在这个例子中，函数将多字节字符串 `str` 转换为宽字符集字符串，并将转换后的字符串存储在 `wstr` 缓冲区中。
		缓冲区的大小由之前调用 `MultiByteToWideChar` 函数时返回的值确定。*/
	// 返回转换后的字符串
	return wstr;
}





void playorder(void)//决定先后手
{
	//绘制先后手图像
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
	//绘制先后手图像

	MOUSEMSG m;                                                                     // 定义鼠标消息对象
	while (true)                                                                    // 循环监听鼠标事件
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





void selectLevelWindow()  //残局挑战选择关卡
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
		int a, b, c, d, e, f;
		a = b = c = d = e = f = 1;

		switch (m.uMsg) // 根据消息类型做出不同的处理
		{
		case WM_MOUSEMOVE: // 鼠标移动事件
			if (x >= 340 && x <= 460 && y >= 200 && y <= 240)
			{
				setcolor(RED);
				rectangle(340, 200, 460, 240);
				outtextxy(370, 210, L"第二关");
				b = 0;
				a = c = d = e = f = 1;
			}
			if (x >= 340 && x <= 460 && y >= 300 && y <= 340)
			{
				setcolor(RED);
				rectangle(340, 300, 460, 340);
				outtextxy(370, 310, L"第三关");
				c = 0;
				a = b = d = e = f = 1;
			}
			if (x >= 340 && x <= 460 && y >= 400 && y <= 440)
			{
				setcolor(RED);
				rectangle(340, 400, 460, 440);
				outtextxy(370, 410, L"第四关");
				d = 0;
				a = b = c = e = f = 1;
			}
			if (x >= 340 && x <= 460 && y >= 500 && y <= 540)
			{
				setcolor(RED);
				rectangle(340, 500, 460, 540);
				outtextxy(370, 510, L"第五关");
				e = 0;
				a = b = c = d = f = 1;
			}
			if (x >= 340 && x <= 460 && y >= 600 && y <= 640)
			{
				setcolor(RED);
				rectangle(340, 600, 460, 640);
				outtextxy(370, 610, L"第六关");
				f = 0;
				a = b = c = d = e = 1;
			}
			if (x >= 340 && x <= 460 && y >= 100 && y <= 140)
			{
				setcolor(RED);
				rectangle(340, 100, 460, 140);
				outtextxy(370, 110, L"第一关");
				a = 0;
				b = c = d = e = f = 1;
			}
			
			{
				setcolor(BLACK);
				if (a)
				{
					rectangle(340, 100, 460, 140);
					outtextxy(370, 110, L"第一关");
				}
				if (b)
				{
					rectangle(340, 200, 460, 240);
					outtextxy(370, 210, L"第二关");
				}
				if (c)
				{
					rectangle(340, 300, 460, 340);
					outtextxy(370, 310, L"第三关");
				}
				if (d)
				{
					rectangle(340, 400, 460, 440);
					outtextxy(370, 410, L"第四关");
				}
				if (e)
				{
					rectangle(340, 500, 460, 540);
					outtextxy(370, 510, L"第五关");
				}
				if (f)
				{
					rectangle(340, 600, 460, 640);
					outtextxy(370, 610, L"第六关");
				}
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



//计时器

// 定义原子变量 isRunning，用于控制线程是否运行
std::atomic<bool> isRunning{ true };
// 定义原子变量 global_duration，用于存储全局时间
std::atomic<int> global_duration{ 0 };
// 定义原子变量 last_turn_duration，用于存储上一轮时间
std::atomic<int> last_turn_duration{ 0 };
// 定义 last_turn_start 变量，用于存储上一轮开始时间
std::chrono::time_point<std::chrono::steady_clock> last_turn_start;

// 计时器线程函数
void timer_thread()
{
	// 获取当前时间作为开始时间
	auto start = std::chrono::steady_clock::now();
	// 设置上一轮开始时间为开始时间
	last_turn_start = start;
	// 循环直到 isRunning 变为 false
	while (isRunning) 
	{
		// 获取当前时间
		auto now = std::chrono::steady_clock::now();
		// 计算全局时间
		global_duration = std::chrono::duration_cast<std::chrono::seconds>(now - start).count();
		// 计算上一轮时间
		last_turn_duration = std::chrono::duration_cast<std::chrono::seconds>(now - last_turn_start).count();


		// 构造全局时间字符串并显示在屏幕上
		std::wstring global_timer_text = L"全局时间： " + std::to_wstring(global_duration) + L"s";
		outtextxy(590, 540, global_timer_text.c_str());
		// 构造上一轮时间字符串并显示在屏幕上
		std::wstring turn_timer_text = L"轮次时间： " + std::to_wstring(last_turn_duration) + L"s";
		outtextxy(590, 570, turn_timer_text.c_str());


		// 休眠 1 秒钟
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}
//计时器






int computer_and_player(void) {
	// 定义 MyChess 类对象
	MyChess mychs;
	// 定义 Show 类对象
	Show s;
	// 定义 AiChess 类对象
	AiChess ai;
	// 定义 Users 类对象
	Users user;
	// 定义互斥锁
	std::mutex mt;
	// 读取用户信息
	user.Read();
	// 设置地图
	map = cop;
	// 初始化步数
	mychs.steps = 0;
	// 初始化图形界面
	initgraph(Width, High);
	// 定义轮次时间显示字符串
	char turntimeshow[20] = "0:0";


	// 启动计时器线程
	std::thread timer(timer_thread);

	// 循环直到 isRunning 变为 false
	while (isRunning) 
	{
		// 获取当前时间作为开始时间
		first = time(NULL);
		// 如果是 AI 下棋，则调用 AI 的方法进行下棋
		if (!firstorsecond)
			ai.Get_key_Setchess(mychs);
		// 显示棋盘和棋子
		s.show(mychs, user);

		BeginBatchDraw();
		outtextxy(570, 530, wchar_t((turntimeshow)));
		FlushBatchDraw();
		EndBatchDraw();

		// 判断游戏是否结束，如果结束则重置地图和步数并继续下一轮游戏
		if (ai.gameOver(s, user)) 
		{
			map = cop;
			mychs.steps = 0;
			continue;
		}

		firstorsecond = 0;
		mychs.now = true;
		// 获取用户鼠标操作并更新棋盘和棋子信息
		s.Mouse(mychs, user);


		// 更新上一轮开始时间
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

	// 停止计时器线程并等待其结束
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
	MyChess mychs; // 创建 MyChess 对象，用于管理棋局状态
	Show s; // 创建 Show 对象，用于显示棋局界面
	AiChess ai; // 创建 AiChess 对象，用于实现 AI 算法
	Users user; // 创建 Users 对象，用于管理用户信息
	Readers readers; // 创建 Readers 对象，用于读取文件
	std::mutex mt; // 创建互斥锁对象，用于线程同步
	user.Read(); // 读取用户信息
	int filenum = 1; // 文件编号
	selectLevelWindow(); // 选择游戏难度的窗口
	map = readers.read_map_from_file("level", map, filenum); // 从文件中读取地图数据
	mychs.steps = 0; // 初始化棋局步数为 0
	initgraph(Width, High); // 初始化绘图环境
	char turntimeshow[20] = "0:0"; // 存储计时器显示的字符串
	// 启动计时器线程
	std::thread timer(timer_thread);
	while (isRunning) { // 循环执行游戏主逻辑，直到游戏结束
		first = time(NULL); // 记录当前时间
		if (!firstorsecond)
			ai.Get_key_Setchess(mychs); // AI 下棋
		s.show(mychs, user); // 显示棋局
		BeginBatchDraw(); // 开始批量绘制
		outtextxy(570, 530, wchar_t((turntimeshow))); // 绘制计时器文本
		FlushBatchDraw(); // 刷新绘图
		EndBatchDraw(); // 结束批量绘制
		if (ai.gameOver(s, user)) { // 检查是否达到游戏结束条件
			map = cop; // 恢复地图状态
			mychs.steps = 0; // 重置棋局步数
			continue; // 继续下一轮循环
		}
		firstorsecond = 0; // 切换为用户回合
		mychs.now = true; // 设置当前轮到用户操作
		s.Mouse(mychs, user); // 处理用户鼠标操作
		// 更新上次回合的开始时间
		last_turn_start = std::chrono::steady_clock::now();
		second = time(NULL); // 记录当前时间
		s.show(mychs, user); // 显示棋局
		BeginBatchDraw(); // 开始批量绘制
		double time_diff = difftime(second, first); // 计算两次时间差
		int minutes = static_cast<int>((int)time_diff / 60); // 计算分钟数
		int seconds = static_cast<int>((int)time_diff % 60); // 计算秒数
		std::string turntimeshow = std::to_string(minutes) + "min: " + std::to_string(seconds) + "s"; // 构建计时器显示字符串
		FlushBatchDraw(); // 刷新绘图
		EndBatchDraw(); // 结束批量绘制
		if (mychs.gameOver(s, user)) { // 检查是否达到游戏结束条件
			map = cop; // 恢复地图状态
			mychs.steps = 0; // 重置棋局步数
			continue; // 继续下一轮循环
		}
	}
	// 停止计时器线程
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




//主页面绘制函数
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
				setcolor(BLACK);
			}
			/*if (x >= 340 && x <= 460 && y >= 400 && y <= 440)
			{
				setcolor(RED);                              //函数将当前画笔颜色设置为黑色。
				rectangle(340, 200, 460, 240);              // 绘制矩形
				outtextxy(370, 210, L"玩家对战");            // 输出文本// 在鼠标位置处画一个圆圈，表示可以下
			}*/
			else if (x >= 340 && x <= 460 && y >= 500 && y <= 540)
			{
				setcolor(RED);                              //函数将当前画笔颜色设置为黑色。
				rectangle(340, 500, 460, 540);              // 绘制矩形
				outtextxy(370, 510, L"先手");            // 输出文本// 在鼠标位置处画一个圆圈，表示可以下
				setcolor(BLACK);
			}
			else if (x >= 340 && x <= 460 && y >= 540 && y <= 580)
			{
				setcolor(RED);                              //函数将当前画笔颜色设置为黑色。
				rectangle(340, 540, 460, 580);              // 绘制矩形
				outtextxy(370, 550, L"后手");            // 输出文本// 在鼠标位置处画一个圆圈，表示可以下
				setcolor(BLACK);
			}
			else if (x >= 340 && x <= 460 && y >= 300 && y <= 340)
			{
				setcolor(RED);                              //函数将当前画笔颜色设置为黑色。
				rectangle(340, 300, 460, 340);              // 绘制矩形
				outtextxy(370, 310, L"残局闯关");            // 输出文本// 在鼠标位置处画一个圆圈，表示可以下
				setcolor(BLACK);
			}
			else if (x >= 340 && x <= 460 && y >= 100 && y <= 140)
			{
				setcolor(RED);                              //函数将当前画笔颜色设置为黑色。
				rectangle(340, 100, 460, 140);              // 绘制矩形
				outtextxy(370, 110, L"联网对战");            // 输出文本// 在鼠标位置处画一个圆圈，表示可以下
				setcolor(BLACK);
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

		case WM_LBUTTONUP: // 处理鼠标左键抬起事件
			if (x >= 340 && x <= 460 && y >= 540 && y <= 580) {
				f = 0; // 设置 f 变量为 0
				firstorsecond = 0; // 设置 firstorsecond 变量为 0
			}
			else if (x >= 340 && x <= 460 && y >= 200 && y <= 240) {
				b = 0; // 设置 b 变量为 0
				int done = computer_and_player(); // 调用 computer_and_player() 函数，并将返回值赋给 done 变量
				return 0; // 返回 0
			}
			else if (x >= 340 && x <= 460 && y >= 400 && y <= 440) {
				d = 0; // 设置 d 变量为 0
				int done = player_and_player(); // 调用 player_and_player() 函数，并将返回值赋给 done 变量
				return 0; // 返回 0
			}
			else if (x >= 340 && x <= 460 && y >= 300 && y <= 340) {
				c = 0; // 设置 c 变量为 0
				int done = end_game(); // 调用 end_game() 函数，并将返回值赋给 done 变量
				return 0; // 返回 0
			}
			else if (x >= 340 && x <= 460 && y >= 100 && y <= 140) {
				a = 0; // 设置 a 变量为 0
				int done = online_player(); // 调用 online_player() 函数，并将返回值赋给 done 变量
				return 0; // 返回 0
			}
			else if (x >= 340 && x <= 460 && y >= 500 && y <= 540) {
				e = 0; // 设置 e 变量为 0
			}
			break;
		}
	}
}


