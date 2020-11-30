#pragma once

#include <iostream>
using namespace std;
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
#include "function.h"

#include <fstream>
#define FILENAME "empFile.txt"


class WorkerManager
{
public:
	// ���캯��
	WorkerManager();

	// ��������
	~WorkerManager();

	// չʾ�˵�
	void showMenu();

	// �˳�ϵͳ
	void exitSystem();

	// ����ְ��
	void addEmp();

	// �����ļ�
	void save();

	// ��ȡְ������
	int getNum();

	// ��ʼ��ְ��
	void initEmp();

	// ����
	void reset();

	// ��ʾְ��
	void showEmp();

	// ɾ��ְ��
	void delEmp();

	// ����ְ������ж�ְ���Ƿ���ڣ������ڷ���ְ���������е�λ�ã������ڷ���-1
	int isExist(int id);

	// �޸�ְ��
	void modEmp();

	// ����ְ��
	void findEmp();

	// ����ְ���������
	void sortEmp();

	// ����ļ�
	void cleanFile();


public:
	// ��¼�ļ��е���������
	int m_EmpNum;

	// Ա�������ָ��
	Worker** m_EmpArray;

	// ��־�ļ��Ƿ�Ϊ��
	bool m_FileEmpty;
};
