#pragma once

#include <iostream>
using namespace std;

// 限制必须输入整数
static void inputInt(istream & in, int& num)
{
	int s;
	char str[200];
	in >> num;
	s = in.rdstate();
	while (s)
	{
		in.clear();
		in >> str;
		cout << "您的输入为非整数，请您重新输入" << endl;
		in >> num;
		s = in.rdstate();
	}
}