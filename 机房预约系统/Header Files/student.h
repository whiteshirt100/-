#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;
#include "Identity.h"
#include "computerRoom.h"
#include "globalFile.h"
#include "orderFile.h"
#include "function.h"

// ѧ�������
class Student : public Identity
{
public:

	// Ĭ�Ϲ���
	Student();

	// �вι��죨������������ѧ�š����룩
	Student(int id, string name, string password);

	// �˵�����
	virtual void openMenu();

	// ����ԤԼ
	void applyOrder();

	// �鿴����ԤԼ
	void showMyOrder();

	// �鿴����ԤԼ
	void showAllOrder();

	// ȡ��ԤԼ
	void cancelOrder();

	// ��ȡ������Ϣ
	void getCom();

	// ����ԤԼ��Ϣ
	void save(int date, int interval, int stuId, string stuName, int roomId, string status);

public:
	// ѧ��ѧ��
	int m_id;

	// ��������
	vector<ComputerRoom>vCom;
};
