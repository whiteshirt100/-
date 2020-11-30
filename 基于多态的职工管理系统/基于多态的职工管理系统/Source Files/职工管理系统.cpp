
#include <iostream>
using namespace std;

#include "workerManager.h"
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
#include "function.h"

int main()
{
	WorkerManager wm;
	int choice;
	while (true)
	{
		// 展示菜单
		wm.showMenu();

		cout << "请输入您的选择:" << endl;
		choice = 0;
		// 限制输入为整数
		inputInt(cin, choice);

		switch (choice)
		{
		case 0:  // 退出系统
			wm.exitSystem();
			break;
		case 1:  // 添加职工
			wm.addEmp();
			break;
		case 2:  // 显示职工
			wm.showEmp();
			break;
		case 3:  // 删除职工
			wm.delEmp();
			break;
		case 4:  // 修改职工
			wm.modEmp();
			break;
		case 5:  // 查找职工
			wm.findEmp();
			break;
		case 6:  // 排序职工
			wm.sortEmp();
			break;
		case 7:  // 清空文件
			wm.cleanFile();
			break;
		default:
			cout << "请输入正确的数字" << endl;
			system("pause");
			system("cls");  // 清屏
			break;
		}
		
	}

	system("pause");
	return 0;
}