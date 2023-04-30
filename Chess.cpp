//类的函数的重载

#include "include.h"

extern std::vector<vector<int>> map;          //抽象后的地图
extern int aiset;                             //ai决策结果
extern double aiPos, myPos;                   //我方和电脑棋局得分

/*判断鼠标是否落入空交点内*/
int MyChess::Get_xy(int& x, int& y)           
{
	for (int i = 0; i < 18; i++)              //18列 18行
	{
		for (int j = 0; j < 18; j++)          //switch_xy 将坐标转化为实际位置
		{
			if ((x - switch_xy(i)) * (x - switch_xy(i)) + (y - switch_xy(j)) * (y - switch_xy(j)) <= 36) 
			{
				x = switch_xy(i);
				y = switch_xy(j);
				return 1;
			}
		}
	}
	return 0;
}

/*获取得分最高的位置，并下棋*/
void AiChess::Get_key_Setchess(MyChess& mychs)
{
	if (mychs.steps == 0)                     //开始时走天元
	{
		map[8][8] = 0;                        
		aiset = 0x108;                        //清零
	}
	else 
	{
		int points, maxpoints = -1;          //表示当前位置的得分,表示最大的得分
		int maxx = 0, maxy = 0;              //maxx和maxy表示最大得分对应的坐标
		int book = 0;                        //book表示已经遍历过的位置的数量
		int cnt = 324 - 2 * mychs.steps;     //cnt表示需要遍历的总位置的数量
		vector<vector<int>> visit(map);      //记录哪些位置已经被访问过了

		while (book != cnt)                  //记录当前需要遍历的次数
		{
			int i, j;

			srand((unsigned)time(0));        //使得电脑下棋尽可能随机化
			do
			{
				i = rand() % 18;
				j = rand() % 18;
			}
			while (visit[i][j] != -1);
			visit[i][j] = 0;
			points = Get_Points(i, j, 1);
			
			if (points > maxpoints)         //获取最大的分点
			{
				maxpoints = points;
				maxx = i;
				maxy = j;
			}
			book++;
		}

		aiset = (maxx << 5) | maxy;
		map[maxx][maxy] = 0;
	}

	myPos = mychs.GetNowPoints(1);      //己方得分
	aiPos = mychs.GetNowPoints(0);      //敌方得分

	Sleep(500);	              //为了让上一次的音效播放完，必须让他停顿一会
	mciSendString(_T("close chs"), NULL, 0, NULL);//表示关闭一个名为chs的设备
	mciSendString(_T("open setChs.wav alias chs"), NULL, 0, NULL);//打开一个名为setChs.wav的音效文件
	mciSendString(_T("play chs"), NULL, 0, NULL); //播放名为chs的设备
	return ;
}

/* 计算棋子在指定位置的得分*/
int Chess::Get_Points(int x, int y, int ch)
{
	int ret = 0;                                                // 初始化总得分
	int x1(x), y1(y), x2(x), y2(y), x3(x), y3(y), x4(x), y4(y); // 初始化四个方向的坐标

	for (int i = 0; i < 5; i++)                                 // 遍历四个方向的连续棋子
	{
		if (is_Ok(x1, y1))                                      // 如果当前坐标在棋盘内
		{
			ret += xy_Points(Get_Nums1(x1, y1), ch);             // 根据棋子种类和该位置的棋子数量计算得分
			y1++;
		}
		if (is_Ok(x2, y2))                                      // 如果当前坐标在棋盘内
		{
			ret += xy_Points(Get_Nums2(x2, y2), ch);				// 根据棋子种类和该位置的棋子数量计算得分
			x2++;
		}
		if (is_Ok(x3, y3))                                      // 如果当前坐标在棋盘内
		{
			ret += xy_Points(Get_Nums3(x3, y3), ch);				// 根据棋子种类和该位置的棋子数量计算得分
			x3--, y3++;
		}
		if (is_Ok(x4, y4))                                      // 如果当前坐标在棋盘内
		{
			ret += xy_Points(Get_Nums4(x4, y4), ch);				// 根据棋子种类和该位置的棋子数量计算得分
			x4++, y4++;
		}
	}

	return ret;                                                 // 返回总得分
}

/*获取指定位置(x,y)横向连续五个棋子的黑白数量*/
vector<int> Chess::Get_Nums1(int x, int y)
{
	int k = 0, t = 0, cnt = 5;                                 // k记录黑棋数量，t记录白棋数量，cnt记录检测剩余格子数

	while (cnt-- && is_Ok(x, y))                               // 判断剩余格子数和是否越界
	{
		if (map[x][y] == 0)                                    // 如果当前位置为黑棋
			k++;                                               // 黑棋数量加1
		if (map[x][y] == 1)                                    // 如果当前位置为白棋
			t++;                                               // 白棋数量加1
		y--;                                                   // 继续检测下一格
	}

	if (cnt >= 0)                                              // 如果剩余格子数大于等于0，说明未找到连续五个棋子，返回空vector
		return {};
	return vector<int>({ k, t });                          // 返回黑白数量
}

/*获取指定位置(x,y)横向连续五个棋子的黑白数量*/
vector<int> Chess::Get_Nums2(int x, int y)
{
	int k = 0, t = 0, cnt = 5;

	while (cnt-- && is_Ok(x, y))                              // 向左遍历5个位置
	{
		if (map[x][y] == 0)
			k++;                                              // 统计0的数量
		if (map[x][y] == 1)
			t++;                                              // 统计1的数量
		x--;
	}

	if (cnt >= 0)
		return {};                                        // 如果超出边界，返回空vector

	return vector<int>({ k, t });                        // 返回0和1的数量
}

/*获取指定位置(x,y)横向连续五个棋子的黑白数量*/
vector<int> Chess::Get_Nums3(int x, int y)
{
	int k = 0, t = 0, cnt = 5;

	while (cnt-- && is_Ok(x, y))                            // 向左上遍历5个位置
	{
		if (map[x][y] == 0)
			k++;                                            // 统计0的数量
		if (map[x][y] == 1)
			t++;                                            // 统计1的数量
		x++, y--;
	}

	if (cnt >= 0)
		return {};                                      // 如果超出边界，返回空vector

	return vector<int>({ k,t });                       // 返回0和1的数量
}

/*获取指定位置(x,y)横向连续五个棋子的黑白数量*/
vector<int> Chess::Get_Nums4(int x, int y)
{
	int k = 0, t = 0, cnt = 5;

	while (cnt-- && is_Ok(x, y))                          // 向右上遍历5个位置
	{
		if (map[x][y] == 0)
			k++;                                          // 统计0的数量
		if (map[x][y] == 1)
			t++;                                          // 统计1的数量
		x--, y--;
	}

	if (cnt >= 0)
		return {};                                     // 如果超出边界，返回空vector

	return vector<int>({ k,t });                      // 返回0和1的数量
}

/*通过双方棋子 通过加权 判断位置价值*/
int Chess::xy_Points(vector<int> nums, int ch)
{
	if (nums.empty())	
		return 0;

	int g, b;

	if (ch)		 
		g = nums[0], b = nums[1];                         //g是我方，b是电脑，ch = 1则获取电脑得分
	else         
		g = nums[1], b = nums[0];                         //g是电脑，b是我方，ch = 0则获取我方得分

	if (g == 0 && b == 0)		                          //加权 结合双方 判断位置价值
		return 10;
	else if (g == 1 && b == 0)	
		return 35;
	else if (g == 2 && b == 0)	
		return 1500;
	else if (g == 3 && b == 0)	
		return 18000;
	else if (g == 4 && b == 0)	
		return 1000000;
	else if (g == 0 && b == 1)	
		return 15;
	else if (g == 0 && b == 2)	
		return 400;
	else if (g == 0 && b == 3)	
		return 6000;
	else if (g == 0 && b == 4)	
		return 150000;
	else if (g != 0 && b != 0)	
		return 0;

	return 0;
}

/*遍历 评估位置的优劣*/
double Chess::GetNowPoints(int ch)
{
	double ret = 0;
	for (int i = 0; i < 18; i++) 
	{
		for (int j = 0; j < 18; j++) 
		{
			if (map[i][j] == ch) 
			{
				ret += Get_Points(i, j, ch) / 100.0;
			}
		}
	}
	return ret;
}

/*对方 判断 是否胜利*/
bool AiChess::gameOver(Show s, Users& user)
{
	for (int i = 0; i < 18; i++) 
	{
		for (int j = 0; j < 18; j++) 
		{
			if (map[i][j] == 0 && win(i, j)) 
			{
				s.End(-1, user, 0);
				return true;
			}
		}
	}
	return false;
}

/*我方 判断 是否胜利*/
bool MyChess::gameOver(Show s, Users& user)
{
	for (int i = 0; i < 18; i++) 
	{
		for (int j = 0; j < 18; j++) 
		{
			if (map[i][j] == 1 && win(i, j)) 
			{
				s.End(1, user, steps);
				return true;
			}
		}
	}
	return false;
}

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

