#include "include.h"





void Users::Read(void)
{
    ifstream in("users.txt", ios::in);               // ���ı��ļ� users.txt��������ģʽ��

    if (!in.is_open())                                           // ����ļ���ʧ�ܣ����˳�����
        return;

    in >> wincnt >> failcnt >> drawcnt >> minsteps >> restcnt;   // ��ȡ�ļ��е����ݵ����Ա������

    in.close();                                                  // �ر��ļ���
}





void Users::Write(void)
{
    ofstream out("users.txt");                           // ���ı��ļ� users.txt�������ģʽ��

    if (!out.is_open())                                         // ����ļ���ʧ�ܣ����˳�����
        exit(0);

    out << wincnt << " " << failcnt << " " << drawcnt << " " << minsteps << " " << restcnt;	// �����Ա����д���ļ�

    out.close(); // �ر��ļ���
}
