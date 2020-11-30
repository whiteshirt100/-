#include "student.h"

// 默认构造
Student::Student()
{
}

// 有参构造  参数：姓名、学号、密码
Student::Student(int id, string name, string password)
{
	// 初始化属性
	this->m_id = id;
	this->m_name = name;
	this->m_password = password;

	// 初始化 获取机房信息
	this->getCom();
}

// 菜单界面
void Student::openMenu()
{
	cout << "欢迎学生代表：" << this->m_name << "登录！" << endl;
	cout << "\t\t --------------------------------- " << endl;
	cout << "\t\t|                                 |" << endl;
	cout << "\t\t|          1、申请预约            |" << endl;
	cout << "\t\t|                                 |" << endl;
	cout << "\t\t|          2、查看我的预约        |" << endl;
	cout << "\t\t|                                 |" << endl;
	cout << "\t\t|          3、查看所有预约        |" << endl;
	cout << "\t\t|                                 |" << endl;
	cout << "\t\t|          4、取消预约            |" << endl;
	cout << "\t\t|                                 |" << endl;
	cout << "\t\t|          0、注销登录            |" << endl;
	cout << "\t\t|                                 |" << endl;
	cout << "\t\t --------------------------------- " << endl;
	cout << "请选择您的操作：" << endl;
}

// 申请预约
void Student::applyOrder()
{
	cout << "机房开放时间为周一到周五" << endl;
	cout << "请输入申请预约的时间为：" << endl;
	cout << "1、周一" << endl;
	cout << "2、周二" << endl;
	cout << "3、周三" << endl;
	cout << "4、周四" << endl;
	cout << "5、周五" << endl;

	int date = 0;		// 日期
	int interval = 0;	// 时间段
	int room = 0;		// 机房编号

	while (true)
	{
		// 限制必须输入整数
		inputInt(cin, date);

		if (date >= 1 && date <= 5)
		{
			break;
		}
		cout << "输入日期有误，请重新输入！" << endl;
	}

	cout << "请输入申请预约的时间段：" << endl;
	cout << "1、上午" << endl;
	cout << "2、下午" << endl;

	while (true)
	{
		// 限制必须输入整数
		inputInt(cin, interval);

		if (interval >= 1 && interval <= 2)
		{
			break;
		}
		cout << "输入的时间段有误，请重新输入！" << endl;
	}

	cout << "请选择机房：" << endl;
	for (int i = 0; i < (int)vCom.size(); i++)
	{
		cout << vCom[i].m_comId << "号机房容量为：" << vCom[i].m_maxNum << endl;
	}
	while (true)
	{
		// 限制必须输入整数
		inputInt(cin, room);

		if (room >= 1 && room <= 3)
		{
			break;
		}
		cout << "输入的机房号有误，请重新输入！" << endl;
	}

	cout << "预约成功！审核中..." << endl;

	// 保存预约信息到文件
	this->save(date, interval, this->m_id, this->m_name, room, "1");

	system("pause");
	system("cls");

}

// data:1 interval:2 stuId:1 stuName:张三 roomId:2 status:1
/*
map<string, string>			key代表 属性    value代表 实值
key    data		value	1
key    interval value	2
key    stuId	value	1
key    stuName	value	张三
key    roomId	value	2
key    status	value	1

// 使用容器嵌套容器 把所有数据维护住
map<int, map<string, string>>    key 预约记录条数  value 代表一条记录中的所有信息
*/
// 查看自身预约
void Student::showMyOrder()
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
		// string 转 int
		// string 利用 .c_str() 转 const char *
		// 利用atoi(const char *) 转 int
		if (this->m_id == atoi(of.m_orderData[i]["stuId"].c_str()))
		{
			cout << "预约日期：周" << of.m_orderData[i]["date"];
			cout << "  时段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
			cout << "  机房：" << of.m_orderData[i]["roomId"];
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
	}

	system("pause");
	system("cls");
}

// 查看所有预约
void Student::showAllOrder()
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
		cout << "  机房：" << of.m_orderData[i]["roomId"];
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

// 取消预约
void Student::cancelOrder()
{
	OrderFile of;
	if (of.m_size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}

	cout << "审核中或预约成功的记录可以取消，请输入要取消的记录：" << endl;
	vector<int>v;  // 存放在最大容器中的下标编号
	int index = 1;
	for (int i = 0; i < of.m_size; i++)
	{
		// 先判断是自身学号
		if (this->m_id == atoi(of.m_orderData[i]["stuId"].c_str()))
		{
			// 再筛选状态 审核中或预约成功
			if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2")
			{
				v.push_back(i);
				cout << index++ << "、";  // 给用户提供的下标用index提示，但实际容器中下标用容器 vector<int>v 存储
				cout << "预约日期：周" << of.m_orderData[i]["date"];
				cout << "  时段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
				cout << "  机房：" << of.m_orderData[i]["roomId"];
				string status = "  状态：";
				// 1 审核中   2 预约成功
				if (of.m_orderData[i]["status"] == "1")
				{
					status += "审核中";
				}
				else if (of.m_orderData[i]["status"] == "2")
				{
					status += "预约成功";
				}
				cout << status << endl;
			}
		}
	}

	cout << "请输入取消的记录，0代表返回" << endl;
	int select = 0;

	while (true)
	{
		// 限制必须输入整数
		inputInt(cin, select);
		// 限制输入范围为 [0, v.size()] 之间
		if (select >= 0 && select <= (int)v.size())
		{
			break;
		}
		cout << "输入有误，请重新输入" << endl;
	}

	if (select != 0)
	{
		// 记录所在位置
		of.m_orderData[v[select - 1]]["status"] = "0";
		of.updateOrder();
		cout << "已取消预约" << endl;
	}

	system("pause");
	system("cls");
}


// 初始化 获取机房信息
void Student::getCom()
{
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);

	if (!ifs.is_open())
	{
		cout << "文件打开失败！" << endl;
		return;
	}
	ComputerRoom com;
	while (ifs >> com.m_comId && ifs >> com.m_maxNum)
	{
		// 将读取到的信息放入到 容器中
		vCom.push_back(com);
	}

	ifs.close();
}

// 保存预约信息
void Student::save(int date, int interval, int stuId, string stuName, int roomId, string status)
{
	ofstream ofs;
	ofs.open(ORDER_FILE, ios::app);

	ofs << "date:" << date << " ";
	ofs << "interval:" << interval << " ";
	ofs << "stuId:" << this->m_id << " ";
	ofs << "stuName:" << this->m_name << " ";
	ofs << "roomId:" << roomId << " ";
	ofs << "status:" << status << endl;  // 预约状态1(审核中)

	ofs.close();
}
