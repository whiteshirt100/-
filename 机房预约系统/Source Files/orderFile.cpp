#include "orderFile.h"

// 构造函数
OrderFile::OrderFile()
{
	ifstream ifs;
	ifs.open(ORDER_FILE, ios::in);

	string date;		// 日期
	string interval;	// 时间段
	string stuId;		// 学号
	string stuName;		// 学生姓名
	string roomId;		// 机房号
	string status;		// 预约状态

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

		strSub(date, m);		// 截取日期
		strSub(interval, m);	// 截取时间段
		strSub(stuId, m);		// 截取学号
		strSub(stuName, m);		// 截取学生姓名
		strSub(roomId, m);		// 截取机房号
		strSub(status, m);		// 截取预约状态

		// 将小map容器放入到打的map容器中
		this->m_orderData.insert(make_pair(this->m_size, m));
		this->m_size++;
	}

	ifs.close();

	// 测试最大map容器
	/*for (map<int, map<string, string>>::iterator it = m_orderData.begin(); it != m_orderData.end(); it++)
	{
		cout << "条数为：" << it->first << " value = " << endl;
		for (map<string, string>::iterator mit = it->second.begin(); mit != it->second.end(); mit++)
		{
			cout << " key = " << mit->first << " value = " << mit->second << " ";
		}
		cout << endl;
	}*/
}

// 更新预约记录
void OrderFile::updateOrder()
{
	if (this->m_size == 0)
	{
		return;  // 预约记录0条，直接return
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

// 截取字符串函数
void OrderFile::strSub(string str, map<string, string>&m)
{
	//date:1
	string key;
	string value;

	int pos = str.find(":");	// 4
	if (pos != -1)
	{
		key = str.substr(0, pos);	// 截4个，所以第二个参数pos
		value = str.substr(pos + 1, str.size() - pos - 1);	// 截1个，size = 6  pos = 4  size - pos - 1

		//cout << "key = " << key << endl;
		//cout << "value = " << value << endl;

		m.insert(make_pair(key, value));
	}
}
