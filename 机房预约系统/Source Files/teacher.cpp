#include "teacher.h"

// 默认构造
Teacher::Teacher()
{
}

// 有参构造（职工编号、姓名、密码）
Teacher::Teacher(int empId, string name, string password)
{
	// 初始化属性
	this->m_empId = empId;
	this->m_name = name;
	this->m_password = password;
}

// 菜单界面
void Teacher::openMenu()
{
	cout << "欢迎教师：" << this->m_name << "登录！" << endl;
	cout << "\t\t --------------------------------- " << endl;
	cout << "\t\t|                                 |" << endl;
	cout << "\t\t|          1、查看所有预约        |" << endl;
	cout << "\t\t|                                 |" << endl;
	cout << "\t\t|          2、审核预约            |" << endl;
	cout << "\t\t|                                 |" << endl;
	cout << "\t\t|          0、注销登录            |" << endl;
	cout << "\t\t|                                 |" << endl;
	cout << "\t\t --------------------------------- " << endl;
	cout << "请选择您的操作：" << endl;
}

// 查看所有预约
void Teacher::showAllOrder()
{
	OrderFile of;
	if (of.m_size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < of.m_size; i++)
	{
		cout << i + 1 << "、";
		cout << "预约日期：周" << of.m_orderData[i]["date"];
		cout << "  时段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
		cout << "  学号：" << of.m_orderData[i]["stuId"];
		cout << "  姓名：" << of.m_orderData[i]["stuName"];
		cout << "  机房编号：" << of.m_orderData[i]["roomId"];
		string status = "  状态：";
		// 1 审核中   2 已预约   -1 预约失败   0 取消预约
		if (of.m_orderData[i]["status"] == "1")
		{
			status += "审核中";
		}
		else if (of.m_orderData[i]["status"] == "2")
		{
			status += "预约成功";
		}
		else if (of.m_orderData[i]["status"] == "-1")
		{
			status += "预约失败，审核未通过";
		}
		else
		{
			status += "预约已取消";
		}
		cout << status << endl;
	}
	system("pause");
	system("cls");
}

// 审核预约
void Teacher::validOrder()
{
	OrderFile of;
	if (of.m_size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}

	cout << "待审核的预约记录如下：" << endl;
	vector<int>v;  // 在文件中下标编号
	int index = 1;
	for (int i = 0; i < of.m_size; i++)
	{
		// 筛选状态 审核中
		if (of.m_orderData[i]["status"] == "1")
		{
			v.push_back(i);
			cout << index++ << "、";  // 给用户提供的下标用index提示，但实际容器中下标用容器 vector<int>v 存储
			cout << "预约日期：周" << of.m_orderData[i]["date"];
			cout << "  时段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
			cout << "  学号：" << of.m_orderData[i]["stuId"];
			cout << "  姓名：" << of.m_orderData[i]["stuName"];
			cout << "  机房：" << of.m_orderData[i]["roomId"];
			string status = "  状态：审核中";
			cout << status << endl;
		}
		
	}
	//cout << v.size() << endl;
	if (v.size() == 0)
	{
		cout << "待审核记录为空" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "请输入审核的预约记录，0代表返回" << endl;
	int select = 0;	// 接受用户选择的预约记录
	int ret = 0;	// 接受预约结果记录
	while (true)
	{
		// 限制必须输入整数
		inputInt(cin, select);
		// 
		if (select >= 0 && select <= v.size())
		{
			break;
		}
		cout << "输入有误，请重新输入！" << endl;
	}

	if (select != 0)
	{
		cout << "请输入审核结果：" << endl;
		cout << "1、通过" << endl;
		cout << "2、不通过" << endl;
		while (true)
		{
			// 限制必须输入整数
			inputInt(cin, ret);

			if (ret >= 1 && ret <= 2)
			{
				break;
			}
			cout << "输入有误，请重新输入！" << endl;
		}

		if (ret == 1)
		{
			// 通过情况
			of.m_orderData[v[select - 1]]["status"] = "2";
		}
		else
		{
			// 不通过情况
			of.m_orderData[v[select - 1]]["status"] = "-1";
		}
		of.updateOrder();  // 更新预约记录
		cout << "审核完毕！" << endl;
	}

	system("pause");
	system("cls");
}
