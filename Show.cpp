#include "include.h"

extern int aiset;                                     //��¼������һ���µ�λ��
extern stack<pair<int, int>> stk;                     //���Կ��ƻ���-��ɾ��
extern vector<vector<int>> map;                       //map�����̣�-1�գ�0���ԣ�1�ѷ�
extern double myPos, aiPos;                           //�ҷ��͵�����ֵ÷�
static const char dir1[] = { "ABCDEFGHIJKLMNOPQR" };  //
static const char dir2[] = { "123456789ABCDEFGHI" };  //


void Show::show(MyChess& mychs, Users& user)
{
	BeginBatchDraw(); // ��ʼһ���εĻ��ƣ���߻���Ч��
	setbkcolor(WHITE); // ���ñ�����ɫΪ��ɫ
	cleardevice(); // �����Ļ���õ�ǰ����ɫ���������Ļ
	setcolor(BLACK); // ���û�����ɫΪ��ɫ
	TCHAR row, col; // �����ַ����ͱ���

	// �������߲���ʾ����
	for (int i = 20; i <= 530; i += 30) {
		line(20, i, 530, i); // ������
		line(i, 20, i, 530); // ������
		row = dir1[reswitch_xy(i)]; // ��ȡ�������Ӧ���ַ�
		col = dir2[reswitch_xy(i)]; // ��ȡ�������Ӧ���ַ�
		outtextxy(5, i - 7, row); // ��ʾ�������ַ�
		outtextxy(i - 5, 545, col); // ��ʾ�������ַ�
	}

	// ����4��С�ڵ�
	setfillcolor(BLACK);
	fillcircle(170, 170, 3);
	fillcircle(170, 380, 3);
	fillcircle(380, 170, 3);
	fillcircle(380, 380, 3);

	// ���������ϵ�����
	for (int i = 0; i < 18; i++) {
		for (int j = 0; j < 18; j++) {
			if (map[i][j] != -1) {
				setChess(switch_xy(i), switch_xy(j), map[i][j]);
			}
		}
	}

	TCHAR str[250];
	wchar_t* wstr = new wchar_t[100];
	//double nowTime = clock(), sec = 20 - ((nowTime - startTime) / CLOCKS_PER_SEC);
	mychs.get_grade(user, wstr);
	setcolor(BLACK);

	// ��ʾ�û���Ϣ
	outtextxy(600, 5, _T("�û���challger"));
	_stprintf_s(str, _T("ʤ����%d"), user.wincnt);
	outtextxy(600, 25, str);
	_stprintf_s(str, _T("������%d"), user.failcnt);
	outtextxy(600, 45, str);
	_stprintf_s(str, _T("ƽ�֣�%d"), user.drawcnt);
	outtextxy(600, 65, str);
	_stprintf_s(str, _T("ʤ�ʣ�%.2f%%"), user.failcnt ? (double)user.wincnt / (double)(user.wincnt + user.failcnt) * 100 : 0);
	outtextxy(600, 85, str);
	_stprintf_s(str, _T("��λ��%s"), wstr);
	outtextxy(600, 105, str);
	_stprintf_s(str, _T("ʤ����̲���: %d"), user.minsteps);
	outtextxy(600, 125, str);
	_stprintf_s(str, _T("ʣ����岽��: %d"), user.restcnt);
	outtextxy(600, 145, str);

	setcolor(BLUE); // ������
	line(580, 2, 580, 170);
	line(580, 170, 735, 170);
	line(735, 170, 735, 2);
	line(580, 2, 735, 2);
	setcolor(BLACK);

	// ��ʾ��ǰ����
	_stprintf_s(str, _T("����ǰ���� %d ��"), mychs.steps);
	outtextxy(600, 195, str);

	outtextxy(600, 225, _T("��ǰ������У�")); // ��ʾ��ǰ����������Ϣ

	// ���ơ����塱��ť
	setcolor(RED);
	rectangle(620, 265, 680, 305);
	outtextxy(634, 276, _T("����"));
	setcolor(BLACK);

	_stprintf_s(str, _T("���Ըղ�����λ�ã�%c�� %c��"), dir1[aiset & 0x1f], dir2[aiset >> 5]);
	outtextxy(570, 330, str); // ��ʾ���Ըղ����µ�λ��

	_stprintf_s(str, _T("������ֵ÷�: %.1f"), myPos);
	outtextxy(570, 370, str); // ��ʾ��ǰ��ֵ÷�
	_stprintf_s(str, _T("�Է���ֵ÷�: %.1f"), aiPos);
	outtextxy(570, 410, str);

	_stprintf_s(str, _T("��Ŀǰ��ʤ��Ϊ��%.2f%%"), 100 * myPos / (myPos + aiPos));
	outtextxy(570, 450, str); // ��ʾʤ��

	mychs.get_assuse(wstr);
	_stprintf_s(str, _T("��ǰ�������������%s"), wstr);
	outtextxy(570, 490, str); // ��ʾ��ǰ����������Ϣ

	if (mychs.now == true) {
		outtextxy(180, 595, _T("���������Ļغϣ�������...")); // ��ʾ��ǰ�غ���Ϣ
	}
	else {
		outtextxy(160, 595, _T("�����ǶԷ��Ļغϣ������ȴ�..."));
	}

	setcolor(RED);
	rectangle(440, 580, 520, 620); // ���ơ����¿�ʼ����ť
	outtextxy(444, 591, _T("���¿�ʼ"));
	setcolor(BLACK);
	setcolor(RED);
	rectangle(520, 580, 600, 620); // ���ơ��˳���Ϸ����ť
	outtextxy(524, 591, _T("�˳���Ϸ"));
	setcolor(BLACK);

	FlushBatchDraw(); // ˢ�»�ͼ������
	EndBatchDraw(); // ����һ���εĻ���
	return;
}


void Show::setChess(int x, int y, int choice)//0Ϊ�������壬1Ϊ�Լ�����
{
	setfillcolor(RED);                   // ���������ɫΪ��ɫ�����ڻ��岿�֣�
	if (!choice)                          // ���choiceΪ0����ʾ�������壩
		setfillcolor(BLACK);              // �������ɫ����Ϊ��ɫ
	fillcircle(x, y, 14);                 // ��ָ��λ��(x, y)������һ���뾶Ϊ14�����Բ��
	return;
}


void Show::Mouse(MyChess& mychs, Users& user)
{
	MOUSEMSG m; // ���������Ϣ����
	while (true) // ѭ����������¼�
	{
		TCHAR str[250];																 // �����ַ����飬���ڴ洢Ҫ������ַ���
		m = GetMouseMsg();															 // ��ȡ�����Ϣ
		int x = m.x, y = m.y;														 // ��ȡ���λ��
		switch (m.uMsg)																 // ������Ϣ����������ͬ�Ĵ���
		{
		case WM_MOUSEMOVE:                                                           // ����ƶ��¼�
			show(mychs, user);                                                   // ��ʾ��Ϸ����
			if (mychs.Get_xy(x, y) && map[reswitch_xy(x)][reswitch_xy(y)] == -1) // �������������ڲ��ҵ�ǰλ��δ����
			{
				int x1 = reswitch_xy(x), y1 = reswitch_xy(y);                        // ת������������
				_stprintf_s(str, _T("%c�� %c��"), dir1[y1], dir2[x1]);        // ��ʽ��Ҫ������ַ���
				outtextxy(705, 225, str);                                         // ����ַ���
				circle(x, y, 14);                                                // �����λ�ô���һ��ԲȦ����ʾ��������
			}
			else if (m.x > 620 && m.x < 680 && m.y > 265 && m.y < 305)               // �������ڻ��尴ť��Χ��
			{
				setcolor(BLUE);                                                  // �ı仭����ɫΪ��ɫ
				rectangle(620, 265, 680, 305);                         // ��һ����ɫ�ľ��ο�
				outtextxy(634, 276, _T("����"));                                // ��������塱�ַ���
				setcolor(BLACK);                                                 // �ı仭����ɫΪ��ɫ
			}
			else if (m.x > 440 && m.x < 520 && m.y > 580 && m.y < 620) // ���������˳���Ϸ��ť��Χ��
			{
				setcolor(BLUE);                                                  // �ı仭����ɫΪ��ɫ
				rectangle(440, 580, 520, 620);
				outtextxy(444, 591, _T("���¿�ʼ"));
				setcolor(BLACK);                                                 // �ı仭����ɫΪ��ɫ
			}
			else if (m.x > 520 && m.x < 600 && m.y > 580 && m.y < 620) // ���������˳���Ϸ��ť��Χ��
			{
				setcolor(BLUE);                                                  // �ı仭����ɫΪ��ɫ
				rectangle(520, 580, 600, 620);
				outtextxy(524, 591, _T("�˳���Ϸ"));                                // ��������塱�ַ���
				setcolor(BLACK);                                                 // �ı仭����ɫΪ��ɫ
			}
			break;

		case WM_LBUTTONUP:
			/*����*/
			if (mychs.Get_xy(x, y) && map[reswitch_xy(x)][reswitch_xy(y)] == -1)
			{
				int x1 = reswitch_xy(x), y1 = reswitch_xy(y);    
				stk.push({ aiset, (x1 << 5) | y1 });                        //����������͵�ǰAI������ѹ��ջ�У����ڻ����������
				map[x1][y1] = 1;                                                     //��������ϸ�λ��Ϊ�����塣
				mychs.now = false;													//��������״̬��AI->��ң���												
				mychs.steps++;														//�������ֲ�����
				myPos = mychs.GetNowPoints(1);									//��ȡ��ǰ��Һ�AI������λ����Ϣ��
				aiPos = mychs.GetNowPoints(0);
				mciSendString(_T("close chs"), NULL, 0, NULL); //����������Ч��
				mciSendString(_T("open setChs.wav alias chs"), NULL, 0, NULL);
				mciSendString(_T("play chs"), NULL, 0, NULL);
				return;
			}
			/*����*/
			else if (m.x > 620 && m.x < 680 && m.y > 265 && m.y < 305)
			{
				if (!user.restcnt) // ���û�л��������
				{
					MessageBox(0, _T("��û�л�������ˣ�����Ӯ���Ի�ø������ɣ�"), _T("NO"), 0); // ��ʾ��ʾ��Ϣ
					continue; // ����ѭ���ȴ�����¼�
				}
				if (stk.empty()) // �����ǰû�п��Ի���Ĳ���
				{
					MessageBox(0, _T("�����޷����壡"), _T("NO"), 0); // ��ʾ��ʾ��Ϣ
					continue; // ����ѭ���ȴ�����¼�
				}
				auto it = stk.top(); // ȡ��ջ��Ԫ�أ�������ʱ�����AI���Լ���λ����Ϣ
				stk.pop(); // ����ջ��Ԫ��
				int ai = it.first, self = it.second; // �ֱ�ȡ��AI���Լ���λ����Ϣ
				map[self >> 5][self & 0x1f] = -1; // ���Լ���λ����Ϣ�ӵ�ͼ�����
				map[aiset >> 5][aiset & 0x1f] = -1; // ��AI��λ����Ϣ�ӵ�ͼ�����
				aiset = ai; // �������AIλ����Ϣ�������õ�aiset�У��Ա���һ��AI����

				myPos = mychs.GetNowPoints(1); // �����Լ���AI�����ӷֲ����
				aiPos = mychs.GetNowPoints(0);
				user.restcnt--; // ��ʣ����������1
				user.Write(); // ��ʣ��������д���ļ�
				show(mychs, user); // ���»������̺������Ϣ
				return Mouse(mychs, user); // �����ȴ�����¼�
			}
			else if (m.x > 440 && m.x < 520 && m.y > 580 && m.y < 620) // ���������˳���Ϸ��ť��Χ��
			{
				setcolor(BLACK); // �ı仭����ɫΪ��ɫ
			    Show::End(2, user, mychs.steps); // ��ʾ��Ϸ������Ϣ
				setbkcolor(GREEN);
				cleardevice();
				exit(1); // �˳���Ϸ
			}
			else if (m.x > 520 && m.x < 600 && m.y > 580 && m.y < 620) // ���������˳���Ϸ��ť��Χ��
			{
				Show::End(2, user, mychs.steps);
				vector<vector<int>> cop(18, vector<int>(18, -1));
				map = cop;
				exit(1); // �˳���Ϸ
			}
		}
	}
	return;
}

void Show::End(int who, Users& user, int steps)
{
	if (!who) 
		return; 
	LOGFONT f;                              //�����������ԵĽṹ��
	gettextstyle(&f);						// ��ȡ��ǰ��������
	f.lfHeight = 20;						// ��������߶�Ϊ 48
	wcscpy_s(f.lfFaceName, _T("����"));		// ��������Ϊ�����塱(�߰汾 VC �Ƽ�ʹ�� _tcscpy_s ����)
	f.lfQuality = ANTIALIASED_QUALITY;		// �������Ч��Ϊ�����  
	settextstyle(&f);						// ����������ʽ
	outtextxy(615, 500, _T("��Ϸ����"));

	/*��δ�����һ��������䣬���ݱ��� `who` ��ֵ��������ͬ����ʾ�򣬱�ʾ��Ϸ��ʤ����ʧ�ܣ�������ʤ����ʧ����ִ����Ӧ�Ĳ�����������˵��

- ��� `who` ��ֵΪ 1����ʾ��һ�ʤ������һ����Ϣ����ʾ���ʤ����������Ļ���������ϲ��ʤ��������������ͬʱ�����û�ʤ��������ʣ���������������š�win.wav����������
- ��� `who` ��ֵ��Ϊ 1����ʾ���ʧ�ܣ�����һ����Ϣ����ʾ���ʧ�ܣ�������Ļ���������ʧ���ˣ���Ҫ�����´������ɣ�����������ͬʱ�����û�ʧ�ܴ����������š�defet.mp3����������
- ����������¶������Ļ�ϵ����ݣ�������һ�ʤʱ��ʾ����ϲ��ʤ�������������ʧ��ʱ��ʾ����ʧ���ˣ���Ҫ�����´������ɣ�����
- �����ʧ��ʱ����������Ļ��������밴�����������Ϸ...������ʾ��ҿ��԰������������Ϸ��*
- ����������¶������� `mciSendString` ������������Ӧ�������ļ���
*/

	if (who == 1) 
	{
		MessageBox(0, _T("��ϲ��ʤ����"), _T("YES"), 0);
		setbkcolor(GREEN);
		cleardevice();
		outtextxy(250, 200, _T("��ϲ��ʤ����"));	
		//outtextxy(250, 300, _T("�밴�����������Ϸ..."));
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
		MessageBox(0, _T("��ʧ���ˣ���Ҫ�����´������ɣ���"), _T("NO"), 0);
		setbkcolor(GREEN);
		cleardevice();
		outtextxy(250, 200, _T("��ʧ���ˣ���Ҫ�����´������ɣ�"));
		outtextxy(250, 300, _T("�밴�����������Ϸ..."));
		mciSendString(_T("close det"), NULL, 0, NULL);
		mciSendString(_T("open defet.mp3 alias det"), NULL, 0, NULL);
		mciSendString(_T("play det"), NULL, 0, NULL);
		user.failcnt++;
	}

	user.Write();
	int ch = _gettch();          //�����������������ַ���ASCII�����ɨ���롣

	while (!stk.empty())		 //����
		stk.pop();
	aiPos = 0;
	myPos = 0;
	closegraph();
	return;
}

