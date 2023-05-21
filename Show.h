
#pragma once

#ifndef SHOW_H
#define SHOW_H

#include "Class.h"
#include "Users.h"
#include <graphics.h>
#include <time.h>
#include <string>
#include <stack>
#include <vector>

class Show
{
public:
	void show(MyChess& mychs, Users& user);		//���ƺ���
	void setChess(int x, int y, int choice);	//���庯����choice���ó�0Ϊ�����£�1Ϊ�ҷ�
	void Mouse(MyChess& mychs, Users& user);	//������Ӧ���
	void End(int who, Users& user, int steps);	//��Ϸ��������ҳ��
};

#endif // 



