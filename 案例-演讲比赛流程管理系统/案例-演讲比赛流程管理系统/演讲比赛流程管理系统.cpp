
#include <iostream>
using namespace std;
#include "speechManager.h"
#include <string>
#include <ctime>
/*
1 比赛规则

* 12个人参加，比赛分两轮，淘汰赛、决赛
* 编号，如10001 ~ 10012
* 分组比赛，每组6人
* 第一轮分两组，按抽签顺序演讲
* 十个评委打分，去掉最高和最低，求平均
* 小组演讲完后，淘汰组内排名最后的三位选手，前三名晋级进入下一轮
* 第二轮为决赛，前三名胜出
* 每轮比赛过后显示晋级选手的信息


2 程序功能

* 开始演讲比赛：完成整届比赛的流程，每个比赛阶段需要给用户一个提示，用户按任意键后继续下一个阶段
* 查看往届记录：查看之前比赛的前三名结果，每次比赛都会记录到文件中，文件用.csv后缀名保存
* 清空比赛记录：将文件中数据清空
* 退出比赛程序：可以退出当前程序
*/

int main()
{
	// 随机数种子
	srand((unsigned int)time(NULL));
	
	// 创建管理类对象
	SpeechManager sm;

	// 测试代码
	/*for (map<int, Speaker>::iterator it = sm.m_speaker.begin(); it != sm.m_speaker.end(); it ++)
	{
		cout << "选手编号：" << it->first << " 姓名：" << it->second.m_name << " 成绩：" << it->second.m_score[0] << endl;
	}*/

	int choice = 0;

	while (true)
	{
		sm.showMenu();

		cout << "请输入您的选择：" << endl;

reEnter_main_choice:
		choice = 0;
		// 限制必须输入整数
		SpeechManager::isInt(cin, choice);

		while (choice >3 || choice <0)
		{
			cout << "请输入正确的数字" << endl;
			goto reEnter_main_choice;
		}

		switch (choice)
		{
		case 1:
			sm.startSpeech();
			break;
		case 2:
			sm.showRecord();
			break;
		case 3:
			sm.clearRecord();
			break;
		case 0:
			sm.exitSystem();
			break;
		default:
			system("cls");
			break;
		}
	}
	cout << "hello..." << endl;
	system("pause");
	return 0;
}