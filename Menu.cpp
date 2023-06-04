#include "include.h"

#define _CRT_SECURE_NO_WARNINGS

constexpr int Width = 800;
constexpr int High = 640;
vector<vector<int>> map(18, vector<int>(18, -1)), cop(map);		//map�����̣�-1�գ�0���ԣ�1�ѷ�
stack<pair<int, int>> stk;			//���Կ��ƻ���-��ɾ��
double myPos = 0, aiPos = 0;		//�ҷ��͵�����ֵ÷�
int aiset;							//��¼������һ���µ�λ��
bool firstorsecond=1;
time_t first, second;
bool a, b, c, d, e, f;					//������ʾ
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

	BeginBatchDraw();                                 //������ʾ��ʼһ���εĻ��ƣ����Խ����ͼ��һ���Ի��Ƴ�������߻���Ч�ʡ�
	setbkcolor(WHITE);                            //���ñ�����ɫΪ��ɫ
	cleardevice();                                    //�����Ļ���õ�ǰ����ɫ���������Ļ��
	setcolor(BLACK);                              //��������ǰ������ɫ����Ϊ��ɫ��

	rectangle(340, 100, 460, 140); // ���ƾ���
	outtextxy(370, 110, L"����"); // ����ı�

	rectangle(340, 200, 460, 240); // ���ƾ���
	outtextxy(370, 210, L"����"); // ����ı�

	FlushBatchDraw();
	EndBatchDraw();
	MOUSEMSG m; // ���������Ϣ����
	while (true) // ѭ����������¼�
	{
		TCHAR str[250];																 // �����ַ����飬���ڴ洢Ҫ������ַ���
		m = GetMouseMsg();															 // ��ȡ�����Ϣ
		int x = m.x, y = m.y;														 // ��ȡ���λ��
		switch (m.uMsg)																 // ������Ϣ����������ͬ�Ĵ���
		{
		case WM_LBUTTONUP:                                                           // ����ƶ��¼�
			if (x >= 340 && x <= 460 && y >= 200 && y <= 240)
			{
				setcolor(RED);                              //��������ǰ������ɫ����Ϊ��ɫ��
				rectangle(340, 200, 460, 240);              // ���ƾ���
				outtextxy(370, 210, L"����"); // ����ı�
				firstorsecond = 1;
				return;
			}
			else if (x >= 340 && x <= 460 && y >= 100 && y <= 140)
			{
				setcolor(RED);                              //��������ǰ������ɫ����Ϊ��ɫ��
				rectangle(340, 200, 460, 240);              // ���ƾ���
				outtextxy(370, 210, L"����"); // ����ı�
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
	initgraph(Width, High+100); // ��ʼ����ͼ���ڴ�С

	while (true)
	{
		BeginBatchDraw(); // ��ʼһ���εĻ���

		setbkcolor(WHITE); // ���ñ�����ɫΪ��ɫ
		cleardevice();    // �����Ļ���õ�ǰ����ɫ���������Ļ
		setcolor(BLACK);  // ���û�����ɫΪ��ɫ

		MOUSEMSG m;       // ���������Ϣ����
		m = GetMouseMsg(); // ��ȡ�����Ϣ
		int x = m.x, y = m.y; // ��ȡ���λ��

		switch (m.uMsg) // ������Ϣ����������ͬ�Ĵ���
		{
		case WM_MOUSEMOVE: // ����ƶ��¼�
			if (x >= 340 && x <= 460 && y >= 200 && y <= 240)
			{
				setcolor(RED);
				rectangle(340, 200, 460, 240);
				outtextxy(370, 210, L"�ڶ���");
			}
			if (x >= 340 && x <= 460 && y >= 300 && y <= 340)
			{
				setcolor(RED);
				rectangle(340, 300, 460, 340);
				outtextxy(370, 310, L"������");
			}
			if (x >= 340 && x <= 460 && y >= 400 && y <= 440)
			{
				setcolor(RED);
				rectangle(340, 400, 460, 440);
				outtextxy(370, 410, L"���Ĺ�");
			}
			if (x >= 340 && x <= 460 && y >= 500 && y <= 540)
			{
				setcolor(RED);
				rectangle(340, 500, 460, 540);
				outtextxy(370, 510, L"�����");
			}
			if (x >= 340 && x <= 460 && y >= 600 && y <= 640)
			{
				setcolor(RED);
				rectangle(340, 600, 460, 640);
				outtextxy(370, 610, L"������");
			}
			if (x >= 340 && x <= 460 && y >= 100 && y <= 140)
			{
				setcolor(RED);
				rectangle(340, 100, 460, 140);
				outtextxy(370, 110, L"��һ��");
			}
			else
			{
				setcolor(BLACK);
				rectangle(340, 100, 460, 140);
				outtextxy(370, 110, L"��һ��");
				rectangle(340, 200, 460, 240);
				outtextxy(370, 210, L"�ڶ���");
				rectangle(340, 300, 460, 340);
				outtextxy(370, 310, L"������");
				rectangle(340, 400, 460, 440);
				outtextxy(370, 410, L"���Ĺ�");
				rectangle(340, 500, 460, 540);
				outtextxy(370, 510, L"�����");
				rectangle(340, 600, 460, 640);
				outtextxy(370, 610, L"������");
			}
			break;
		case WM_LBUTTONUP:
			if (x >= 340 && x <= 460 && y >= 200 && y <= 240)
			{
				filenum = 2;
				closegraph(); // �رջ�ͼ����
				return;       // ����ѡ��Ĺؿ�
			}
			else if (x >= 340 && x <= 460 && y >= 300 && y <= 340)
			{
				filenum = 3;
				closegraph(); // �رջ�ͼ����
				return;       // ����ѡ��Ĺؿ�
			}
			else if (x >= 340 && x <= 460 && y >= 400 && y <= 440)
			{
				filenum = 4;
				closegraph(); // �رջ�ͼ����
				return;       // ����ѡ��Ĺؿ�
			}
			else if (x >= 340 && x <= 460 && y >= 500 && y <= 540)
			{
				filenum = 5;
				closegraph(); // �رջ�ͼ����
				return;       // ����ѡ��Ĺؿ�
			}
			else if (x >= 340 && x <= 460 && y >= 600 && y <= 640)
			{
				filenum = 6;
				closegraph(); // �رջ�ͼ����
				return;       // ����ѡ��Ĺؿ�
			}
			else if (x >= 340 && x <= 460 && y >= 100 && y <= 140)
			{
				filenum = 1;
				closegraph(); // �رջ�ͼ����
				return;       // ����ѡ��Ĺؿ�
			}
			break;
		}

		FlushBatchDraw(); // ˢ�»�ͼ����
		EndBatchDraw();   // ����һ���εĻ���
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
		std::wstring global_timer_text = L"ȫ��ʱ�䣺 " + std::to_wstring(global_duration) + L"s";
		std::wstring turn_timer_text = L"�ִ�ʱ�䣺 " + std::to_wstring(last_turn_duration) + L"s";
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
	Users user;                     //��������

	std::mutex mt;                  //windows api ��������
	user.Read();                    //��Ϣ

	map = cop;
	mychs.steps = 0;
	initgraph(Width, High);

	bool isRunning = true;          //����һ������ѭ���ı���
	while (isRunning)
	{
		mychs.now = true;			//��Ļغ� set now = true
		s.Mouse(mychs, user);		//���ȷ��ѡ��,set now = false
		s.show(mychs, user);        //չʾ��ͼ
		if (mychs.gameOver(s, user))//�ж��Ƿ�ʤ��	
		{
			map = cop;              //���õ�ͼ
			mychs.steps = 0;        //���ò���
			continue;               //��������ѭ�������¿�ʼ
		}

		mychs.now = false;			//��Ļغ� set now = true
		s.Mouse(mychs, user);		//���ȷ��ѡ��,set now = false
		s.show(mychs, user);        //չʾ��ͼ
		if (mychs.gameOver(s, user))//�ж��Ƿ�ʤ��	
		{
			map = cop;              //���õ�ͼ
			mychs.steps = 0;        //���ò���
			continue;               //��������ѭ�������¿�ʼ
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
	Users user;                     //��������
	Readers readers;

	std::mutex mt;                  //windows api ��������
	user.Read();                    //��Ϣ

	BeginBatchDraw();                                 //������ʾ��ʼһ���εĻ��ƣ����Խ����ͼ��һ���Ի��Ƴ�������߻���Ч�ʡ�
	setbkcolor(WHITE);                            //���ñ�����ɫΪ��ɫ
	cleardevice();                                    //�����Ļ���õ�ǰ����ɫ���������Ļ��
	setcolor(BLACK);                              //��������ǰ������ɫ����Ϊ��ɫ��
	MOUSEMSG m; // ���������Ϣ����
	while (true) // ѭ����������¼�
	{
		TCHAR str[250];																 // �����ַ����飬���ڴ洢Ҫ������ַ���
		m = GetMouseMsg();															 // ��ȡ�����Ϣ
		int x = m.x, y = m.y;														 // ��ȡ���λ��
		switch (m.uMsg)																 // ������Ϣ����������ͬ�Ĵ���
		{
		case WM_MOUSEMOVE:                                                           // ����ƶ��¼�
			if (x >= 340 && x <= 460 && y >= 200 && y <= 240)
			{
				setcolor(RED);                              //��������ǰ������ɫ����Ϊ��ɫ��
				rectangle(340, 200, 460, 240);              // ���ƾ���
				outtextxy(370, 210, L"�˻���ս");            // ����ı�// �����λ�ô���һ��ԲȦ����ʾ������
			}
			/*if (x >= 340 && x <= 460 && y >= 400 && y <= 440)
			{
				setcolor(RED);                              //��������ǰ������ɫ����Ϊ��ɫ��
				rectangle(340, 200, 460, 240);              // ���ƾ���
				outtextxy(370, 210, L"��Ҷ�ս");            // ����ı�// �����λ�ô���һ��ԲȦ����ʾ������
			}*/
			if (x >= 340 && x <= 460 && y >= 500 && y <= 540)
			{
				setcolor(RED);                              //��������ǰ������ɫ����Ϊ��ɫ��
				rectangle(340, 500, 460, 540);              // ���ƾ���
				outtextxy(370, 510, L"����");            // ����ı�// �����λ�ô���һ��ԲȦ����ʾ������
			}
			if (x >= 340 && x <= 460 && y >= 540 && y <= 580)
			{
				setcolor(RED);                              //��������ǰ������ɫ����Ϊ��ɫ��
				rectangle(340, 540, 460, 580);              // ���ƾ���
				outtextxy(370, 550, L"����");            // ����ı�// �����λ�ô���һ��ԲȦ����ʾ������
			}
			if (x >= 340 && x <= 460 && y >= 300 && y <= 340)
			{
				setcolor(RED);                              //��������ǰ������ɫ����Ϊ��ɫ��
				rectangle(340, 300, 460, 340);              // ���ƾ���
				outtextxy(370, 310, L"�оִ���");            // ����ı�// �����λ�ô���һ��ԲȦ����ʾ������
			}
			if (x >= 340 && x <= 460 && y >= 100 && y <= 140)
			{
				setcolor(RED);                              //��������ǰ������ɫ����Ϊ��ɫ��
				rectangle(340, 100, 460, 140);              // ���ƾ���
				outtextxy(370, 110, L"������ս");            // ����ı�// �����λ�ô���һ��ԲȦ����ʾ������
			}
			else
			{
				setcolor(BLACK);                             //��������ǰ������ɫ����Ϊ��ɫ��
				if (a)
				{
					rectangle(340, 100, 460, 140); // ���ƾ���
					outtextxy(370, 110, L"������ս"); // ����ı�
				}
				if (b)
				{
					rectangle(340, 200, 460, 240); // ���ƾ���
					outtextxy(370, 210, L"�˻���ս"); // ����ı�
				}
				if (c)
				{
					rectangle(340, 300, 460, 340); // ���ƾ���
					outtextxy(370, 310, L"�оִ���"); // ����ı�
				}
				/*if (d)
				{
					rectangle(340, 400, 460, 440); // ���ƾ���
					outtextxy(370, 410, L"��Ҷ�ս"); // ����ı�
				}*/
				if (e)
				{
					rectangle(340, 500, 460, 540); // ���ƾ���
					outtextxy(370, 510, L"����"); // ����ı�
				}
				if (f)
				{
					rectangle(340, 540, 460, 580); // ���ƾ���
					outtextxy(370, 550, L"����"); // ����ı���
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
	EndBatchDraw(); //������ʾ����һ���εĻ��ƣ�����������ͼ��һ���Ի��Ƴ�����

	map = readers.read_map_from_file("level", map,1);
	mychs.steps = 0;
	initgraph(Width, High);

	bool isRunning = true;          //����һ������ѭ���ı���
	bool flag = 0;
	while (isRunning)
	{
		if (flag)
			ai.Get_key_Setchess(mychs);	//Al�غ�
		s.show(mychs, user);		//չʾ��ͼ
		if (ai.gameOver(s, user))	//�ж��Ƿ�ʤ��
		{
			map = cop;              //���õ�ͼ
			mychs.steps = 0;        //���ò���
			continue;               //��������ѭ�������¿�ʼ
		}

		flag = 1;
		mychs.now = true;			//��Ļغ� set now = true
		s.Mouse(mychs, user);		//���ȷ��ѡ��,set now = false
		s.show(mychs, user);        //չʾ��ͼ
		if (mychs.gameOver(s, user))//�ж��Ƿ�ʤ��	
		{
			map = cop;              //���õ�ͼ
			mychs.steps = 0;        //���ò���
			continue;               //��������ѭ�������¿�ʼ
		}
	}
	return 0;

}

int main()
{
	a = b = c = d = e = f = 1;
	initgraph(Width, High);

	BeginBatchDraw();                                 //������ʾ��ʼһ���εĻ��ƣ����Խ����ͼ��һ���Ի��Ƴ�������߻���Ч�ʡ�
	setbkcolor(WHITE);                            //���ñ�����ɫΪ��ɫ
	cleardevice();                                    //�����Ļ���õ�ǰ����ɫ���������Ļ��
	setcolor(BLACK);                              //��������ǰ������ɫ����Ϊ��ɫ��

	rectangle(340, 100, 460, 140); // ���ƾ���
	outtextxy(370, 110, L"������ս"); // ����ı�

	rectangle(340, 200, 460, 240); // ���ƾ���
	outtextxy(370, 210, L"�˻���ս"); // ����ı�

	rectangle(340, 300, 460, 340); // ���ƾ���
	outtextxy(370, 310, L"�оִ���"); // ����ı�

	//rectangle(340, 400, 460, 440); // ���ƾ���
	//outtextxy(370, 410, L"��Ҷ�ս"); // ����ı�

	rectangle(340, 500, 460, 540); // ���ƾ���
	outtextxy(370, 510, L"����"); // ����ı�

	rectangle(340, 540, 460, 580); // ���ƾ���
	outtextxy(370, 550, L"����"); // ����ı�

	FlushBatchDraw();
	EndBatchDraw(); //������ʾ����һ���εĻ��ƣ�����������ͼ��һ���Ի��Ƴ�����
	MOUSEMSG m; // ���������Ϣ����
	while (true) // ѭ����������¼�
	{
		TCHAR str[250];																 // �����ַ����飬���ڴ洢Ҫ������ַ���
		m = GetMouseMsg();															 // ��ȡ�����Ϣ
		int x = m.x, y = m.y;														 // ��ȡ���λ��
		switch (m.uMsg)																 // ������Ϣ����������ͬ�Ĵ���
		{
		case WM_MOUSEMOVE:                                                           // ����ƶ��¼�
			if (x >= 340 && x <= 460 && y >= 200 && y <= 240)
			{
				setcolor(RED);                              //��������ǰ������ɫ����Ϊ��ɫ��
				rectangle(340, 200, 460, 240);              // ���ƾ���
				outtextxy(370, 210, L"�˻���ս");            // ����ı�// �����λ�ô���һ��ԲȦ����ʾ������
			}
			/*if (x >= 340 && x <= 460 && y >= 400 && y <= 440)
			{
				setcolor(RED);                              //��������ǰ������ɫ����Ϊ��ɫ��
				rectangle(340, 200, 460, 240);              // ���ƾ���
				outtextxy(370, 210, L"��Ҷ�ս");            // ����ı�// �����λ�ô���һ��ԲȦ����ʾ������
			}*/
			if (x >= 340 && x <= 460 && y >= 500 && y <= 540)
			{
				setcolor(RED);                              //��������ǰ������ɫ����Ϊ��ɫ��
				rectangle(340, 500, 460, 540);              // ���ƾ���
				outtextxy(370, 510, L"����");            // ����ı�// �����λ�ô���һ��ԲȦ����ʾ������
			}
			if (x >= 340 && x <= 460 && y >= 540 && y <= 580)
			{
				setcolor(RED);                              //��������ǰ������ɫ����Ϊ��ɫ��
				rectangle(340, 540, 460, 580);              // ���ƾ���
				outtextxy(370, 550, L"����");            // ����ı�// �����λ�ô���һ��ԲȦ����ʾ������
			}
			if (x >= 340 && x <= 460 && y >= 300 && y <= 340)
			{
				setcolor(RED);                              //��������ǰ������ɫ����Ϊ��ɫ��
				rectangle(340, 300, 460, 340);              // ���ƾ���
				outtextxy(370, 310, L"�оִ���");            // ����ı�// �����λ�ô���һ��ԲȦ����ʾ������
			}
			if (x >= 340 && x <= 460 && y >= 100 && y <= 140)
			{
				setcolor(RED);                              //��������ǰ������ɫ����Ϊ��ɫ��
				rectangle(340, 100, 460, 140);              // ���ƾ���
				outtextxy(370, 110, L"������ս");            // ����ı�// �����λ�ô���һ��ԲȦ����ʾ������
			}
			else
			{
				setcolor(BLACK);                             //��������ǰ������ɫ����Ϊ��ɫ��
				if (a)
				{
					rectangle(340, 100, 460, 140); // ���ƾ���
					outtextxy(370, 110, L"������ս"); // ����ı�
				}
				if (b)
				{
					rectangle(340, 200, 460, 240); // ���ƾ���
					outtextxy(370, 210, L"�˻���ս"); // ����ı�
				}
				if (c)
				{
					rectangle(340, 300, 460, 340); // ���ƾ���
					outtextxy(370, 310, L"�оִ���"); // ����ı�
				}
				/*if (d)
				{
					rectangle(340, 400, 460, 440); // ���ƾ���
					outtextxy(370, 410, L"��Ҷ�ս"); // ����ı�
				}*/
				if (e)
				{
					rectangle(340, 500, 460, 540); // ���ƾ���
					outtextxy(370, 510, L"����"); // ����ı�
				}
				if (f)
				{
					rectangle(340, 540, 460, 580); // ���ƾ���
					outtextxy(370, 550, L"����"); // ����ı���
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


