#pragma once

#include <iostream>
using namespace std;
#include <string>

// ��ݳ������
class Identity
{
public:
	// �����˵� ���麯��
	virtual void openMenu() = 0;

public:
	string m_name;
	string m_password;
};
