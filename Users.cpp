#include "include.h"

void Users::Read(void)
{
	ifstream in("users.dat", ios::binary | ios::in); // �򿪶������ļ� users.dat��������ģʽ��

	if (!in.is_open()) // ����ļ���ʧ�ܣ����˳�����
		return;

	// ��ȡ�ļ��е����ݵ����Ա������
	in.read((char*)&wincnt, sizeof(int));
	in.read((char*)&failcnt, sizeof(int));
	in.read((char*)&drawcnt, sizeof(int));
	in.read((char*)&minsteps, sizeof(int));
	in.read((char*)&restcnt, sizeof(int));

	in.close(); // �ر��ļ���
}

void Users::Write(void)
{
	ofstream out("users.dat", ios::binary); // �򿪶������ļ� users.dat�������ģʽ��

	if (!out.is_open()) // ����ļ���ʧ�ܣ����˳�����
		exit(0);

	// �����Ա����д���ļ�
	out.write((char*)&wincnt, sizeof(int));
	out.write((char*)&failcnt, sizeof(int));
	out.write((char*)&drawcnt, sizeof(int));
	out.write((char*)&minsteps, sizeof(int));
	out.write((char*)&restcnt, sizeof(int));

	out.Close(); // �ر��ļ���
}

