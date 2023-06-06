#include "include.h"





void Users::Read(void)
{
    ifstream in("users.txt", ios::in);               // 打开文本文件 users.txt，以输入模式打开

    if (!in.is_open())                                           // 如果文件打开失败，则退出函数
        return;

    in >> wincnt >> failcnt >> drawcnt >> minsteps >> restcnt;   // 读取文件中的数据到类成员变量中

    in.close();                                                  // 关闭文件流
}





void Users::Write(void)
{
    ofstream out("users.txt");                           // 打开文本文件 users.txt，以输出模式打开

    if (!out.is_open())                                         // 如果文件打开失败，则退出程序
        exit(0);

    out << wincnt << " " << failcnt << " " << drawcnt << " " << minsteps << " " << restcnt;	// 将类成员变量写入文件

    out.close(); // 关闭文件流
}
