#include "teacher.h"

// Ĭ�Ϲ���
Teacher::Teacher()
{
}

// �вι��죨ְ����š����������룩
Teacher::Teacher(int empId, string name, string password)
{
	// ��ʼ������
	this->m_empId = empId;
	this->m_name = name;
	this->m_password = password;
}

// �˵�����
void Teacher::openMenu()
{
	cout << "��ӭ��ʦ��" << this->m_name << "��¼��" << endl;
	cout << "\t\t --------------------------------- " << endl;
	cout << "\t\t|                                 |" << endl;
	cout << "\t\t|          1���鿴����ԤԼ        |" << endl;
	cout << "\t\t|                                 |" << endl;
	cout << "\t\t|          2�����ԤԼ            |" << endl;
	cout << "\t\t|                                 |" << endl;
	cout << "\t\t|          0��ע����¼            |" << endl;
	cout << "\t\t|                                 |" << endl;
	cout << "\t\t --------------------------------- " << endl;
	cout << "��ѡ�����Ĳ�����" << endl;
}

// �鿴����ԤԼ
void Teacher::showAllOrder()
{
	OrderFile of;
	if (of.m_size == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < of.m_size; i++)
	{
		cout << i + 1 << "��";
		cout << "ԤԼ���ڣ���" << of.m_orderData[i]["date"];
		cout << "  ʱ�Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����");
		cout << "  ѧ�ţ�" << of.m_orderData[i]["stuId"];
		cout << "  ������" << of.m_orderData[i]["stuName"];
		cout << "  ������ţ�" << of.m_orderData[i]["roomId"];
		string status = "  ״̬��";
		// 1 �����   2 ��ԤԼ   -1 ԤԼʧ��   0 ȡ��ԤԼ
		if (of.m_orderData[i]["status"] == "1")
		{
			status += "�����";
		}
		else if (of.m_orderData[i]["status"] == "2")
		{
			status += "ԤԼ�ɹ�";
		}
		else if (of.m_orderData[i]["status"] == "-1")
		{
			status += "ԤԼʧ�ܣ����δͨ��";
		}
		else
		{
			status += "ԤԼ��ȡ��";
		}
		cout << status << endl;
	}
	system("pause");
	system("cls");
}

// ���ԤԼ
void Teacher::validOrder()
{
	OrderFile of;
	if (of.m_size == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}

	cout << "����˵�ԤԼ��¼���£�" << endl;
	vector<int>v;  // ���ļ����±���
	int index = 1;
	for (int i = 0; i < of.m_size; i++)
	{
		// ɸѡ״̬ �����
		if (of.m_orderData[i]["status"] == "1")
		{
			v.push_back(i);
			cout << index++ << "��";  // ���û��ṩ���±���index��ʾ����ʵ���������±������� vector<int>v �洢
			cout << "ԤԼ���ڣ���" << of.m_orderData[i]["date"];
			cout << "  ʱ�Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����");
			cout << "  ѧ�ţ�" << of.m_orderData[i]["stuId"];
			cout << "  ������" << of.m_orderData[i]["stuName"];
			cout << "  ������" << of.m_orderData[i]["roomId"];
			string status = "  ״̬�������";
			cout << status << endl;
		}
		
	}
	//cout << v.size() << endl;
	if (v.size() == 0)
	{
		cout << "����˼�¼Ϊ��" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "��������˵�ԤԼ��¼��0������" << endl;
	int select = 0;	// �����û�ѡ���ԤԼ��¼
	int ret = 0;	// ����ԤԼ�����¼
	while (true)
	{
		// ���Ʊ�����������
		inputInt(cin, select);
		// 
		if (select >= 0 && select <= v.size())
		{
			break;
		}
		cout << "�����������������룡" << endl;
	}

	if (select != 0)
	{
		cout << "��������˽����" << endl;
		cout << "1��ͨ��" << endl;
		cout << "2����ͨ��" << endl;
		while (true)
		{
			// ���Ʊ�����������
			inputInt(cin, ret);

			if (ret >= 1 && ret <= 2)
			{
				break;
			}
			cout << "�����������������룡" << endl;
		}

		if (ret == 1)
		{
			// ͨ�����
			of.m_orderData[v[select - 1]]["status"] = "2";
		}
		else
		{
			// ��ͨ�����
			of.m_orderData[v[select - 1]]["status"] = "-1";
		}
		of.updateOrder();  // ����ԤԼ��¼
		cout << "�����ϣ�" << endl;
	}

	system("pause");
	system("cls");
}
