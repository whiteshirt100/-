#include "orderFile.h"

// ���캯��
OrderFile::OrderFile()
{
	ifstream ifs;
	ifs.open(ORDER_FILE, ios::in);

	string date;		// ����
	string interval;	// ʱ���
	string stuId;		// ѧ��
	string stuName;		// ѧ������
	string roomId;		// ������
	string status;		// ԤԼ״̬

	this->m_size = 0;

	while (ifs >> date && ifs >> interval && ifs >> stuId && ifs >> stuName && ifs >> roomId && ifs >> status)
	{
		/*cout << date << endl;
		cout << interval << endl;
		cout << stuId << endl;
		cout << stuName << endl;
		cout << roomId << endl;
		cout << status << endl;
		cout << endl;*/
		map<string, string>m;

		strSub(date, m);		// ��ȡ����
		strSub(interval, m);	// ��ȡʱ���
		strSub(stuId, m);		// ��ȡѧ��
		strSub(stuName, m);		// ��ȡѧ������
		strSub(roomId, m);		// ��ȡ������
		strSub(status, m);		// ��ȡԤԼ״̬

		// ��Сmap�������뵽���map������
		this->m_orderData.insert(make_pair(this->m_size, m));
		this->m_size++;
	}

	ifs.close();

	// �������map����
	/*for (map<int, map<string, string>>::iterator it = m_orderData.begin(); it != m_orderData.end(); it++)
	{
		cout << "����Ϊ��" << it->first << " value = " << endl;
		for (map<string, string>::iterator mit = it->second.begin(); mit != it->second.end(); mit++)
		{
			cout << " key = " << mit->first << " value = " << mit->second << " ";
		}
		cout << endl;
	}*/
}

// ����ԤԼ��¼
void OrderFile::updateOrder()
{
	if (this->m_size == 0)
	{
		return;  // ԤԼ��¼0����ֱ��return
	}

	ofstream ofs;
	ofs.open(ORDER_FILE, ios::out | ios::trunc);
	for (int i = 0; i < this->m_size; i++)
	{
		ofs << "date:" << this->m_orderData[i]["date"] << " ";
		ofs << "interval:" << this->m_orderData[i]["interval"] << " ";
		ofs << "stuId:" << this->m_orderData[i]["stuId"] << " ";
		ofs << "stuName:" << this->m_orderData[i]["stuName"] << " ";
		ofs << "roomId:" << this->m_orderData[i]["roomId"] << " ";
		ofs << "status:" << this->m_orderData[i]["status"] << " ";
	}

	ofs.close();
}

// ��ȡ�ַ�������
void OrderFile::strSub(string str, map<string, string>&m)
{
	//date:1
	string key;
	string value;

	int pos = str.find(":");	// 4
	if (pos != -1)
	{
		key = str.substr(0, pos);	// ��4�������Եڶ�������pos
		value = str.substr(pos + 1, str.size() - pos - 1);	// ��1����size = 6  pos = 4  size - pos - 1

		//cout << "key = " << key << endl;
		//cout << "value = " << value << endl;

		m.insert(make_pair(key, value));
	}
}
