#pragma once

#include <iostream>
#include <map>
#include <string>
#include <fstream>
using namespace std;
#include "globalFile.h"

class OrderFile
{
public:

	// ���캯��
	OrderFile();

	// ����ԤԼ��¼
	void updateOrder();

	// ��ȡ�ַ�������
	void strSub(string str, map<string, string>&m);

public:

	// ��¼ԤԼ����
	int m_size;

	// ��¼����ԤԼ��Ϣ������  key��¼����  value�����¼��ֵ����Ϣ
	map<int, map<string, string>>m_orderData;


};

