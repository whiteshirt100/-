#pragma once

#include <iostream>
#include <string>
#include <vector>
using namespace std;
#include "Identity.h"
#include "globalFile.h"
#include "orderFile.h"
#include "function.h"

// 教师类设计
class Teacher : public Identity
{
public:
	
	// 默认构造
	Teacher();

	// 有参构造（职工编号、姓名、密码）
	Teacher(int empId, string name, string password);

	// 菜单界面
	virtual void openMenu();

	// 查看所有预约
	void showAllOrder();

	// 审核预约
	void validOrder();

public:
	// 教师编号
	int m_empId;



};
