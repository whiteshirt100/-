#pragma once

#include <iostream>
using namespace std;
#include <string>

// 身份抽象基类
class Identity
{
public:
	// 操作菜单 纯虚函数
	virtual void openMenu() = 0;

public:
	string m_name;
	string m_password;
};
