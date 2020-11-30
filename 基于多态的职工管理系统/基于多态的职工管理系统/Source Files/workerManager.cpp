#include "workerManager.h"

WorkerManager::WorkerManager()
{
	// 1 文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in);  // 读文件

	if (!ifs.is_open())
	{
		//cout << "文件不存在！" << endl;
		// 重置
		this->reset();
		ifs.close();
		return;
	}

	// 2 文件存在 数据为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "文件为空！" << endl;
		// 重置
		this->reset();
		ifs.close();
		return;
	}

	// 3 文件存在，并且记录数据
	int num = this->getNum();
	//cout << "职工人数为：" << num << endl;
	this->m_EmpNum = num;

	// 开辟空间
	this->m_EmpArray = new Worker*[this->m_EmpNum];
	// 将文件中的数据，存到数组中
	this->initEmp();
}

// 析构函数
WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != nullptr)
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			if (this->m_EmpArray[i] != nullptr)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = nullptr;
			}
		}
		delete [] this->m_EmpArray;
		this->m_EmpArray = nullptr;
	}
}

// 展示菜单
void WorkerManager::showMenu()
{
	cout << "**************************************************" << endl;
	cout << "************ 欢迎使用职工管理系统! ***************" << endl;
	cout << "**************** 0.退出管理程序 ******************" << endl;
	cout << "**************** 1.增加职工信息 ******************" << endl;
	cout << "**************** 2.显示职工信息 ******************" << endl;
	cout << "**************** 3.删除离职职工 ******************" << endl;
	cout << "**************** 4.修改职工信息 ******************" << endl;
	cout << "**************** 5.查找职工信息 ******************" << endl;
	cout << "**************** 6.按照编号排序 ******************" << endl;
	cout << "**************** 7.清空所有文档 ******************" << endl;
	cout << "**************************************************" << endl;
	cout << endl;
}

// 退出系统
void WorkerManager::exitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

// 增加职工
void WorkerManager::addEmp()
{
	cout << "请输入增加职工数量: " << endl;
	int addNum = 0;

	while (true)
	{
		// 限制必须输入整数
		inputInt(cin, addNum);

		if (addNum > 0)
		{
			break;
		}
		cout << "输入数据有误，请重新输入！" << endl;
	}

	// 计算新空间大小
	int newSize = this->m_EmpNum + addNum;

	// 开辟新空间
	Worker** newSpace = new Worker*[newSize];

	// 将原空间下数据，拷贝到新空间下
	if (this->m_EmpArray != nullptr)
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			newSpace[i] = this->m_EmpArray[i];
		}
	}

	// 批量添加新数据
	for (int i = 0; i < addNum; i++)
	{
		int		id = 0;			// 职工编号
		string	name = "";		// 职工姓名
		int		dSelect = 0;	// 部门选择

		cout << "请输入第 " << i + 1 << " 个新职工编号：" << endl;

		while (true)
		{
			// 限制必须输入整数
			inputInt(cin, id);

			// 职工编号不能重复
			if (this->isExist(id) == -1)
			{
				break;
			}
			cout << "职工编号已存在，请重新输入编号：" << endl;
		}

		cout << "请输入第 " << i + 1 << " 个新职工姓名：" << endl;
		cin >> name;

		cout << "请选择该职工岗位：" << endl;
		cout << "1、普通职工" << endl;
		cout << "2、经理" << endl;
		cout << "3、老板" << endl;
		dSelect = 0;

		while (true)
		{
			// 限制输入必须为整数
			inputInt(cin, dSelect);

			if (dSelect >= 1 && dSelect <= 3)
			{
				break;
			}
			cout << "请输入正确的数字" << endl;
		}

		Worker* worker = nullptr;
		switch (dSelect)
		{
		case 1:
			worker = new Employee(id, name, 1);
			break;
		case 2:
			worker = new Manager(id, name, 2);
			break;
		case 3:
			worker = new Boss(id, name, 3);
			break;
		default:
			break;
		}
		// 将创建职工指针，保存到数组中
		newSpace[this->m_EmpNum + i] = worker;
	}

	delete[] this->m_EmpArray;  // 释放原有空间

	this->m_EmpArray = newSpace;  // 更改新空间的指向
	this->m_EmpNum = newSize;  // 更新新的职工人数

	cout << "成功添加" << addNum << "名新职工！" << endl;  // 提示添加成功

	this->m_FileEmpty = false;  // 更新文件不为空的标志
	this->save();  // 保存到文件中

	// 按任意键后 清屏回到上级目录
	system("pause");
	system("cls");


}

// 保存文件
void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);

	for (int i = 0; i < m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}
	ofs.close();
}

// 获取职工人数
int WorkerManager::getNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id = 0;
	string name;
	int dId = 0;
	int num = 0;

	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		num++;
	}
	return num;
}

// 初始化员工
void WorkerManager::initEmp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id = 0;
	string name;
	int dId = 0;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker* worker = nullptr;
		// 根据不同的部门Id创建不同的对象
		if (dId == 1)  // 1 普通员工
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2)  // 2 经理
		{
			worker = new Manager(id, name, dId);
		}
		else  // 3 老板
		{
			worker = new Boss(id, name, dId);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}
	ifs.close();
}

// 重置
void WorkerManager::reset()
{
	// 初始化人数
	this->m_EmpNum = 0;
	// 初始化数组的指针
	this->m_EmpArray = nullptr;
	// 初始化文件是否为空
	this->m_FileEmpty = true;
}

// 显示职工
void WorkerManager::showEmp()
{
	// 判断文件是否为空
	if (this->m_FileEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			// 利用多态调用程序接口
			this->m_EmpArray[i]->showInfo();
		}
	}
	// 按任意键后清屏
	system("pause");
	system("cls");
}

// 删除职工
void WorkerManager::delEmp()
{
	if (this->m_FileEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		// 按职工编号删除
		cout << "请输入要删除的职工号：" << endl;
		int id = 0;

		// 限制必须输入整数
		inputInt(cin, id);

		int index = this->isExist(id);
		if (index != -1)  // 说明职工存在，并且要删除index上位置上的员工
		{
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				// 数据前移
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;  // 更新数组中记录人员个数

			this->save();  // 删除后数据同步到文件中
			cout << "删除成功！" << endl;
		}
		else
		{
			cout << "删除失败，未找到该职工" << endl;
		}
	}
	// 按任意键清屏
	system("pause");
	system("cls");
}

// 根据职工编号判断职工是否存在，若存在返回职工在数组中的位置，不存在返回-1
int WorkerManager::isExist(int id)
{
	int index = -1;

	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			index = i;
			
			break;
		}
	}
	return index;
}

// 修改职工
void WorkerManager::modEmp()
{
	if (this->m_FileEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请输入要修改的职工编号：" << endl;
		int id = 0;

		// 限制必须输入整数
		inputInt(cin, id);

		int ret = this->isExist(id);
		if (ret != -1)
		{
			// 查找到编号的职工
			delete this->m_EmpArray[ret];

			int newId = 0;
			string newName = "";
			int dSelect = 0;

			cout << "查到：" << id << "号职工，请输入新职工号：" << endl;

			while (true)
			{
				// 限制必须输入整数
				inputInt(cin, newId);

				if (this->isExist(newId) == -1)
				{
					break;
				}
				cout << "职工编号已存在，请重新输入编号：" << endl;
			}
			
			cout << "请输入新姓名：" << endl;
			cin >> newName;

			cout << "请输入岗位：" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			dSelect = 0;;

			while (true)
			{
				// 限制必须输入整数
				inputInt(cin, dSelect);

				if (dSelect >= 1 && dSelect <= 3)
				{
					break;
				}
				cout << "请输入正确的数字" << endl;
			}
			
			Worker* worker = nullptr;

			switch (dSelect)
			{
			case 1:
				worker = new Employee(newId, newName, dSelect);
				break;
			case 2:
				worker = new Manager(newId, newName, dSelect);
				break;
			case 3:
				worker = new Boss(newId, newName, dSelect);
				break;
			default:
				break;
			}
			
			this->m_EmpArray[ret] = worker;  // 更改数据 到数组中
			cout << "修改成功！" << this->m_EmpArray[ret]->m_DeptId << endl;
			this->save();  // 保存到文件中
 		}
		else
		{
			cout << "查找失败，查无此人！" << endl;
		}
	}
	// 按任意键清屏
	system("pause");
	system("cls");
}

// 查找职工
void WorkerManager::findEmp()
{
	if (this->m_FileEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请输入查找的方式：" << endl;
		cout << "1、按职工编号查找" << endl;
		cout << "2、按姓名查找" << endl;
		int select = 0;

		while (true)
		{
			// 限制必须输入整数
			inputInt(cin, select);

			if (select >= 1 && select <= 2)
			{
				break;
			}
			cout << "请输入正确的数字" << endl;
		}

		if (select == 1)  // 按职工编号查找
		{
			int id;
			cout << "请输入查找的职工编号：" << endl;
			cin >> id;
			int ret = this->isExist(id);
			if (ret != -1)
			{
				cout << "查找成功!该职工信息如下：" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "查找失败，查无此人！" << endl;
			}
		}
		else		// 按姓名查找
		{
			string name = "";
			cout << "请输入要查找的姓名：" << endl;
			cin >> name;

			bool flag = false;  // 默认查找不到
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					cout << "查找成功，职工编号为 "
						<< this->m_EmpArray[i]->m_Id
						<< " 号的信息如下：" << endl;

					flag = true;
					this->m_EmpArray[i]->showInfo();
				}
			}
			if (flag == false)
			{
				cout << "查找失败，查无此人！" << endl;
			}
		}
	}
	// 按任意键清屏
	system("pause");
	system("cls");
}

// 按照职工编号排序
void WorkerManager::sortEmp()
{
	if (this->m_FileEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
		// 按任意键清屏
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择排序方式：" << endl;
		cout << "1、按职工号进行升序排列" << endl;
		cout << "2、按职工号进行降序排列" << endl;	
		int select = 0;

		while (true)
		{
			// 限制必须输入整数
			inputInt(cin, select);

			if (select >= 1 && select <= 2)
			{
				break;
			}
			cout << "请输入正确的数字" << endl;
		}

		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int minOrMax = i;
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1)  // 升序
				{
					if (m_EmpArray[minOrMax]->m_Id > m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
				else  // 降序
				{
					if (m_EmpArray[minOrMax]->m_Id < m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
			}
			if (i != minOrMax)  // 交换
			{
				Worker* tmp = m_EmpArray[minOrMax];
				m_EmpArray[minOrMax] = m_EmpArray[i];
				m_EmpArray[i] = tmp;
			}
		}
		cout << "排序成功，排序后的结果为：" << endl;
		this->save();
		this->showEmp();
	}
}

// 清空文件
void WorkerManager::cleanFile()
{
	cout << "确定清空？" << endl;
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

		cout << "请输入正确的数字" << endl;
	}

	if (select == 1)
	{
		// 清空文件
		ofstream ofs(FILENAME, ios::trunc);  // 删除文件后重新创建
		ofs.close();

		if (this->m_EmpArray != nullptr)
		{
			// 删除堆区的每个职工对象
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i] != nullptr)
				{
					delete this->m_EmpArray[i];
					this->m_EmpArray[i] = nullptr;
				}
			}

			// 删除堆区数组指针
			delete[] this->m_EmpArray;
			this->m_EmpArray = nullptr;
			this->m_EmpNum = 0;
			this->m_FileEmpty = true;
		}
		cout << "清空成功！" << endl;
	}
	// 按任意键清屏
	system("pause");
	system("cls");
}


