#include "include.h"

#define _CRT_SECURE_NO_WARNINGS     //����һ��Ԥ����ָ������� Visual Studio �н��þ��档���������Ƶ�ʹ��ĳЩ�������� scanf() �� strncpy()��ʱ���������ɵľ��档

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
	// ��ȡת������ַ�������
	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), NULL, 0);
	/*���д���ʹ���� MultiByteToWideChar ����������һ�� Windows API ���������ڽ����ֽ��ַ�����MBCS���ַ���ת��Ϊ���ַ�����Unicode���ַ�����
	 *����������У������ĵ�һ������ CP_ACP ��ʾʹ��ϵͳĬ�ϵ� Windows ANSI ����ҳ��ִ��ת����
	 *�ڶ�������Ϊ��־����������Ϊ 0��
	 *�������͵��ĸ������ֱ�ָ��Ҫת���Ķ��ֽ��ַ������䳤�ȡ�
	 *���������Ϊ����ת����Ŀ��ַ����ַ����Ļ���������������Ϊ NULL����ʾ������ת������ַ�����
	 *���һ������ָ���������Ĵ�С����������Ϊ 0��
		�� MultiByteToWideChar �����ĵ������������Ϊ NULL �ҵ�������������Ϊ 0 ʱ�������������軺�����Ĵ�С���Կ��ַ�Ϊ��λ��������ִ��ʵ�ʵ�ת��������������У���������ֵ���洢����Ϊ len �� int �����У���ʾת����Ŀ��ַ����ַ�������Ļ�������С��*/
	// ����һ�� std::wstring ����
	std::wstring wstr(len, L'\0');
	// ���� MultiByteToWideChar ���������ת��
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), &wstr[0], len);
	/*���д����ٴε����� `MultiByteToWideChar` ���������ڽ����ֽ��ַ�����MBCS���ַ���ת��Ϊ���ַ�����Unicode���ַ�����
	 *����һ�ε�����ȣ���ε��õĵ��������Ϊ `&wstr[0]`����ʾ����ת����Ŀ��ַ����ַ����Ļ�������
	 *����������Ϊ `len`����ʾ�������Ĵ�С��
		����������У����������ֽ��ַ��� `str` ת��Ϊ���ַ����ַ���������ת������ַ����洢�� `wstr` �������С�
		�������Ĵ�С��֮ǰ���� `MultiByteToWideChar` ����ʱ���ص�ֵȷ����*/
	// ����ת������ַ���
	return wstr;
}





void playorder(void)//�����Ⱥ���
{
	//�����Ⱥ���ͼ��
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
	//�����Ⱥ���ͼ��

	MOUSEMSG m;                                                                     // ���������Ϣ����
	while (true)                                                                    // ѭ����������¼�
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





void selectLevelWindow()  //�о���սѡ��ؿ�
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
		int a, b, c, d, e, f;
		a = b = c = d = e = f = 1;

		switch (m.uMsg) // ������Ϣ����������ͬ�Ĵ���
		{
		case WM_MOUSEMOVE: // ����ƶ��¼�
			if (x >= 340 && x <= 460 && y >= 200 && y <= 240)
			{
				setcolor(RED);
				rectangle(340, 200, 460, 240);
				outtextxy(370, 210, L"�ڶ���");
				b = 0;
				a = c = d = e = f = 1;
			}
			if (x >= 340 && x <= 460 && y >= 300 && y <= 340)
			{
				setcolor(RED);
				rectangle(340, 300, 460, 340);
				outtextxy(370, 310, L"������");
				c = 0;
				a = b = d = e = f = 1;
			}
			if (x >= 340 && x <= 460 && y >= 400 && y <= 440)
			{
				setcolor(RED);
				rectangle(340, 400, 460, 440);
				outtextxy(370, 410, L"���Ĺ�");
				d = 0;
				a = b = c = e = f = 1;
			}
			if (x >= 340 && x <= 460 && y >= 500 && y <= 540)
			{
				setcolor(RED);
				rectangle(340, 500, 460, 540);
				outtextxy(370, 510, L"�����");
				e = 0;
				a = b = c = d = f = 1;
			}
			if (x >= 340 && x <= 460 && y >= 600 && y <= 640)
			{
				setcolor(RED);
				rectangle(340, 600, 460, 640);
				outtextxy(370, 610, L"������");
				f = 0;
				a = b = c = d = e = 1;
			}
			if (x >= 340 && x <= 460 && y >= 100 && y <= 140)
			{
				setcolor(RED);
				rectangle(340, 100, 460, 140);
				outtextxy(370, 110, L"��һ��");
				a = 0;
				b = c = d = e = f = 1;
			}
			
			{
				setcolor(BLACK);
				if (a)
				{
					rectangle(340, 100, 460, 140);
					outtextxy(370, 110, L"��һ��");
				}
				if (b)
				{
					rectangle(340, 200, 460, 240);
					outtextxy(370, 210, L"�ڶ���");
				}
				if (c)
				{
					rectangle(340, 300, 460, 340);
					outtextxy(370, 310, L"������");
				}
				if (d)
				{
					rectangle(340, 400, 460, 440);
					outtextxy(370, 410, L"���Ĺ�");
				}
				if (e)
				{
					rectangle(340, 500, 460, 540);
					outtextxy(370, 510, L"�����");
				}
				if (f)
				{
					rectangle(340, 600, 460, 640);
					outtextxy(370, 610, L"������");
				}
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



//��ʱ��

// ����ԭ�ӱ��� isRunning�����ڿ����߳��Ƿ�����
std::atomic<bool> isRunning{ true };
// ����ԭ�ӱ��� global_duration�����ڴ洢ȫ��ʱ��
std::atomic<int> global_duration{ 0 };
// ����ԭ�ӱ��� last_turn_duration�����ڴ洢��һ��ʱ��
std::atomic<int> last_turn_duration{ 0 };
// ���� last_turn_start ���������ڴ洢��һ�ֿ�ʼʱ��
std::chrono::time_point<std::chrono::steady_clock> last_turn_start;

// ��ʱ���̺߳���
void timer_thread()
{
	// ��ȡ��ǰʱ����Ϊ��ʼʱ��
	auto start = std::chrono::steady_clock::now();
	// ������һ�ֿ�ʼʱ��Ϊ��ʼʱ��
	last_turn_start = start;
	// ѭ��ֱ�� isRunning ��Ϊ false
	while (isRunning) 
	{
		// ��ȡ��ǰʱ��
		auto now = std::chrono::steady_clock::now();
		// ����ȫ��ʱ��
		global_duration = std::chrono::duration_cast<std::chrono::seconds>(now - start).count();
		// ������һ��ʱ��
		last_turn_duration = std::chrono::duration_cast<std::chrono::seconds>(now - last_turn_start).count();


		// ����ȫ��ʱ���ַ�������ʾ����Ļ��
		std::wstring global_timer_text = L"ȫ��ʱ�䣺 " + std::to_wstring(global_duration) + L"s";
		outtextxy(590, 540, global_timer_text.c_str());
		// ������һ��ʱ���ַ�������ʾ����Ļ��
		std::wstring turn_timer_text = L"�ִ�ʱ�䣺 " + std::to_wstring(last_turn_duration) + L"s";
		outtextxy(590, 570, turn_timer_text.c_str());


		// ���� 1 ����
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}
//��ʱ��






int computer_and_player(void) {
	// ���� MyChess �����
	MyChess mychs;
	// ���� Show �����
	Show s;
	// ���� AiChess �����
	AiChess ai;
	// ���� Users �����
	Users user;
	// ���廥����
	std::mutex mt;
	// ��ȡ�û���Ϣ
	user.Read();
	// ���õ�ͼ
	map = cop;
	// ��ʼ������
	mychs.steps = 0;
	// ��ʼ��ͼ�ν���
	initgraph(Width, High);
	// �����ִ�ʱ����ʾ�ַ���
	char turntimeshow[20] = "0:0";


	// ������ʱ���߳�
	std::thread timer(timer_thread);

	// ѭ��ֱ�� isRunning ��Ϊ false
	while (isRunning) 
	{
		// ��ȡ��ǰʱ����Ϊ��ʼʱ��
		first = time(NULL);
		// ����� AI ���壬����� AI �ķ�����������
		if (!firstorsecond)
			ai.Get_key_Setchess(mychs);
		// ��ʾ���̺�����
		s.show(mychs, user);

		BeginBatchDraw();
		outtextxy(570, 530, wchar_t((turntimeshow)));
		FlushBatchDraw();
		EndBatchDraw();

		// �ж���Ϸ�Ƿ������������������õ�ͼ�Ͳ�����������һ����Ϸ
		if (ai.gameOver(s, user)) 
		{
			map = cop;
			mychs.steps = 0;
			continue;
		}

		firstorsecond = 0;
		mychs.now = true;
		// ��ȡ�û����������������̺�������Ϣ
		s.Mouse(mychs, user);


		// ������һ�ֿ�ʼʱ��
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

	// ֹͣ��ʱ���̲߳��ȴ������
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
	MyChess mychs; // ���� MyChess �������ڹ������״̬
	Show s; // ���� Show ����������ʾ��ֽ���
	AiChess ai; // ���� AiChess ��������ʵ�� AI �㷨
	Users user; // ���� Users �������ڹ����û���Ϣ
	Readers readers; // ���� Readers �������ڶ�ȡ�ļ�
	std::mutex mt; // �������������������߳�ͬ��
	user.Read(); // ��ȡ�û���Ϣ
	int filenum = 1; // �ļ����
	selectLevelWindow(); // ѡ����Ϸ�ѶȵĴ���
	map = readers.read_map_from_file("level", map, filenum); // ���ļ��ж�ȡ��ͼ����
	mychs.steps = 0; // ��ʼ����ֲ���Ϊ 0
	initgraph(Width, High); // ��ʼ����ͼ����
	char turntimeshow[20] = "0:0"; // �洢��ʱ����ʾ���ַ���
	// ������ʱ���߳�
	std::thread timer(timer_thread);
	while (isRunning) { // ѭ��ִ����Ϸ���߼���ֱ����Ϸ����
		first = time(NULL); // ��¼��ǰʱ��
		if (!firstorsecond)
			ai.Get_key_Setchess(mychs); // AI ����
		s.show(mychs, user); // ��ʾ���
		BeginBatchDraw(); // ��ʼ��������
		outtextxy(570, 530, wchar_t((turntimeshow))); // ���Ƽ�ʱ���ı�
		FlushBatchDraw(); // ˢ�»�ͼ
		EndBatchDraw(); // ������������
		if (ai.gameOver(s, user)) { // ����Ƿ�ﵽ��Ϸ��������
			map = cop; // �ָ���ͼ״̬
			mychs.steps = 0; // ������ֲ���
			continue; // ������һ��ѭ��
		}
		firstorsecond = 0; // �л�Ϊ�û��غ�
		mychs.now = true; // ���õ�ǰ�ֵ��û�����
		s.Mouse(mychs, user); // �����û�������
		// �����ϴλغϵĿ�ʼʱ��
		last_turn_start = std::chrono::steady_clock::now();
		second = time(NULL); // ��¼��ǰʱ��
		s.show(mychs, user); // ��ʾ���
		BeginBatchDraw(); // ��ʼ��������
		double time_diff = difftime(second, first); // ��������ʱ���
		int minutes = static_cast<int>((int)time_diff / 60); // ���������
		int seconds = static_cast<int>((int)time_diff % 60); // ��������
		std::string turntimeshow = std::to_string(minutes) + "min: " + std::to_string(seconds) + "s"; // ������ʱ����ʾ�ַ���
		FlushBatchDraw(); // ˢ�»�ͼ
		EndBatchDraw(); // ������������
		if (mychs.gameOver(s, user)) { // ����Ƿ�ﵽ��Ϸ��������
			map = cop; // �ָ���ͼ״̬
			mychs.steps = 0; // ������ֲ���
			continue; // ������һ��ѭ��
		}
	}
	// ֹͣ��ʱ���߳�
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




//��ҳ����ƺ���
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
				setcolor(BLACK);
			}
			/*if (x >= 340 && x <= 460 && y >= 400 && y <= 440)
			{
				setcolor(RED);                              //��������ǰ������ɫ����Ϊ��ɫ��
				rectangle(340, 200, 460, 240);              // ���ƾ���
				outtextxy(370, 210, L"��Ҷ�ս");            // ����ı�// �����λ�ô���һ��ԲȦ����ʾ������
			}*/
			else if (x >= 340 && x <= 460 && y >= 500 && y <= 540)
			{
				setcolor(RED);                              //��������ǰ������ɫ����Ϊ��ɫ��
				rectangle(340, 500, 460, 540);              // ���ƾ���
				outtextxy(370, 510, L"����");            // ����ı�// �����λ�ô���һ��ԲȦ����ʾ������
				setcolor(BLACK);
			}
			else if (x >= 340 && x <= 460 && y >= 540 && y <= 580)
			{
				setcolor(RED);                              //��������ǰ������ɫ����Ϊ��ɫ��
				rectangle(340, 540, 460, 580);              // ���ƾ���
				outtextxy(370, 550, L"����");            // ����ı�// �����λ�ô���һ��ԲȦ����ʾ������
				setcolor(BLACK);
			}
			else if (x >= 340 && x <= 460 && y >= 300 && y <= 340)
			{
				setcolor(RED);                              //��������ǰ������ɫ����Ϊ��ɫ��
				rectangle(340, 300, 460, 340);              // ���ƾ���
				outtextxy(370, 310, L"�оִ���");            // ����ı�// �����λ�ô���һ��ԲȦ����ʾ������
				setcolor(BLACK);
			}
			else if (x >= 340 && x <= 460 && y >= 100 && y <= 140)
			{
				setcolor(RED);                              //��������ǰ������ɫ����Ϊ��ɫ��
				rectangle(340, 100, 460, 140);              // ���ƾ���
				outtextxy(370, 110, L"������ս");            // ����ı�// �����λ�ô���һ��ԲȦ����ʾ������
				setcolor(BLACK);
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

		case WM_LBUTTONUP: // ����������̧���¼�
			if (x >= 340 && x <= 460 && y >= 540 && y <= 580) {
				f = 0; // ���� f ����Ϊ 0
				firstorsecond = 0; // ���� firstorsecond ����Ϊ 0
			}
			else if (x >= 340 && x <= 460 && y >= 200 && y <= 240) {
				b = 0; // ���� b ����Ϊ 0
				int done = computer_and_player(); // ���� computer_and_player() ��������������ֵ���� done ����
				return 0; // ���� 0
			}
			else if (x >= 340 && x <= 460 && y >= 400 && y <= 440) {
				d = 0; // ���� d ����Ϊ 0
				int done = player_and_player(); // ���� player_and_player() ��������������ֵ���� done ����
				return 0; // ���� 0
			}
			else if (x >= 340 && x <= 460 && y >= 300 && y <= 340) {
				c = 0; // ���� c ����Ϊ 0
				int done = end_game(); // ���� end_game() ��������������ֵ���� done ����
				return 0; // ���� 0
			}
			else if (x >= 340 && x <= 460 && y >= 100 && y <= 140) {
				a = 0; // ���� a ����Ϊ 0
				int done = online_player(); // ���� online_player() ��������������ֵ���� done ����
				return 0; // ���� 0
			}
			else if (x >= 340 && x <= 460 && y >= 500 && y <= 540) {
				e = 0; // ���� e ����Ϊ 0
			}
			break;
		}
	}
}


