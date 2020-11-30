#include "manager.h"

// Ĭ�Ϲ���
Manager::Manager()
{
}

// �вι��죨����Ա���������룩
Manager::Manager(string name, string password)
{
	// ��ʼ������Ա��Ϣ
	this->m_name = name;
	this->m_password = password;

	// ��ʼ������ ��ȡ�������ļ��� ѧ������ʦ��Ϣ
	this->initVector();

	// ��ʼ�� ��ȡ������Ϣ
	this->getCom();
}

// ѡ��˵�
void Manager::openMenu()
{
	cout << "��ӭ����Ա��" << this->m_name << "��¼��" << endl;
	cout << "\t\t --------------------------------- " << endl;
	cout << "\t\t|                                 |" << endl;
	cout << "\t\t|          1������˺�            |" << endl;
	cout << "\t\t|                                 |" << endl;
	cout << "\t\t|          2���鿴�˺�            |" << endl;
	cout << "\t\t|                                 |" << endl;
	cout << "\t\t|          3���鿴����            |" << endl;
	cout << "\t\t|                                 |" << endl;
	cout << "\t\t|          4�����ԤԼ            |" << endl;
	cout << "\t\t|                                 |" << endl;
	cout << "\t\t|          0��ע����¼            |" << endl;
	cout << "\t\t|                                 |" << endl;
	cout << "\t\t --------------------------------- " << endl;
	cout << "��ѡ�����Ĳ�����" << endl;
}

// ����˺�
void Manager::addPerson()
{
	cout << "��������ӵ��˺����ͣ�" << endl;
	cout << "1�����ѧ��" << endl;
	cout << "2�������ʦ" << endl;

	string fileName = "";	// �����ļ���
	string tip = "";		// ��ʾid��
	ofstream ofs;			// �ļ���������

	int select = 0;			// �����û���ѡ��
	string errorTip;		// �ظ�������ʾ

	while (true)
	{
		// ���Ʊ�����������
		inputInt(cin, select);

		if (select >= 1 && select <= 2)
		{
			break;
		}
		cout << "�����������������룡" << endl;
	}

	if (select == 1)
	{
		// ��ӵ���ѧ��
		fileName = STUDENT_FILE;
		tip = "������ѧ�ţ�";
		errorTip = "ѧ���ظ�������������";
	}
	else
	{
		// ��ӵ�����ʦ
		fileName = TEACHER_FILE;
		tip = "������ְ�����";
		errorTip = "ְ�����ظ�������������";
	}

	// ����׷�ӵķ�ʽ д�ļ�
	ofs.open(fileName, ios::out | ios::app);
	int id;				// ѧ��/ְ����
	string name;		// ����
	string password;	// ����
	
	cout << tip << endl;

	// Ҫ��ѧ��/ְ���Ų����ظ�
	while (true)
	{
		// ���Ʊ�����������
		inputInt(cin, id);

		bool ret = this->checkRepeat(id, select);

		if (ret)  // ���ظ�
		{
			cout << errorTip << endl;
		}
		else
		{
			break;
		}
	}

	cout << "������������" << endl;
	cin >> name;

	cout << "���������룺" << endl;
	cin >> password;

	// ���ļ����������
	ofs << id << " " << name << " " << password << " " << endl;
	cout << "��ӳɹ���" << endl;

	system("pause");
	system("cls");

	ofs.close();

	// ��ʼ������ ���»�ȡ��������
	this->initVector();
}

void printStudent(Student &s)
{
	cout << "ѧ�ţ�" << s.m_id << " ������" << s.m_name << " ���룺" << s.m_password << endl;
}

void printTeacher(Teacher &t)
{
	cout << "ѧ�ţ�" << t.m_empId << " ������" << t.m_name << " ���룺" << t.m_password << endl;
}

// �鿴�˺�
void Manager::showPerson()
{
	cout << "������Ҫ�鿴�����ݣ�" << endl;
	cout << "1���鿴ѧ��" << endl;
	cout << "2���鿴��ʦ" << endl;

	int select = 0;  // �����û�����
	while (true)
	{
		// ���Ʊ�����������
		inputInt(cin, select);
		if (select >= 1 && select <= 2)
		{
			break;
		}
		cout << "�����������������룡" << endl;
	}

	if (select == 1)
	{
		cout << "����ѧ����Ϣ���£�" << endl;
		for_each(vStu.begin(), vStu.end(), printStudent);
	}
	else
	{
		cout << "������ʦ��Ϣ���£�" << endl;
		for_each(vTea.begin(), vTea.end(), printTeacher);
	}

	system("pause");
	system("cls");
}

void printComputerRoom(ComputerRoom &c)
{
	cout << "������ţ�" << c.m_comId << " �������������" << c.m_maxNum << endl;
}

// �鿴������Ϣ
void Manager::showComputer()
{
	cout << "������Ϣ���£�" << endl;

	for_each(vCom.begin(), vCom.end(), printComputerRoom);
	
	system("pause");
	system("cls");
}

// ���ԤԼ��¼
void Manager::cleanFile()
{
	cout << "�Ƿ�ȷ�����ԤԼ��¼��" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;
	int select = 0;

	while (true)
	{
		// ���Ʊ�����������
		inputInt(cin, select);

		if (select >= 1 && select <= 2)
		{
			break;
		}

		cout << "�����������������룡" << endl;
	}

	if (select == 1)
	{
		ofstream ofs(ORDER_FILE, ios::trunc);
		ofs.close();
		cout << "��ճɹ���" << endl;
	}

	system("pause");
	system("cls");
}

// ��ʼ������
void Manager::initVector()
{
	// ȷ���������״̬
	vStu.clear();
	vTea.clear();

	// ��ȡ��Ϣ ѧ��
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ���ȡʧ�ܣ�" << endl;
		return;
	}
	Student s;
	while (ifs >> s.m_id && ifs >> s.m_name && ifs >> s.m_password)
	{
		vStu.push_back(s);
	}
	cout << "��ǰѧ������Ϊ��" << vStu.size() << endl;
	ifs.close();

	// ��ȡ��Ϣ ��ʦ
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ���ʧ�ܣ�" << endl;
		return;
	}
	Teacher t;
	while (ifs >> t.m_empId && ifs >> t.m_name && ifs >> t.m_password)
	{
		vTea.push_back(t);
	}
	cout << "��ǰ��ʦ����Ϊ��" << vTea.size() << endl;
	ifs.close();
}

// ����ظ� ����������id���������ͣ� ����ֵ��true�������ظ���false����û���ظ���
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

// ��ȡ������Ϣ
void Manager::getCom()
{
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);

	if (!ifs.is_open())
	{
		cout << "�ļ���ʧ��" << endl;
		return;
	}

	ComputerRoom c;
	while (ifs >> c.m_comId && ifs >> c.m_maxNum)
	{
		vCom.push_back(c);
	}
	cout << "��ǰ��������Ϊ��" << vCom.size() << endl;

	ifs.close();
}
