#pragma once

#include <iostream>
#include <string>
#include <vector>
using namespace std;
#include "Identity.h"
#include "globalFile.h"
#include "orderFile.h"
#include "function.h"

// ��ʦ�����
class Teacher : public Identity
{
public:
	
	// Ĭ�Ϲ���
	Teacher();

	// �вι��죨ְ����š����������룩
	Teacher(int empId, string name, string password);

	// �˵�����
	virtual void openMenu();

	// �鿴����ԤԼ
	void showAllOrder();

	// ���ԤԼ
	void validOrder();

public:
	// ��ʦ���
	int m_empId;



};
