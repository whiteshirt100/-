#pragma once

#include <iostream>
using namespace std;
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
#include "function.h"

#include <fstream>
#define FILENAME "empFile.txt"


class WorkerManager
{
public:
	// 构造函数
	WorkerManager();

	// 析构函数
	~WorkerManager();

	// 展示菜单
	void showMenu();

	// 退出系统
	void exitSystem();

	// 增加职工
	void addEmp();

	// 保存文件
	void save();

	// 获取职工人数
	int getNum();

	// 初始化职工
	void initEmp();

	// 重置
	void reset();

	// 显示职工
	void showEmp();

	// 删除职工
	void delEmp();

	// 根据职工编号判断职工是否存在，若存在返回职工在数组中的位置，不存在返回-1
	int isExist(int id);

	// 修改职工
	void modEmp();

	// 查找职工
	void findEmp();

	// 按照职工编号排序
	void sortEmp();

	// 清空文件
	void cleanFile();


public:
	// 记录文件中的人数个数
	int m_EmpNum;

	// 员工数组的指针
	Worker** m_EmpArray;

	// 标志文件是否为空
	bool m_FileEmpty;
};
