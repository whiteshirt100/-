#include "workerManager.h"

WorkerManager::WorkerManager()
{
	// 1 �ļ�������
	ifstream ifs;
	ifs.open(FILENAME, ios::in);  // ���ļ�

	if (!ifs.is_open())
	{
		//cout << "�ļ������ڣ�" << endl;
		// ����
		this->reset();
		ifs.close();
		return;
	}

	// 2 �ļ����� ����Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "�ļ�Ϊ�գ�" << endl;
		// ����
		this->reset();
		ifs.close();
		return;
	}

	// 3 �ļ����ڣ����Ҽ�¼����
	int num = this->getNum();
	//cout << "ְ������Ϊ��" << num << endl;
	this->m_EmpNum = num;

	// ���ٿռ�
	this->m_EmpArray = new Worker*[this->m_EmpNum];
	// ���ļ��е����ݣ��浽������
	this->initEmp();
}

// ��������
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

// չʾ�˵�
void WorkerManager::showMenu()
{
	cout << "**************************************************" << endl;
	cout << "************ ��ӭʹ��ְ������ϵͳ! ***************" << endl;
	cout << "**************** 0.�˳�������� ******************" << endl;
	cout << "**************** 1.����ְ����Ϣ ******************" << endl;
	cout << "**************** 2.��ʾְ����Ϣ ******************" << endl;
	cout << "**************** 3.ɾ����ְְ�� ******************" << endl;
	cout << "**************** 4.�޸�ְ����Ϣ ******************" << endl;
	cout << "**************** 5.����ְ����Ϣ ******************" << endl;
	cout << "**************** 6.���ձ������ ******************" << endl;
	cout << "**************** 7.��������ĵ� ******************" << endl;
	cout << "**************************************************" << endl;
	cout << endl;
}

// �˳�ϵͳ
void WorkerManager::exitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

// ����ְ��
void WorkerManager::addEmp()
{
	cout << "����������ְ������: " << endl;
	int addNum = 0;
	// ���Ʊ�����������
	isInt(cin, addNum);

	if (addNum > 0)
	{
		// �����¿ռ��С
		int newSize = this->m_EmpNum + addNum;

		// �����¿ռ�
		Worker** newSpace = new Worker*[newSize];

		// ��ԭ�ռ������ݣ��������¿ռ���
		if (this->m_EmpArray != nullptr)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		// �������������
		for (int i = 0; i < addNum; i++)
		{
			int		id = 0;			// ְ�����
			string	name = "";		// ְ������
			int		dSelect = 0;	// ����ѡ��

			cout << "������� " << i + 1 << " ����ְ����ţ�" << endl;

		reEnter_addNum_id:
			id = 0;
			// ���Ʊ�����������
			isInt(cin, id);

			// ְ����Ų����ظ�
			while (this->isExist(id) != -1)
			{
				cout << "ְ������Ѵ��ڣ������������ţ�" << endl;
				goto reEnter_addNum_id;
			}

			cout << "������� " << i + 1 << " ����ְ��������" << endl;
			cin >> name;

		reEnter_addNum_dSelect:
			cout << "��ѡ���ְ����λ��" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
			dSelect = 0;
			// �����������Ϊ����
			isInt(cin, dSelect);

			if (dSelect != 1 && dSelect != 2 && dSelect != 3)
			{
				cout << "��������ȷ������" << endl;
				goto reEnter_addNum_dSelect;
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
			// ������ְ��ָ�룬���浽������
			newSpace[this->m_EmpNum + i] = worker;
		}

		delete[] this->m_EmpArray;  // �ͷ�ԭ�пռ�

		this->m_EmpArray = newSpace;  // �����¿ռ��ָ��
		this->m_EmpNum = newSize;  // �����µ�ְ������

		cout << "�ɹ����" << addNum << "����ְ����" << endl;  // ��ʾ��ӳɹ�

		this->m_FileEmpty = false;  // �����ļ���Ϊ�յı�־
		this->save();  // ���浽�ļ���

		// ��������� �����ص��ϼ�Ŀ¼
		system("pause");
		system("cls");
	}
	else
	{
		cout << "������������" << endl;
	}
}

// �����ļ�
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

// ��ȡְ������
int WorkerManager::getNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int dId;
	int num = 0;

	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		num++;
	}
	return num;
}

// ��ʼ��Ա��
void WorkerManager::initEmp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker* worker = nullptr;
		// ���ݲ�ͬ�Ĳ���Id������ͬ�Ķ���
		if (dId == 1)  // 1 ��ͨԱ��
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2)  // 2 ����
		{
			worker = new Manager(id, name, dId);
		}
		else  // 3 �ϰ�
		{
			worker = new Boss(id, name, dId);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}
	ifs.close();
}

// ����
void WorkerManager::reset()
{
	// ��ʼ������
	this->m_EmpNum = 0;
	// ��ʼ�������ָ��
	this->m_EmpArray = nullptr;
	// ��ʼ���ļ��Ƿ�Ϊ��
	this->m_FileEmpty = true;
}

// ��ʾְ��
void WorkerManager::showEmp()
{
	// �ж��ļ��Ƿ�Ϊ��
	if (this->m_FileEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			// ���ö�̬���ó���ӿ�
			this->m_EmpArray[i]->showInfo();
		}
	}
	// �������������
	system("pause");
	system("cls");
}

// ɾ��ְ��
void WorkerManager::delEmp()
{
	if (this->m_FileEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		// ��ְ�����ɾ��
		cout << "������Ҫɾ����ְ���ţ�" << endl;
		int id = 0;

		// ���Ʊ�����������
		isInt(cin, id);

		int index = this->isExist(id);
		if (index != -1)  // ˵��ְ�����ڣ�����Ҫɾ��index��λ���ϵ�Ա��
		{
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				// ����ǰ��
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;  // ���������м�¼��Ա����

			this->save();  // ɾ��������ͬ�����ļ���
			cout << "ɾ���ɹ���" << endl;
		}
		else
		{
			cout << "ɾ��ʧ�ܣ�δ�ҵ���ְ��" << endl;
		}
	}
	// �����������
	system("pause");
	system("cls");
}

// ����ְ������ж�ְ���Ƿ���ڣ������ڷ���ְ���������е�λ�ã������ڷ���-1
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

// �޸�ְ��
void WorkerManager::modEmp()
{
	if (this->m_FileEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "������Ҫ�޸ĵ�ְ����ţ�" << endl;
		int id = 0;

		// ���Ʊ�����������
		isInt(cin, id);

		int ret = this->isExist(id);
		if (ret != -1)
		{
			// ���ҵ���ŵ�ְ��
			delete this->m_EmpArray[ret];

			int newId = 0;
			string newName = "";
			int dSelect = 0;

			cout << "�鵽��" << id << "��ְ������������ְ���ţ�" << endl;

		reEnter_modEmp_newId:
			newId = 0;
			// ���Ʊ�����������
			isInt(cin, newId);

			while (this->isExist(newId) != -1)
			{
				cout << "ְ������Ѵ��ڣ������������ţ�" << endl;
				goto reEnter_modEmp_newId;
			}

			cout << "��������������" << endl;
			cin >> newName;

		reEnter_modEmp_dSelect:
			cout << "�������λ��" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
			dSelect = 0;
			// ���Ʊ�����������
			isInt(cin, dSelect);

			if (dSelect != 1 && dSelect != 2 && dSelect != 3)
			{
				cout << "��������ȷ������" << endl;
				goto reEnter_modEmp_dSelect;
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
			
			this->m_EmpArray[ret] = worker;  // �������� ��������

			cout << "�޸ĳɹ���" << this->m_EmpArray[ret]->m_DeptId << endl;

			this->save();  // ���浽�ļ���
 		}
		else
		{
			cout << "����ʧ�ܣ����޴��ˣ�" << endl;
		}
	}
	// �����������
	system("pause");
	system("cls");
}

// ����ְ��
void WorkerManager::findEmp()
{
	if (this->m_FileEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
	reEnter_findEmp_select:
		cout << "��������ҵķ�ʽ��" << endl;
		cout << "1����ְ����Ų���" << endl;
		cout << "2������������" << endl;
		int select = 0;
		// ���Ʊ�����������
		isInt(cin, select);

		while (select != 1 && select != 2)
		{
			cout << "��������ȷ������" << endl;
			goto reEnter_findEmp_select;
		}

		if (select == 1)  // ��ְ����Ų���
		{	
			int id;
			cout << "��������ҵ�ְ����ţ�" << endl;
			cin >> id;
			int ret = this->isExist(id);
			if (ret != -1)
			{
				cout << "���ҳɹ�!��ְ����Ϣ���£�" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "����ʧ�ܣ����޴��ˣ�" << endl;
			}
		}
		else if (select == 2)  // ����������
		{
			string name = "";
			cout << "������Ҫ���ҵ�������" << endl;
			cin >> name;

			bool flag = false;  // Ĭ�ϲ��Ҳ���
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					cout << "���ҳɹ���ְ�����Ϊ " 
						 << this->m_EmpArray[i]->m_Id 
						 << " �ŵ���Ϣ���£�" << endl;
					
					flag = true;
					this->m_EmpArray[i]->showInfo();
				}
			}
			if (flag == false)
			{
				cout << "����ʧ�ܣ����޴��ˣ�" << endl;
			}
		}
		else
		{
			cin.clear();
			cout << "����ѡ������" << endl;
		}
	}
	// �����������
	system("pause");
	system("cls");
}

// ����ְ���������
void WorkerManager::sortEmp()
{
	if (this->m_FileEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
		// �����������
		system("pause");
		system("cls");
	}
	else
	{
	reEnter_sortEmp_select:
		cout << "��ѡ������ʽ��" << endl;
		cout << "1����ְ���Ž�����������" << endl;
		cout << "2����ְ���Ž��н�������" << endl;	
		int select = 0;
		// ���Ʊ�����������
		isInt(cin, select);

		while (select != 1 && select != 2)
		{
			cout << "��������ȷ������" << endl;
			goto reEnter_sortEmp_select;
		}

		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int minOrMax = i;
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1)  // ����
				{
					if (m_EmpArray[minOrMax]->m_Id > m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
				else  // ����
				{
					if (m_EmpArray[minOrMax]->m_Id < m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
			}
			if (i != minOrMax)  // ����
			{
				Worker* tmp = m_EmpArray[minOrMax];
				m_EmpArray[minOrMax] = m_EmpArray[i];
				m_EmpArray[i] = tmp;
			}
		}
		cout << "����ɹ��������Ľ��Ϊ��" << endl;
		this->save();
		this->showEmp();
	}
}

// ����ļ�
void WorkerManager::cleanFile()
{
reEnter_cleanFile_select:
	cout << "ȷ����գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;
	int select = 0;
	// ���Ʊ�����������
	isInt(cin, select);

	while (select != 1 && select != 2)
	{
		cout << "��������ȷ������" << endl;
		goto reEnter_cleanFile_select;
	}

	if (select == 1)
	{
		// ����ļ�
		ofstream ofs(FILENAME, ios::trunc);  // ɾ���ļ������´���
		ofs.close();

		if (this->m_EmpArray != nullptr)
		{
			// ɾ��������ÿ��ְ������
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i] != nullptr)
				{
					delete this->m_EmpArray[i];
					this->m_EmpArray[i] = nullptr;
				}
			}

			// ɾ����������ָ��
			delete[] this->m_EmpArray;
			this->m_EmpArray = nullptr;
			this->m_EmpNum = 0;
			this->m_FileEmpty = true;
		}
		cout << "��ճɹ���" << endl;
	}
	// �����������
	system("pause");
	system("cls");
}

// ���Ʊ�����������
void WorkerManager::isInt(istream & in, int& num)
{
	int s;
	char str[200];
	in >> num;
	s = in.rdstate();
	while (s)
	{
		in.clear();
		in >> str;
		cout << "��������Ϊ��������������������" << endl;
		in >> num;
		s = in.rdstate();
	}
}

