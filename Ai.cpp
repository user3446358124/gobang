#include "include.h"

const int INF = 1000000000000;                //Alpha,beta
const int MAXN = 18;                          // ���̴�С
const int MAXM = 324;                         // ���̸�����

extern std::vector<vector<int>> map;          //�����ĵ�ͼ
extern int aiset;                             //ai���߽��
extern double aiPos, myPos;                   //�ҷ��͵�����ֵ÷�


/*alpha-beta*/
// ����һ�����̵ĵ÷�ֵ
int Get_Points(vector<vector<int>>& map, int player);

// �ж�����������Ƿ����
bool Is_Game_Over(vector<vector<int>>& map, int player);

int Get_Points(int x, int y, int player, const vector<vector<int>>& map);

// �ݹ���������

// Zobrist��ϣ
unsigned long long zobrist_hash[MAXM][3];
unsigned long long zobrist_key = 0;

// Zobrist��ϣ��ʼ��
void Zobrist_Init() {
	srand(time(NULL));
	for (int i = 0; i < MAXM; i++) {
		for (int j = 0; j < 3; j++) {
			zobrist_hash[i][j] = ((unsigned long long)rand() << 32) | rand();
		}
	}
	zobrist_key = ((unsigned long long)rand() << 32) | rand();
}

// ���㵱ǰ���̵Ĺ�ϣֵ
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

// ���¼�֦����
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

// �ж�����������Ƿ����
bool Is_Game_Over(vector<vector<int>>& map, int player)
{
	int n = map.size();
	int m = map[0].size();

	// ������
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

	// ������
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

	// ���Խ��߼��
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

	// ���Խ��߼��
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

//��ĺ���������



extern std::vector<vector<int>> map;          //�����ĵ�ͼ
extern int aiset;                             //ai���߽��
extern double aiPos, myPos;                   //�ҷ��͵�����ֵ÷�


/*�ж�����Ƿ�����ս�����*/
int MyChess::Get_xy(int& x, int& y)
{
	for (int i = 0; i < 18; i++)              //18�� 18��
	{
		for (int j = 0; j < 18; j++)          //switch_xy ������ת��Ϊʵ��λ��
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



/*��ȡ�÷���ߵ�λ�ã�������*/
void AiChess::Get_key_Setchess(MyChess& mychs)
{
	if (mychs.steps == 0)                     //��ʼʱ����Ԫ
	{
		map[8][8] = 0;
		aiset = 0x108;                        //����
	}
	else
	{
		int points, maxpoints = -1;          //��ʾ��ǰλ�õĵ÷�,��ʾ���ĵ÷�
		int maxx = 0, maxy = 0;              //maxx��maxy��ʾ���÷ֶ�Ӧ������
		int book = 0;                        //book��ʾ�Ѿ���������λ�õ�����
		int cnt = 324 - 2 * mychs.steps;     //cnt��ʾ��Ҫ��������λ�õ�����
		vector<vector<int>> visit(map);      //��¼��Щλ���Ѿ������ʹ���

		while (book != cnt)                  //��¼��ǰ��Ҫ�����Ĵ���
		{
			int i, j;

			srand((unsigned)time(0));        //ʹ�õ������御���������
			do
			{
				i = rand() % 18;
				j = rand() % 18;
			} while (visit[i][j] != -1);
			visit[i][j] = 0;
			points = Get_Points(i, j, 1);
			points = Get_Points(i, j, 1);	//���㵱ǰλ�õĵ�

			if (points > maxpoints)         //��ȡ���ķֵ�
			{
				maxpoints = points;
				maxx = i;
				maxy = j;
			}
			book++;
		}

		aiset = (maxx << 5) | maxy;
		map[maxx][maxy] = 0;

		aiset = (maxx << 5) | maxy;        //�����÷ֵ�����ת��Ϊ������
		map[maxx][maxy] = 0;               //����
	}

	myPos = mychs.GetNowPoints(1);      //�����÷�
	aiPos = mychs.GetNowPoints(0);      //�з��÷�

	Sleep(500);	              //Ϊ������һ�ε���Ч�����꣬��������ͣ��һ��
	mciSendString(_T("close chs"), NULL, 0, NULL);//��ʾ�ر�һ����Ϊchs���豸
	mciSendString(_T("open setChs.wav alias chs"), NULL, 0, NULL);//��һ����ΪsetChs.wav����Ч�ļ�
	mciSendString(_T("play chs"), NULL, 0, NULL); //������Ϊchs���豸
	return;
}

/*�Ż��㷨*/

/*�Ż��㷨*/

/* ����������ָ��λ�õĵ÷�*/
int Chess::Get_Points(int x, int y, int ch)
{
	int ret = 0;                                                // ��ʼ���ܵ÷�
	int x1(x), y1(y), x2(x), y2(y), x3(x), y3(y), x4(x), y4(y); // ��ʼ���ĸ����������

	for (int i = 0; i < 5; i++)                                 // �����ĸ��������������
	{
		if (is_Ok(x1, y1))                                      // �����ǰ������������
		{
			ret += xy_Points(Get_Nums1(x1, y1), ch);             // ������������͸�λ�õ�������������÷�
			y1++;
		}
		if (is_Ok(x2, y2))                                      // �����ǰ������������
		{
			ret += xy_Points(Get_Nums2(x2, y2), ch);				// ������������͸�λ�õ�������������÷�
			x2++;
		}
		if (is_Ok(x3, y3))                                      // �����ǰ������������
		{
			ret += xy_Points(Get_Nums3(x3, y3), ch);				// ������������͸�λ�õ�������������÷�
			x3--, y3++;
		}
		if (is_Ok(x4, y4))                                      // �����ǰ������������
		{
			ret += xy_Points(Get_Nums4(x4, y4), ch);				// ������������͸�λ�õ�������������÷�
			x4++, y4++;
		}
	}

	return ret;                                                 // �����ܵ÷�
}

/*��ȡָ��λ��(x,y)��������������ӵĺڰ�����*/
vector<int> Chess::Get_Nums1(int x, int y)
{
	int k = 0, t = 0, cnt = 5;                                 // k��¼����������t��¼����������cnt��¼���ʣ�������

	while (cnt-- && is_Ok(x, y))                               // �ж�ʣ����������Ƿ�Խ��
	{
		if (map[x][y] == 0)                                    // �����ǰλ��Ϊ����
			k++;                                               // ����������1
		if (map[x][y] == 1)                                    // �����ǰλ��Ϊ����
			t++;                                               // ����������1
		y--;                                                   // ���������һ��
	}

	if (cnt >= 0)                                              // ���ʣ����������ڵ���0��˵��δ�ҵ�����������ӣ����ؿ�vector
		return {};
	return vector<int>({ k, t });                          // ���غڰ�����
}

/*��ȡָ��λ��(x,y)��������������ӵĺڰ�����*/
vector<int> Chess::Get_Nums2(int x, int y)
{
	int k = 0, t = 0, cnt = 5;

	while (cnt-- && is_Ok(x, y))                              // �������5��λ��
	{
		if (map[x][y] == 0)
			k++;                                              // ͳ��0������
		if (map[x][y] == 1)
			t++;                                              // ͳ��1������
		x--;
	}

	if (cnt >= 0)
		return {};                                        // ��������߽磬���ؿ�vector

	return vector<int>({ k, t });                        // ����0��1������
}

/*��ȡָ��λ��(x,y)��������������ӵĺڰ�����*/
vector<int> Chess::Get_Nums3(int x, int y)
{
	int k = 0, t = 0, cnt = 5;

	while (cnt-- && is_Ok(x, y))                            // �����ϱ���5��λ��
	{
		if (map[x][y] == 0)
			k++;                                            // ͳ��0������
		if (map[x][y] == 1)
			t++;                                            // ͳ��1������
		x++, y--;
	}

	if (cnt >= 0)
		return {};                                      // ��������߽磬���ؿ�vector

	return vector<int>({ k,t });                       // ����0��1������
}

/*��ȡָ��λ��(x,y)��������������ӵĺڰ�����*/
vector<int> Chess::Get_Nums4(int x, int y)
{
	int k = 0, t = 0, cnt = 5;

	while (cnt-- && is_Ok(x, y))                          // �����ϱ���5��λ��
	{
		if (map[x][y] == 0)
			k++;                                          // ͳ��0������
		if (map[x][y] == 1)
			t++;                                          // ͳ��1������
		x--, y--;
	}

	if (cnt >= 0)
		return {};                                     // ��������߽磬���ؿ�vector

	return vector<int>({ k,t });                      // ����0��1������
}

/*ͨ��˫������ ͨ����Ȩ �ж�λ�ü�ֵ*/
int Chess::xy_Points(vector<int> nums, int ch)
{
	if (nums.empty())
		return 0;

	int g, b;

	if (ch)
		g = nums[0], b = nums[1];                         //g���ҷ���b�ǵ��ԣ�ch = 1���ȡ���Ե÷�
	else
		g = nums[1], b = nums[0];                         //g�ǵ��ԣ�b���ҷ���ch = 0���ȡ�ҷ��÷�

	if (g == 0 && b == 0)		                          //��Ȩ ���˫�� �ж�λ�ü�ֵ
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

/*���� ����λ�õ�����*/
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

/*�Է� �ж� �Ƿ�ʤ��*/
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

/*�ҷ� �ж� �Ƿ�ʤ��*/
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


