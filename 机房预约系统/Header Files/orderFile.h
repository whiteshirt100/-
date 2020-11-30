#pragma once

#include <iostream>
#include <map>
#include <string>
#include <fstream>
using namespace std;
#include "globalFile.h"

class OrderFile
{
public:

	// 构造函数
	OrderFile();

	// 更新预约记录
	void updateOrder();

	// 截取字符串函数
	void strSub(string str, map<string, string>&m);

public:

	// 记录预约条数
	int m_size;

	// 记录所有预约信息的容器  key记录条数  value具体记录键值对信息
	map<int, map<string, string>>m_orderData;


};

