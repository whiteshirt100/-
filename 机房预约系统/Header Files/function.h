#pragma once

#include <iostream>
using namespace std;

// ���Ʊ�����������
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
		cout << "��������Ϊ��������������������" << endl;
		in >> num;
		s = in.rdstate();
	}
}