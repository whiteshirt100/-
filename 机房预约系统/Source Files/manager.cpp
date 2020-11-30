#include "manager.h"

// 默认构造
Manager::Manager()
{
}

// 有参构造（管理员姓名，密码）
Manager::Manager(string name, string password)
{
	// 初始化管理员信息
	this->m_name = name;
	this->m_password = password;

	// 初始化容器 获取到所有文件中 学生、老师信息
	this->initVector();

	// 初始化 获取机房信息
	this->getCom();
}

// 选择菜单
void Manager::openMenu()
{
	cout << "欢迎管理员：" << this->m_name << "登录！" << endl;
	cout << "\t\t --------------------------------- " << endl;
	cout << "\t\t|                                 |" << endl;
	cout << "\t\t|          1、添加账号            |" << endl;
	cout << "\t\t|                                 |" << endl;
	cout << "\t\t|          2、查看账号            |" << endl;
	cout << "\t\t|                                 |" << endl;
	cout << "\t\t|          3、查看机房            |" << endl;
	cout << "\t\t|                                 |" << endl;
	cout << "\t\t|          4、清空预约            |" << endl;
	cout << "\t\t|                                 |" << endl;
	cout << "\t\t|          0、注销登录            |" << endl;
	cout << "\t\t|                                 |" << endl;
	cout << "\t\t --------------------------------- " << endl;
	cout << "请选择您的操作：" << endl;
}

// 添加账号
void Manager::addPerson()
{
	cout << "请输入添加的账号类型：" << endl;
	cout << "1、添加学生" << endl;
	cout << "2、添加老师" << endl;

	string fileName = "";	// 操作文件名
	string tip = "";		// 提示id号
	ofstream ofs;			// 文件操作对象

	int select = 0;			// 接受用户的选项
	string errorTip;		// 重复错误提示

	while (true)
	{
		// 限制必须输入整数
		inputInt(cin, select);

		if (select >= 1 && select <= 2)
		{
			break;
		}
		cout << "输入有误，请重新输入！" << endl;
	}

	if (select == 1)
	{
		// 添加的是学生
		fileName = STUDENT_FILE;
		tip = "请输入学号：";
		errorTip = "学号重复，请重新输入";
	}
	else
	{
		// 添加的是老师
		fileName = TEACHER_FILE;
		tip = "请输入职工编号";
		errorTip = "职工号重复，请重新输入";
	}

	// 利用追加的方式 写文件
	ofs.open(fileName, ios::out | ios::app);
	int id;				// 学号/职工号
	string name;		// 姓名
	string password;	// 密码
	
	cout << tip << endl;

	// 要求学号/职工号不能重复
	while (true)
	{
		// 限制必须输入整数
		inputInt(cin, id);

		bool ret = this->checkRepeat(id, select);

		if (ret)  // 有重复
		{
			cout << errorTip << endl;
		}
		else
		{
			break;
		}
	}

	cout << "请输入姓名：" << endl;
	cin >> name;

	cout << "请输入密码：" << endl;
	cin >> password;

	// 向文件中添加数据
	ofs << id << " " << name << " " << password << " " << endl;
	cout << "添加成功！" << endl;

	system("pause");
	system("cls");

	ofs.close();

	// 初始化容器 重新获取容器数据
	this->initVector();
}

void printStudent(Student &s)
{
	cout << "学号：" << s.m_id << " 姓名：" << s.m_name << " 密码：" << s.m_password << endl;
}

void printTeacher(Teacher &t)
{
	cout << "学号：" << t.m_empId << " 姓名：" << t.m_name << " 密码：" << t.m_password << endl;
}

// 查看账号
void Manager::showPerson()
{
	cout << "请输入要查看的内容：" << endl;
	cout << "1、查看学生" << endl;
	cout << "2、查看老师" << endl;

	int select = 0;  // 接受用户输入
	while (true)
	{
		// 限制必须输入整数
		inputInt(cin, select);
		if (select >= 1 && select <= 2)
		{
			break;
		}
		cout << "输入有误，请重新输入！" << endl;
	}

	if (select == 1)
	{
		cout << "所有学生信息如下：" << endl;
		for_each(vStu.begin(), vStu.end(), printStudent);
	}
	else
	{
		cout << "所有老师信息如下：" << endl;
		for_each(vTea.begin(), vTea.end(), printTeacher);
	}

	system("pause");
	system("cls");
}

void printComputerRoom(ComputerRoom &c)
{
	cout << "机房编号：" << c.m_comId << " 机房最大容量：" << c.m_maxNum << endl;
}

// 查看机房信息
void Manager::showComputer()
{
	cout << "机房信息如下：" << endl;

	for_each(vCom.begin(), vCom.end(), printComputerRoom);
	
	system("pause");
	system("cls");
}

// 清空预约记录
void Manager::cleanFile()
{
	cout << "是否确认清空预约记录？" << endl;
	cout << "1、确认" << endl;
	cout << "2、返回" << endl;
	int select = 0;

	while (true)
	{
		// 限制必须输入整数
		inputInt(cin, select);

		if (select >= 1 && select <= 2)
		{
			break;
		}

		cout << "输入有误，请重新输入！" << endl;
	}

	if (select == 1)
	{
		ofstream ofs(ORDER_FILE, ios::trunc);
		ofs.close();
		cout << "清空成功！" << endl;
	}

	system("pause");
	system("cls");
}

// 初始化容器
void Manager::initVector()
{
	// 确保容器清空状态
	vStu.clear();
	vTea.clear();

	// 读取信息 学生
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件读取失败！" << endl;
		return;
	}
	Student s;
	while (ifs >> s.m_id && ifs >> s.m_name && ifs >> s.m_password)
	{
		vStu.push_back(s);
	}
	cout << "当前学生数量为：" << vStu.size() << endl;
	ifs.close();

	// 读取信息 老师
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件打开失败！" << endl;
		return;
	}
	Teacher t;
	while (ifs >> t.m_empId && ifs >> t.m_name && ifs >> t.m_password)
	{
		vTea.push_back(t);
	}
	cout << "当前老师数量为：" << vTea.size() << endl;
	ifs.close();
}

// 检测重复 参数（传入id，传入类型） 返回值（true代表有重复，false代表没有重复）
bool Manager::checkRepeat(int id, int type)
{
	if (type == 1)
	{
		for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++)
		{
			if (id == it->m_id)
			{
				return true;
			}
		}
	}
	else
	{
		for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++)
		{
			if (id == it->m_empId)
			{
				return true;
			}
		}
	}
	return false;
}

// 获取机房信息
void Manager::getCom()
{
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);

	if (!ifs.is_open())
	{
		cout << "文件打开失败" << endl;
		return;
	}

	ComputerRoom c;
	while (ifs >> c.m_comId && ifs >> c.m_maxNum)
	{
		vCom.push_back(c);
	}
	cout << "当前机房数量为：" << vCom.size() << endl;

	ifs.close();
}
