#include "student.h"

// Ĭ�Ϲ���
Student::Student()
{
}

// �вι���  ������������ѧ�š�����
Student::Student(int id, string name, string password)
{
	// ��ʼ������
	this->m_id = id;
	this->m_name = name;
	this->m_password = password;

	// ��ʼ�� ��ȡ������Ϣ
	this->getCom();
}

// �˵�����
void Student::openMenu()
{
	cout << "��ӭѧ������" << this->m_name << "��¼��" << endl;
	cout << "\t\t --------------------------------- " << endl;
	cout << "\t\t|                                 |" << endl;
	cout << "\t\t|          1������ԤԼ            |" << endl;
	cout << "\t\t|                                 |" << endl;
	cout << "\t\t|          2���鿴�ҵ�ԤԼ        |" << endl;
	cout << "\t\t|                                 |" << endl;
	cout << "\t\t|          3���鿴����ԤԼ        |" << endl;
	cout << "\t\t|                                 |" << endl;
	cout << "\t\t|          4��ȡ��ԤԼ            |" << endl;
	cout << "\t\t|                                 |" << endl;
	cout << "\t\t|          0��ע����¼            |" << endl;
	cout << "\t\t|                                 |" << endl;
	cout << "\t\t --------------------------------- " << endl;
	cout << "��ѡ�����Ĳ�����" << endl;
}

// ����ԤԼ
void Student::applyOrder()
{
	cout << "��������ʱ��Ϊ��һ������" << endl;
	cout << "����������ԤԼ��ʱ��Ϊ��" << endl;
	cout << "1����һ" << endl;
	cout << "2���ܶ�" << endl;
	cout << "3������" << endl;
	cout << "4������" << endl;
	cout << "5������" << endl;

	int date = 0;		// ����
	int interval = 0;	// ʱ���
	int room = 0;		// �������

	while (true)
	{
		// ���Ʊ�����������
		inputInt(cin, date);

		if (date >= 1 && date <= 5)
		{
			break;
		}
		cout << "���������������������룡" << endl;
	}

	cout << "����������ԤԼ��ʱ��Σ�" << endl;
	cout << "1������" << endl;
	cout << "2������" << endl;

	while (true)
	{
		// ���Ʊ�����������
		inputInt(cin, interval);

		if (interval >= 1 && interval <= 2)
		{
			break;
		}
		cout << "�����ʱ����������������룡" << endl;
	}

	cout << "��ѡ�������" << endl;
	for (int i = 0; i < (int)vCom.size(); i++)
	{
		cout << vCom[i].m_comId << "�Ż�������Ϊ��" << vCom[i].m_maxNum << endl;
	}
	while (true)
	{
		// ���Ʊ�����������
		inputInt(cin, room);

		if (room >= 1 && room <= 3)
		{
			break;
		}
		cout << "����Ļ������������������룡" << endl;
	}

	cout << "ԤԼ�ɹ��������..." << endl;

	// ����ԤԼ��Ϣ���ļ�
	this->save(date, interval, this->m_id, this->m_name, room, "1");

	system("pause");
	system("cls");

}

// data:1 interval:2 stuId:1 stuName:���� roomId:2 status:1
/*
map<string, string>			key���� ����    value���� ʵֵ
key    data		value	1
key    interval value	2
key    stuId	value	1
key    stuName	value	����
key    roomId	value	2
key    status	value	1

// ʹ������Ƕ������ ����������ά��ס
map<int, map<string, string>>    key ԤԼ��¼����  value ����һ����¼�е�������Ϣ
*/
// �鿴����ԤԼ
void Student::showMyOrder()
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
		// string ת int
		// string ���� .c_str() ת const char *
		// ����atoi(const char *) ת int
		if (this->m_id == atoi(of.m_orderData[i]["stuId"].c_str()))
		{
			cout << "ԤԼ���ڣ���" << of.m_orderData[i]["date"];
			cout << "  ʱ�Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����");
			cout << "  ������" << of.m_orderData[i]["roomId"];
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
	}

	system("pause");
	system("cls");
}

// �鿴����ԤԼ
void Student::showAllOrder()
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
		cout << "  ������" << of.m_orderData[i]["roomId"];
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

// ȡ��ԤԼ
void Student::cancelOrder()
{
	OrderFile of;
	if (of.m_size == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}

	cout << "����л�ԤԼ�ɹ��ļ�¼����ȡ����������Ҫȡ���ļ�¼��" << endl;
	vector<int>v;  // �������������е��±���
	int index = 1;
	for (int i = 0; i < of.m_size; i++)
	{
		// ���ж�������ѧ��
		if (this->m_id == atoi(of.m_orderData[i]["stuId"].c_str()))
		{
			// ��ɸѡ״̬ ����л�ԤԼ�ɹ�
			if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2")
			{
				v.push_back(i);
				cout << index++ << "��";  // ���û��ṩ���±���index��ʾ����ʵ���������±������� vector<int>v �洢
				cout << "ԤԼ���ڣ���" << of.m_orderData[i]["date"];
				cout << "  ʱ�Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����");
				cout << "  ������" << of.m_orderData[i]["roomId"];
				string status = "  ״̬��";
				// 1 �����   2 ԤԼ�ɹ�
				if (of.m_orderData[i]["status"] == "1")
				{
					status += "�����";
				}
				else if (of.m_orderData[i]["status"] == "2")
				{
					status += "ԤԼ�ɹ�";
				}
				cout << status << endl;
			}
		}
	}

	cout << "������ȡ���ļ�¼��0������" << endl;
	int select = 0;

	while (true)
	{
		// ���Ʊ�����������
		inputInt(cin, select);
		// �������뷶ΧΪ [0, v.size()] ֮��
		if (select >= 0 && select <= (int)v.size())
		{
			break;
		}
		cout << "������������������" << endl;
	}

	if (select != 0)
	{
		// ��¼����λ��
		of.m_orderData[v[select - 1]]["status"] = "0";
		of.updateOrder();
		cout << "��ȡ��ԤԼ" << endl;
	}

	system("pause");
	system("cls");
}


// ��ʼ�� ��ȡ������Ϣ
void Student::getCom()
{
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);

	if (!ifs.is_open())
	{
		cout << "�ļ���ʧ�ܣ�" << endl;
		return;
	}
	ComputerRoom com;
	while (ifs >> com.m_comId && ifs >> com.m_maxNum)
	{
		// ����ȡ������Ϣ���뵽 ������
		vCom.push_back(com);
	}

	ifs.close();
}

// ����ԤԼ��Ϣ
void Student::save(int date, int interval, int stuId, string stuName, int roomId, string status)
{
	ofstream ofs;
	ofs.open(ORDER_FILE, ios::app);

	ofs << "date:" << date << " ";
	ofs << "interval:" << interval << " ";
	ofs << "stuId:" << this->m_id << " ";
	ofs << "stuName:" << this->m_name << " ";
	ofs << "roomId:" << roomId << " ";
	ofs << "status:" << status << endl;  // ԤԼ״̬1(�����)

	ofs.close();
}
