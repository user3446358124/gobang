#include "include.h"

void Users::Read(void)
{
	ifstream in("users.dat", ios::binary | ios::in); // 打开二进制文件 users.dat，以输入模式打开

	if (!in.is_open()) // 如果文件打开失败，则退出函数
		return;

	// 读取文件中的数据到类成员变量中
	in.read((char*)&wincnt, sizeof(int));
	in.read((char*)&failcnt, sizeof(int));
	in.read((char*)&drawcnt, sizeof(int));
	in.read((char*)&minsteps, sizeof(int));
	in.read((char*)&restcnt, sizeof(int));

	in.close(); // 关闭文件流
}

void Users::Write(void)
{
	ofstream out("users.dat", ios::binary); // 打开二进制文件 users.dat，以输出模式打开

	if (!out.is_open()) // 如果文件打开失败，则退出程序
		exit(0);

	// 将类成员变量写入文件
	out.write((char*)&wincnt, sizeof(int));
	out.write((char*)&failcnt, sizeof(int));
	out.write((char*)&drawcnt, sizeof(int));
	out.write((char*)&minsteps, sizeof(int));
	out.write((char*)&restcnt, sizeof(int));

	out.Close(); // 关闭文件流
}

