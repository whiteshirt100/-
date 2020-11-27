
#include <iostream>
using namespace std;
#include "speechManager.h"
#include <string>
#include <ctime>
/*
1 ��������

* 12���˲μӣ����������֣���̭��������
* ��ţ���10001 ~ 10012
* ���������ÿ��6��
* ��һ�ַ����飬����ǩ˳���ݽ�
* ʮ����ί��֣�ȥ����ߺ���ͣ���ƽ��
* С���ݽ������̭��������������λѡ�֣�ǰ��������������һ��
* �ڶ���Ϊ������ǰ����ʤ��
* ÿ�ֱ���������ʾ����ѡ�ֵ���Ϣ


2 ������

* ��ʼ�ݽ����������������������̣�ÿ�������׶���Ҫ���û�һ����ʾ���û���������������һ���׶�
* �鿴�����¼���鿴֮ǰ������ǰ���������ÿ�α��������¼���ļ��У��ļ���.csv��׺������
* ��ձ�����¼�����ļ����������
* �˳��������򣺿����˳���ǰ����
*/

int main()
{
	// ���������
	srand((unsigned int)time(NULL));
	
	// �������������
	SpeechManager sm;

	// ���Դ���
	/*for (map<int, Speaker>::iterator it = sm.m_speaker.begin(); it != sm.m_speaker.end(); it ++)
	{
		cout << "ѡ�ֱ�ţ�" << it->first << " ������" << it->second.m_name << " �ɼ���" << it->second.m_score[0] << endl;
	}*/

	int choice = 0;

	while (true)
	{
		sm.showMenu();

		cout << "����������ѡ��" << endl;

reEnter_main_choice:
		choice = 0;
		// ���Ʊ�����������
		SpeechManager::isInt(cin, choice);

		while (choice >3 || choice <0)
		{
			cout << "��������ȷ������" << endl;
			goto reEnter_main_choice;
		}

		switch (choice)
		{
		case 1:
			sm.startSpeech();
			break;
		case 2:
			sm.showRecord();
			break;
		case 3:
			sm.clearRecord();
			break;
		case 0:
			sm.exitSystem();
			break;
		default:
			system("cls");
			break;
		}
	}
	cout << "hello..." << endl;
	system("pause");
	return 0;
}