#include "include.h"

const int INF = 1000000000000;                //Alpha,beta
const int MAXN = 18;                          // 棋盘大小
const int MAXM = 324;                         // 棋盘格子数

extern std::vector<vector<int>> map;          //抽象后的地图
extern int aiset;                             //ai决策结果
extern double aiPos, myPos;                   //我方和电脑棋局得分


/*alpha-beta*/
// 评估一个棋盘的得分值
int Get_Points(vector<vector<int>>& map, int player);

// 判断五子棋棋局是否结束
bool Is_Game_Over(vector<vector<int>>& map, int player);

int Get_Points(int x, int y, int player, const vector<vector<int>>& map);

// 递归搜索函数

// Zobrist哈希
unsigned long long zobrist_hash[MAXM][3];
unsigned long long zobrist_key = 0;

// Zobrist哈希初始化
void Zobrist_Init() {
	srand(time(NULL));
	for (int i = 0; i < MAXM; i++) {
		for (int j = 0; j < 3; j++) {
			zobrist_hash[i][j] = ((unsigned long long)rand() << 32) | rand();
		}
	}
	zobrist_key = ((unsigned long long)rand() << 32) | rand();
}

// 计算当前棋盘的哈希值
unsigned long long Zobrist_Hash(vector<vector<int>>& map) {
	unsigned long long res = 0;
	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXN; j++) {
			if (map[i][j] != -1) {
				int k = (map[i][j] == 0) ? 0 : 1;
				res ^= zobrist_hash[i * MAXN + j][k];
			}
		}
	}
	res ^= zobrist_key;
	return res;
}

// αβ剪枝函数
int AlphaBeta(vector<vector<int>>& map, int depth, int alpha, int beta, bool max_player, int& best_x, int& best_y, unordered_map<unsigned long long, int>& cache) {
	unsigned long long hash_value = Zobrist_Hash(map);
	if (cache.count(hash_value) > 0) 
	{
		return cache[hash_value];
	}

	if (depth == 0 || Is_Game_Over(map, 0) || Is_Game_Over(map, 1)) 
	{
		return Get_Points(best_x, best_y, max_player ? 0 : 1, map);
	}

	int n = map.size();
	int m = map[0].size();
	int best_score = max_player ? INT_MIN : INT_MAX;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j] == -1) {
				map[i][j] = max_player ? 0 : 1;
				int score = AlphaBeta(map, depth - 1, alpha, beta, !max_player, best_x, best_y, cache);
				map[i][j] = -1;
				if (max_player) {
					if (score > best_score) {
						best_score = score;
						best_x = i;
						best_y = j;
						alpha = max(alpha, best_score);
						if (alpha >= beta) {
							return best_score;
						}
					}
				}
				else {
					if (score < best_score) {
						best_score = score;
						best_x = i;
						best_y = j;
						beta = min(beta, best_score);
						if (beta <= alpha) {
							return best_score;
						}
					}
				}
			}
		}
	}
	cache[hash_value] = best_score;
	return best_score;
}

// 判断五子棋棋局是否结束
bool Is_Game_Over(vector<vector<int>>& map, int player)
{
	int n = map.size();
	int m = map[0].size();

	// 横向检查
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= m - 5; j++) {
			bool flag = true;
			for (int k = 0; k < 5; k++) {
				if (map[i][j + k] != player) 
				{
					flag = false;
					break;
				}
			}
			if (flag) {
				return true;
			}
		}
	}

	// 纵向检查
	for (int i = 0; i <= n - 5; i++) {
		for (int j = 0; j < m; j++) {
			bool flag = true;
			for (int k = 0; k < 5; k++) {
				if (map[i + k][j] != player) {
					flag = false;
					break;
				}
			}
			if (flag) {
				return true;
			}
		}
	}

	// 正对角线检查
	for (int i = 0; i <= n - 5; i++) {
		for (int j = 0; j <= m - 5; j++) {
			bool flag = true;
			for (int k = 0; k < 5; k++) {
				if (map[i + k][j + k] != player) {
					flag = false;
					break;
				}
			}
			if (flag) {
				return true;
			}
		}
	}

	// 反对角线检查
	for (int i = 4; i < n; i++) {
		for (int j = 0; j <= m - 5; j++) {
			bool flag = true;
			for (int k = 0; k < 5; k++) {
				if (map[i - k][j + k] != player) {
					flag = false;
					break;
				}
			}
			if (flag) {
				return true;
			}
		}
	}

	return false;
}

int Get_Points(int x, int y, int player, const vector<vector<int>>& map){
	int n = map.size();
	int m = map[0].size();
	int dx[4] = { 0, 1, 1, 1 };
	int dy[4] = { 1, 1, 0, -1 };
	int score = 0;
	for (int k = 0; k < 4; k++) {
		int count = 1;
		bool blocked1 = false;
		bool blocked2 = false;
		for (int step = 1; step < 5; step++) {
			int new_x = x + step * dx[k];
			int new_y = y + step * dy[k];
			if (new_x < 0 || new_x >= n || new_y < 0 || new_y >= m || map[new_x][new_y] == (player ^ 1)) {
				blocked1 = true;
				break;
			}
			if (map[new_x][new_y] == -1) {
				blocked2 = true;
				break;
			}
			count++;
		}
		for (int step = 1; step < 5; step++) {
			int new_x = x - step * dx[k];
			int new_y = y - step * dy[k];
			if (new_x < 0 || new_x >= n || new_y < 0 || new_y >= m || map[new_x][new_y] == (player ^ 1)) {
				blocked1 = true;
				break;
			}
			if (map[new_x][new_y] == -1) {
				blocked2 = true;
				break;
			}
			count++;
		}
		if (!blocked1) {
			if (count == 5) {
				score += 10000;
			}
			else if (count == 4) {
				if (!blocked2) {
					score += 5000;
				}
				else {
					score += 50;
				}
			}
			else if (count == 3) {
				if (!blocked2) {
					score += 1000;
				}
				else {
					score += 5;
				}
			}
			else if (count == 2) {
				if (!blocked2) {
					score += 10;
				}
			}
		}
	}
	return score;
}

/*alpha-beta*/

//类的函数的重载



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
			} while (visit[i][j] != -1);
			visit[i][j] = 0;
			points = Get_Points(i, j, 1);
			points = Get_Points(i, j, 1);	//计算当前位置的得

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

		aiset = (maxx << 5) | maxy;        //将最大得分的坐标转化为二进制
		map[maxx][maxy] = 0;               //下棋
	}

	myPos = mychs.GetNowPoints(1);      //己方得分
	aiPos = mychs.GetNowPoints(0);      //敌方得分

	Sleep(500);	              //为了让上一次的音效播放完，必须让他停顿一会
	mciSendString(_T("close chs"), NULL, 0, NULL);//表示关闭一个名为chs的设备
	mciSendString(_T("open setChs.wav alias chs"), NULL, 0, NULL);//打开一个名为setChs.wav的音效文件
	mciSendString(_T("play chs"), NULL, 0, NULL); //播放名为chs的设备
	return;
}

/*优化算法*/

/*优化算法*/

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


