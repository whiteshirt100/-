#pragma once

#include <iostream>
using namespace std;
#include <vector>
#include <map>
#include <deque>
#include <algorithm>
#include <functional>
#include <numeric>
#include <string>
#include <fstream>
#include "speaker.h"
#include "function.h"

#define FILENAME "speech.csv"

// 演讲管理类
class SpeechManager
{
public:
	// 构造函数
	SpeechManager();
	
	// 展示菜单
	void showMenu();

	// 退出
	void exitSystem();

	// 初始化成员属性
	void initSpeech();

	// 创建12名选手
	void createSpeaker();

	// 开始比赛 比赛整个流程控制函数
	void startSpeech();

	// 抽签
	void speechDraw();

	// 开始比赛
	void speechContest();

	// 显示比赛结果
	void showScore();

	// 保存记录
	void saveRecord();

	// 读取记录
	void loadRecord();

	// 显示往届得分
	void showRecord();

	// 重置
	void reset();

	// 清空记录
	void clearRecord();

	// 析构函数
	~SpeechManager();

public:
	//成员属性
	// 保存第一轮比赛选手编号容器
	vector<int>v1;

	// 第一轮晋级选手编号容器
	vector<int>v2;

	// 胜出前三名选手编号容器
	vector<int>vVictory;

	// 存放编号以及对应具体选手容器
	map<int, Speaker>m_speaker;

	// 比赛轮数
	int m_index;

	// 判断文件是否为空
	bool fileIsEmpty;

	// 往届记录
	map<int, vector<string>>m_record;
};
