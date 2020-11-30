#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;
#include "Identity.h"
#include "computerRoom.h"
#include "globalFile.h"
#include "orderFile.h"
#include "function.h"

// 学生类设计
class Student : public Identity
{
public:

	// 默认构造
	Student();

	// 有参构造（参数：姓名、学号、密码）
	Student(int id, string name, string password);

	// 菜单界面
	virtual void openMenu();

	// 申请预约
	void applyOrder();

	// 查看自身预约
	void showMyOrder();

	// 查看所有预约
	void showAllOrder();

	// 取消预约
	void cancelOrder();

	// 获取机房信息
	void getCom();

	// 保存预约信息
	void save(int date, int interval, int stuId, string stuName, int roomId, string status);

public:
	// 学生学号
	int m_id;

	// 机房容器
	vector<ComputerRoom>vCom;
};
