//��ĺ���������

#include "include.h"

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
			}
			while (visit[i][j] != -1);
			visit[i][j] = 0;
			points = Get_Points(i, j, 1);
			
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
	}

	myPos = mychs.GetNowPoints(1);      //�����÷�
	aiPos = mychs.GetNowPoints(0);      //�з��÷�

	Sleep(500);	              //Ϊ������һ�ε���Ч�����꣬��������ͣ��һ��
	mciSendString(_T("close chs"), NULL, 0, NULL);//��ʾ�ر�һ����Ϊchs���豸
	mciSendString(_T("open setChs.wav alias chs"), NULL, 0, NULL);//��һ����ΪsetChs.wav����Ч�ļ�
	mciSendString(_T("play chs"), NULL, 0, NULL); //������Ϊchs���豸
	return ;
}

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

