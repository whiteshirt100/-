
#include <iostream>
#include <string>
#include <fstream>
#include "globalFile.h"
#include "Identity.h"
#include "student.h"
#include "teacher.h"
#include "manager.h"

using namespace std;

// 进入学生子菜单界面
void studentMenu(Identity* &student)
{
	while (true)
	{
		// 调用学生子菜单
		student->openMenu();

		// 将父类指针 转为子类指针，调用子类里其他接口
		Student * stu = (Student*)student;

		int select = 0;
		// 接收用户选项
		// 限制必须输入整数
		inputInt(cin, select);

		switch (select)
		{
		case 1:		// 申请预约
			//cout << "申请预约" << endl;
			stu->applyOrder();
			break;
		case 2:		// 查看自身预约
			//cout << "查看自身预约" << endl;
			stu->showMyOrder();
			break;
		case 3:		// 查看所有预约
			//cout << "查看所有预约" << endl;
			stu->showAllOrder();
			break;
		case 4:		// 取消预约
			//cout << "取消预约" << endl;
			stu->cancelOrder();
			break;
		case 0:		// 注销登录
			delete student;  // 销毁堆区对象
			cout << "注销成功！" << endl;
			system("pause");
			system("cls");
			return;
		default:
			cout << "输入有误，请重新选择！" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}

// 进入教师子菜单界面
void teacherMenu(Identity* &teacher)
{
	while (true)
	{
		// 调用教师子菜单
		teacher->openMenu();

		// 将父类指针 转为子类指针，调用子类里其他接口
		Teacher * tea = (Teacher*)teacher;

		int select = 0;		// 接收用户选项
		
		// 限制必须输入整数
		inputInt(cin, select);

		switch (select)
		{
		case 1:		// 查看所有预约
			//cout << "查看所有预约" << endl;
			tea->showAllOrder();
			break;
		case 2:		// 审核预约
			//cout << "审核预约" << endl;
			tea->validOrder();
			break;
		case 0:		// 注销登录
			delete teacher;  // 销毁堆区对象
			cout << "注销成功！" << endl;
			system("pause");
			system("cls");
			return;
			break;
		default:
			cout << "输入有误，请重新选择！" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}

// 进入管理员子菜单界面
void managerMenu(Identity* &manager)
{
	while (true)
	{
		// 调用管理员子菜单
		manager->openMenu();

		// 将父类指针 转为子类指针，调用子类里其他接口
		Manager * man = (Manager*)manager;

		int select = 0;
		// 接收用户选项
		// 限制必须输入整数
		inputInt(cin, select);

		switch (select)
		{
		case 1:		// 添加账号
			//cout << "添加账号" << endl;
			man->addPerson();
			break;
		case 2:		// 查看账号
			//cout << "查看账号" << endl;
			man->showPerson();
			break;
		case 3:		// 查看机房
			//cout << "查看机房" << endl;
			man->showComputer();
			break;
		case 4:		// 清空预约
			//cout << "清空预约" << endl;
			man->cleanFile();
			break;
		case 0:		// 注销登录
			delete manager;  // 销毁堆区对象
			cout << "注销成功！" << endl;
			system("pause");
			system("cls");
			return;
			break;
		default:
			cout << "输入有误，请重新选择！" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}

// 登录功能（全局函数） 
// 参数1 操作文件名  参数2 操作身份类型
void loginIn(string fileName, int type)
{
	Identity* person = nullptr;  // 父类指针，用于指向子类对象

	// 读文件
	ifstream ifs;
	ifs.open(fileName, ios::in);

	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}

	// 准备接受用户的信息
	int id = 0;
	string name = "";
	string password = "";

	// 判断身份
	if (type == 1)  // 学生身份
	{
		cout << "请输入你的学号：" << endl;
		// 限制必须输入整数
		inputInt(cin, id);
	}
	else if (type == 2)  // 教师身份
	{
		cout << "请输入您的职工号：" << endl;
		// 限制必须输入整数
		inputInt(cin, id);
	}

	cout << "请输入用户名：" << endl;
	cin >> name;

	cout << "请输入密码：" << endl;
	cin >> password;

	if (type == 1)
	{
		// 学生身份验证
		int fId;		// 从文件中获取id号
		string fName;		// 从文件中获取的姓名
		string fPassword;	// 从文件中获取的密码

		while (ifs >> fId && ifs >> fName && ifs >> fPassword)
		{
			// 与用户输入的信息做对比
			if (fId == id && fName == name && fPassword == password)
			{
				cout << "学生验证登录成功！" << endl;
				// 登录成功后，按任意键进入学生界面
				system("pause");
				system("cls");
				person = new Student(id, name, password);
				// 进入学生身份子菜单
				studentMenu(person);
				return;
			}
		}
	}

	else if (type == 2)
	{
		// 老师身份验证
		int fId;			// 从文件中获取id号
		string fName;		// 从文件中获取的姓名
		string fPassword;	// 从文件中获取的密码

		while (ifs >> fId && ifs >> fName && ifs >> fPassword)
		{
			// 与用户输入的信息做对比
			if (fId == id && fName == name && fPassword == password)
			{
				cout << "老师验证登录成功！" << endl;
				// 登录成功后，按任意键进入老师界面
				system("pause");
				system("cls");
				person = new Teacher(id, name, password);
				// 进入老师身份子菜单
				teacherMenu(person);
				return;
			}
		}
	}
	else if (type == 3)
	{
		// 管理员身份验证
		string fName;		// 从文件中获取的姓名
		string fPassword;	// 从文件中获取的密码

		while (ifs >> fName && ifs >> fPassword)
		{
			// 与用户输入的信息做对比
			if (fName == name && fPassword == password)
			{
				cout << "管理员验证登录成功！" << endl;
				// 登录成功后，按任意键进入管理员界面
				system("pause");
				system("cls");
				person = new Manager(name, password);
				// 进入管理员身份子菜单
				managerMenu(person);
				return;
			}
		}
	}

	cout << "验证登陆失败！" << endl;
	system("pause");
	system("cls");

}

int main()
{
	int select = 0;			// 用于接收用户的选择
	while (true)
	{
		cout << "===================== 欢迎来到豪哥机房预约系统 =====================" << endl;
		cout << "请输入您的身份：" << endl;
		cout << "\t\t --------------------------------- " << endl;
		cout << "\t\t|                                 |" << endl;
		cout << "\t\t|          1、学生代表            |" << endl;
		cout << "\t\t|                                 |" << endl;
		cout << "\t\t|          2、老    师            |" << endl;
		cout << "\t\t|                                 |" << endl;
		cout << "\t\t|          3、管 理 员            |" << endl;
		cout << "\t\t|                                 |" << endl;
		cout << "\t\t|          0、退    出            |" << endl;
		cout << "\t\t|                                 |" << endl;
		cout << "\t\t --------------------------------- " << endl;
		cout << "请输入您的选择：" << endl;

		// 接收用户选择
		// 限制必须输入整数
		inputInt(cin, select);

		switch (select)		// 根据用户选择 实现不同的接口
		{
		case 1:		// 学生身份
			loginIn(STUDENT_FILE, select);
			break;
		case 2:		// 老师身份
			loginIn(TEACHER_FILE, select);
			break;
		case 3:		// 管理员身份
			loginIn(ADMIN_FILE, select);
			break;
		case 0:		// 退出系统
			cout << "欢迎下次使用！" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "输入有误，请重新选择！" << endl;
			system("pause");
			system("cls");
			break;
		}
	}

	system("pause");
	return 0;
}