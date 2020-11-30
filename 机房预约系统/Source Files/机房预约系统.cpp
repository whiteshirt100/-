
#include <iostream>
#include <string>
#include <fstream>
#include "globalFile.h"
#include "Identity.h"
#include "student.h"
#include "teacher.h"
#include "manager.h"

using namespace std;

// ����ѧ���Ӳ˵�����
void studentMenu(Identity* &student)
{
	while (true)
	{
		// ����ѧ���Ӳ˵�
		student->openMenu();

		// ������ָ�� תΪ����ָ�룬���������������ӿ�
		Student * stu = (Student*)student;

		int select = 0;
		// �����û�ѡ��
		// ���Ʊ�����������
		inputInt(cin, select);

		switch (select)
		{
		case 1:		// ����ԤԼ
			//cout << "����ԤԼ" << endl;
			stu->applyOrder();
			break;
		case 2:		// �鿴����ԤԼ
			//cout << "�鿴����ԤԼ" << endl;
			stu->showMyOrder();
			break;
		case 3:		// �鿴����ԤԼ
			//cout << "�鿴����ԤԼ" << endl;
			stu->showAllOrder();
			break;
		case 4:		// ȡ��ԤԼ
			//cout << "ȡ��ԤԼ" << endl;
			stu->cancelOrder();
			break;
		case 0:		// ע����¼
			delete student;  // ���ٶ�������
			cout << "ע���ɹ���" << endl;
			system("pause");
			system("cls");
			return;
		default:
			cout << "��������������ѡ��" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}

// �����ʦ�Ӳ˵�����
void teacherMenu(Identity* &teacher)
{
	while (true)
	{
		// ���ý�ʦ�Ӳ˵�
		teacher->openMenu();

		// ������ָ�� תΪ����ָ�룬���������������ӿ�
		Teacher * tea = (Teacher*)teacher;

		int select = 0;		// �����û�ѡ��
		
		// ���Ʊ�����������
		inputInt(cin, select);

		switch (select)
		{
		case 1:		// �鿴����ԤԼ
			//cout << "�鿴����ԤԼ" << endl;
			tea->showAllOrder();
			break;
		case 2:		// ���ԤԼ
			//cout << "���ԤԼ" << endl;
			tea->validOrder();
			break;
		case 0:		// ע����¼
			delete teacher;  // ���ٶ�������
			cout << "ע���ɹ���" << endl;
			system("pause");
			system("cls");
			return;
			break;
		default:
			cout << "��������������ѡ��" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}

// �������Ա�Ӳ˵�����
void managerMenu(Identity* &manager)
{
	while (true)
	{
		// ���ù���Ա�Ӳ˵�
		manager->openMenu();

		// ������ָ�� תΪ����ָ�룬���������������ӿ�
		Manager * man = (Manager*)manager;

		int select = 0;
		// �����û�ѡ��
		// ���Ʊ�����������
		inputInt(cin, select);

		switch (select)
		{
		case 1:		// ����˺�
			//cout << "����˺�" << endl;
			man->addPerson();
			break;
		case 2:		// �鿴�˺�
			//cout << "�鿴�˺�" << endl;
			man->showPerson();
			break;
		case 3:		// �鿴����
			//cout << "�鿴����" << endl;
			man->showComputer();
			break;
		case 4:		// ���ԤԼ
			//cout << "���ԤԼ" << endl;
			man->cleanFile();
			break;
		case 0:		// ע����¼
			delete manager;  // ���ٶ�������
			cout << "ע���ɹ���" << endl;
			system("pause");
			system("cls");
			return;
			break;
		default:
			cout << "��������������ѡ��" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}

// ��¼���ܣ�ȫ�ֺ����� 
// ����1 �����ļ���  ����2 �����������
void loginIn(string fileName, int type)
{
	Identity* person = nullptr;  // ����ָ�룬����ָ���������

	// ���ļ�
	ifstream ifs;
	ifs.open(fileName, ios::in);

	if (!ifs.is_open())
	{
		cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}

	// ׼�������û�����Ϣ
	int id = 0;
	string name = "";
	string password = "";

	// �ж����
	if (type == 1)  // ѧ�����
	{
		cout << "���������ѧ�ţ�" << endl;
		// ���Ʊ�����������
		inputInt(cin, id);
	}
	else if (type == 2)  // ��ʦ���
	{
		cout << "����������ְ���ţ�" << endl;
		// ���Ʊ�����������
		inputInt(cin, id);
	}

	cout << "�������û�����" << endl;
	cin >> name;

	cout << "���������룺" << endl;
	cin >> password;

	if (type == 1)
	{
		// ѧ�������֤
		int fId;		// ���ļ��л�ȡid��
		string fName;		// ���ļ��л�ȡ������
		string fPassword;	// ���ļ��л�ȡ������

		while (ifs >> fId && ifs >> fName && ifs >> fPassword)
		{
			// ���û��������Ϣ���Ա�
			if (fId == id && fName == name && fPassword == password)
			{
				cout << "ѧ����֤��¼�ɹ���" << endl;
				// ��¼�ɹ��󣬰����������ѧ������
				system("pause");
				system("cls");
				person = new Student(id, name, password);
				// ����ѧ������Ӳ˵�
				studentMenu(person);
				return;
			}
		}
	}

	else if (type == 2)
	{
		// ��ʦ�����֤
		int fId;			// ���ļ��л�ȡid��
		string fName;		// ���ļ��л�ȡ������
		string fPassword;	// ���ļ��л�ȡ������

		while (ifs >> fId && ifs >> fName && ifs >> fPassword)
		{
			// ���û��������Ϣ���Ա�
			if (fId == id && fName == name && fPassword == password)
			{
				cout << "��ʦ��֤��¼�ɹ���" << endl;
				// ��¼�ɹ��󣬰������������ʦ����
				system("pause");
				system("cls");
				person = new Teacher(id, name, password);
				// ������ʦ����Ӳ˵�
				teacherMenu(person);
				return;
			}
		}
	}
	else if (type == 3)
	{
		// ����Ա�����֤
		string fName;		// ���ļ��л�ȡ������
		string fPassword;	// ���ļ��л�ȡ������

		while (ifs >> fName && ifs >> fPassword)
		{
			// ���û��������Ϣ���Ա�
			if (fName == name && fPassword == password)
			{
				cout << "����Ա��֤��¼�ɹ���" << endl;
				// ��¼�ɹ��󣬰�������������Ա����
				system("pause");
				system("cls");
				person = new Manager(name, password);
				// �������Ա����Ӳ˵�
				managerMenu(person);
				return;
			}
		}
	}

	cout << "��֤��½ʧ�ܣ�" << endl;
	system("pause");
	system("cls");

}

int main()
{
	int select = 0;			// ���ڽ����û���ѡ��
	while (true)
	{
		cout << "===================== ��ӭ�����������ԤԼϵͳ =====================" << endl;
		cout << "������������ݣ�" << endl;
		cout << "\t\t --------------------------------- " << endl;
		cout << "\t\t|                                 |" << endl;
		cout << "\t\t|          1��ѧ������            |" << endl;
		cout << "\t\t|                                 |" << endl;
		cout << "\t\t|          2����    ʦ            |" << endl;
		cout << "\t\t|                                 |" << endl;
		cout << "\t\t|          3���� �� Ա            |" << endl;
		cout << "\t\t|                                 |" << endl;
		cout << "\t\t|          0����    ��            |" << endl;
		cout << "\t\t|                                 |" << endl;
		cout << "\t\t --------------------------------- " << endl;
		cout << "����������ѡ��" << endl;

		// �����û�ѡ��
		// ���Ʊ�����������
		inputInt(cin, select);

		switch (select)		// �����û�ѡ�� ʵ�ֲ�ͬ�Ľӿ�
		{
		case 1:		// ѧ�����
			loginIn(STUDENT_FILE, select);
			break;
		case 2:		// ��ʦ���
			loginIn(TEACHER_FILE, select);
			break;
		case 3:		// ����Ա���
			loginIn(ADMIN_FILE, select);
			break;
		case 0:		// �˳�ϵͳ
			cout << "��ӭ�´�ʹ�ã�" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "��������������ѡ��" << endl;
			system("pause");
			system("cls");
			break;
		}
	}

	system("pause");
	return 0;
}