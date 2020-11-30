#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
#include "Identity.h"
#include "student.h"
#include "teacher.h"
#include "computerRoom.h"
#include "globalFile.h"
#include "function.h"

// ����Ա�����
class Manager : public Identity
{
public:
	
	// Ĭ�Ϲ���
	Manager();

	// �вι��죨����Ա���������룩
	Manager(string name, string password);

	// ѡ��˵�
	virtual void openMenu();

	// ����˺�
	void addPerson();

	// �鿴�˺�
	void showPerson();

	// �鿴������Ϣ
	void showComputer();

	// ���ԤԼ��¼
	void cleanFile();

	// ��ʼ������
	void initVector();

	// ����ظ� ����������id���������ͣ� ����ֵ��true�������ظ���false����û���ظ���
	bool checkRepeat(int id, int type);

	// ��ȡ������Ϣ
	void getCom();

public:

	// ѧ������
	vector<Student>vStu;

	// ��ʦ����
	vector<Teacher>vTea;

	// ��������
	vector<ComputerRoom>vCom;
};
