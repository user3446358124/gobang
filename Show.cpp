#include "include.h"

extern int aiset;                                     //记录电脑上一步下的位置
extern stack<pair<int, int>> stk;                     //用以控制悔棋-待删除
extern vector<vector<int>> map;                       //map是棋盘，-1空，0电脑，1友方
extern double myPos, aiPos;                           //我方和电脑棋局得分
static const char dir1[] = { "ABCDEFGHIJKLMNOPQR" };  //
static const char dir2[] = { "123456789ABCDEFGHI" };  //

void Show::show(MyChess& mychs, Users& user)
{
	BeginBatchDraw();                                 //函数表示开始一批次的绘制，可以将多个图形一次性绘制出来，提高绘制效率。
	setbkcolor(WHITE);                           //设置背景颜色为黄色
	cleardevice();                                    //清空屏幕并用当前背景色填充整个屏幕。
	setcolor(BLACK);                              //函数将当前画笔颜色设置为黑色。
	TCHAR row, col;                                   //可以是w_chat


	for (int i = 20; i <= 530; i += 30)               //画横竖线
	{
		line(20, i, 530, i);  
		line(i, 20, i, 530);
		row = dir1[reswitch_xy(i)];                   //花横竖坐标
		col = dir2[reswitch_xy(i)];
		outtextxy(5, i - 7, row);
		outtextxy(i - 5, 545, col);
	}

	/*4个小黑点*/
	setfillcolor(BLACK);
	fillcircle(170, 170, 3);
	fillcircle(170, 380, 3);
	fillcircle(380, 170, 3);
	fillcircle(380, 380, 3);

	for (int i = 0; i < 18; i++) 
	{
		for (int j = 0; j < 18; j++) 
		{
			if (map[i][j] != -1) 
			{
				setChess(switch_xy(i), switch_xy(j), map[i][j]);
			}
		}
	}

	TCHAR str[250];
	wchar_t* wstr = new wchar_t[100];
	//double nowTime = clock(), sec = 20 - ((nowTime - startTime) / CLOCKS_PER_SEC);
	mychs.get_grade(user, wstr);
	setcolor(BLACK);
	/*显示用户信息*/
	outtextxy(600, 5, _T("用户：challger"));
	_stprintf_s(str, _T("胜场：%d"), user.wincnt);
	outtextxy(600, 25, str);
	_stprintf_s(str, _T("负场：%d"), user.failcnt);
	outtextxy(600, 45, str);
	_stprintf_s(str, _T("平局：%d"), user.drawcnt);
	outtextxy(600, 65, str);
	_stprintf_s(str, _T("胜率：%.2f%%"), user.failcnt ? (double)user.wincnt / (double)(user.wincnt + user.failcnt) * 100: 0);
	outtextxy(600, 85, str);
	_stprintf_s(str, _T("段位：%s"), wstr);
	outtextxy(600, 105, str);
	_stprintf_s(str, _T("胜场最短步数: %d"), user.minsteps);
	outtextxy(600, 125, str);
	_stprintf_s(str, _T("剩余悔棋步数: %d"), user.restcnt);
	outtextxy(600, 145, str);

	setcolor(YELLOW);                                 //右上角 画方框
	line(580, 2, 580, 170);
	line(580, 170, 735, 170);
	line(735, 170, 735, 2);
	line(580, 2, 735, 2);
	setcolor(BLACK);

// 显示当前步数 注意绘图时的坐标是逆的，它的 y 轴是向下的
	_stprintf_s(str, _T("您当前走了 %d 步"), mychs.steps);
	outtextxy(600, 195, str);

	// 显示当前鼠标的行列信息
	outtextxy(600, 225, _T("当前鼠标行列："));

	// 绘制“悔棋”按钮
	setcolor(RED);
	rectangle(620, 265, 680, 305);
	outtextxy(634, 276, _T("悔棋"));
	setcolor(BLACK);

	// 显示电脑刚才所下的位置
	_stprintf_s(str, _T("电脑刚才所下位置：%c行 %c列"), dir1[aiset & 0x1f], dir2[aiset >> 5]);
	outtextxy(570, 330, str);

	// 显示当前棋局得分
	_stprintf_s(str, _T("您的棋局得分: %.1f"), myPos);
	outtextxy(570, 370, str);
	_stprintf_s(str, _T("对方棋局得分: %.1f"), aiPos);
	outtextxy(570, 410, str);

	//胜率
	_stprintf_s(str, _T("您目前的胜率为：%.2f%%"), 100 * myPos / (myPos + aiPos));
	outtextxy(570, 450, str);

	// 显示当前局面评估信息
	mychs.get_assuse(wstr);
	_stprintf_s(str, _T("当前您的棋局评估：%s"), wstr);
	outtextxy(570, 490, str);

	// 显示当前回合信息
	if (mychs.now == true)
	{
		outtextxy(180, 595, _T("现在是您的回合，请下棋..."));
	}
	else
	{
		outtextxy(160, 595, _T("现在是对方的回合，请您等待..."));
	}

	FlushBatchDraw();
	EndBatchDraw();
	return;
}


void Show::setChess(int x, int y, int choice)//0为电脑下棋，1为自己下棋
{
	setfillcolor(RED);                   //悔棋部分
	if (!choice) 
		setfillcolor(BLACK);
	fillcircle(x, y, 14);
	return;
}

void Show::Mouse(MyChess& mychs, Users& user)
{
	MOUSEMSG m; // 定义鼠标消息对象
	while (true) // 循环监听鼠标事件
	{
		TCHAR str[250];																 // 定义字符数组，用于存储要输出的字符串
		m = GetMouseMsg();															 // 获取鼠标消息
		int x = m.x, y = m.y;														 // 获取鼠标位置
		switch (m.uMsg)																 // 根据消息类型做出不同的处理
		{
		case WM_MOUSEMOVE:                                                           // 鼠标移动事件
			show(mychs, user);                                                   // 显示游戏界面
			if (mychs.Get_xy(x, y) && map[reswitch_xy(x)][reswitch_xy(y)] == -1) // 如果鼠标在棋盘内并且当前位置未落子
			{
				int x1 = reswitch_xy(x), y1 = reswitch_xy(y);                        // 转换成棋盘坐标
				_stprintf_s(str, _T("%c行 %c列"), dir1[y1], dir2[x1]);        // 格式化要输出的字符串
				outtextxy(705, 225, str);                                         // 输出字符串
				circle(x, y, 14);                                                // 在鼠标位置处画一个圆圈，表示可以下棋
			}
			else if (m.x > 620 && m.x < 680 && m.y > 265 && m.y < 305)               // 如果鼠标在悔棋按钮范围内
			{
				setcolor(BLUE);                                                  // 改变画笔颜色为蓝色
				rectangle(620, 265, 680, 305);                         // 画一个蓝色的矩形框
				outtextxy(634, 276, _T("悔棋"));                                // 输出“悔棋”字符串
				setcolor(BLACK);                                                 // 改变画笔颜色为黑色
			}
			break;

		case WM_LBUTTONUP:
			/*下棋*/
			if (mychs.Get_xy(x, y) && map[reswitch_xy(x)][reswitch_xy(y)] == -1)
			{
				int x1 = reswitch_xy(x), y1 = reswitch_xy(y);    
				stk.push({ aiset, (x1 << 5) | y1 });                        //将下棋坐标和当前AI的坐标压入栈中（用于悔棋操作）。
				map[x1][y1] = 1;                                                     //标记棋盘上该位置为已下棋。
				mychs.now = false;													//更新棋手状态（AI->玩家）。												
				mychs.steps++;														//更新棋手步数。
				myPos = mychs.GetNowPoints(1);									//获取当前玩家和AI的棋子位置信息。
				aiPos = mychs.GetNowPoints(0);
				mciSendString(_T("close chs"), NULL, 0, NULL); //播放下棋音效。
				mciSendString(_T("open setChs.wav alias chs"), NULL, 0, NULL);
				mciSendString(_T("play chs"), NULL, 0, NULL);
				return;
			}
			/*悔棋*/
			else if (m.x > 620 && m.x < 680 && m.y > 265 && m.y < 305)
			{
				if (!user.restcnt) // 如果没有悔棋次数了
				{
					MessageBox(0, _T("您没有悔棋机会了，加油赢棋以获得更多机会吧！"), _T("NO"), 0); // 显示提示信息
					continue; // 继续循环等待鼠标事件
				}
				if (stk.empty()) // 如果当前没有可以悔棋的步骤
				{
					MessageBox(0, _T("现在无法悔棋！"), _T("NO"), 0); // 显示提示信息
					continue; // 继续循环等待鼠标事件
				}
				auto it = stk.top(); // 取出栈顶元素，即悔棋时保存的AI和自己的位置信息
				stk.pop(); // 弹出栈顶元素
				int ai = it.first, self = it.second; // 分别取出AI和自己的位置信息
				map[self >> 5][self & 0x1f] = -1; // 将自己的位置信息从地图上清除
				map[aiset >> 5][aiset & 0x1f] = -1; // 将AI的位置信息从地图上清除
				aiset = ai; // 将保存的AI位置信息重新设置到aiset中，以便下一步AI落子

				myPos = mychs.GetNowPoints(1); // 更新自己和AI的棋子分布情况
				aiPos = mychs.GetNowPoints(0);
				user.restcnt--; // 将剩余悔棋次数减1
				user.Write(); // 将剩余悔棋次数写入文件
				show(mychs, user); // 重新绘制棋盘和相关信息
				return Mouse(mychs, user); // 继续等待鼠标事件
			}
		}
	}
	return;
}

void Show::End(int who, Users& user, int steps)
{
	if (!who) 
		return; 
	LOGFONT f;                              //描述字体属性的结构体
	gettextstyle(&f);						// 获取当前字体设置
	f.lfHeight = 20;						// 设置字体高度为 48
	wcscpy_s(f.lfFaceName, _T("宋体"));		// 设置字体为“宋体”(高版本 VC 推荐使用 _tcscpy_s 函数)
	f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
	settextstyle(&f);						// 设置字体样式
	outtextxy(615, 500, _T("游戏结束"));

	/*这段代码是一个条件语句，根据变量 `who` 的值来弹出不同的提示框，表示游戏的胜利或失败，并根据胜利或失败来执行相应的操作。具体来说：

- 如果 `who` 的值为 1，表示玩家获胜，弹出一个消息框提示玩家胜利，并在屏幕上输出“恭喜您胜利！”的字样，同时更新用户胜利次数和剩余悔棋次数，并播放“win.wav”的声音。
- 如果 `who` 的值不为 1，表示玩家失败，弹出一个消息框提示玩家失败，并在屏幕上输出“您失败了，不要灰心下次再来吧！”的字样，同时更新用户失败次数，并播放“defet.mp3”的声音。
- 在两种情况下都清除屏幕上的内容，并在玩家获胜时显示“恭喜您胜利！”，在玩家失败时显示“您失败了，不要灰心下次再来吧！”。
- 在玩家失败时，还会在屏幕上输出“请按任意键继续游戏...”，提示玩家可以按任意键继续游戏。*
- 在两种情况下都调用了 `mciSendString` 函数来播放相应的声音文件。*/

	if (who == 1) 
	{
		MessageBox(0, _T("恭喜您胜利！"), _T("YES"), 0);
		setbkcolor(GREEN);
		cleardevice();
		outtextxy(250, 200, _T("恭喜您胜利！"));	
		//outtextxy(250, 300, _T("请按任意键继续游戏..."));
		user.wincnt++;
		user.restcnt += 10;
		if (user.minsteps == 0)
			user.minsteps = steps;
		else
			user.minsteps = min(user.minsteps, steps);
		mciSendString(_T("close win"), NULL, 0, NULL);
		mciSendString(_T("open win.wav alias win"), NULL, 0, NULL);
		mciSendString(_T("play win"), NULL, 0, NULL);
	}
	else 
	{
		MessageBox(0, _T("您失败了，不要灰心下次再来吧！！"), _T("NO"), 0);
		setbkcolor(GREEN);
		cleardevice();
		outtextxy(250, 200, _T("您失败了，不要灰心下次再来吧！"));
		outtextxy(250, 300, _T("请按任意键继续游戏..."));
		mciSendString(_T("close det"), NULL, 0, NULL);
		mciSendString(_T("open defet.mp3 alias det"), NULL, 0, NULL);
		mciSendString(_T("play det"), NULL, 0, NULL);
		user.failcnt++;
	}

	user.Write();
	int ch = _gettch();          //这个函数返回输入的字符的ASCII码或者扫描码。

	while (!stk.empty())		 //归零
		stk.pop();
	aiPos = 0;
	myPos = 0;
	closegraph();
	return;
}

