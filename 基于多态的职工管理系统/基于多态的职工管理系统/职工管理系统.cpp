
#include <iostream>
using namespace std;

#include "workerManager.h"
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

int main()
{
	WorkerManager wm;
	int choice;
	while (true)
	{
		// չʾ�˵�
		wm.showMenu();
reEnter_main_choice:
		cout << "����������ѡ��:" << endl;
		choice = 0;
		WorkerManager::isInt(cin, choice);

		while (choice < 0 || choice > 7)
		{
			cout << "��������ȷ������" << endl;
			goto reEnter_main_choice;
		}

		switch (choice)
		{
		case 0:  // �˳�ϵͳ
			wm.exitSystem();
			break;
		case 1:  // ���ְ��
			wm.addEmp();
			break;
		case 2:  // ��ʾְ��
			wm.showEmp();
			break;
		case 3:  // ɾ��ְ��
			wm.delEmp();
			break;		
		case 4:  // �޸�ְ��
			wm.modEmp();
			break;
		case 5:  // ����ְ��
			wm.findEmp();
			break;
		case 6:  // ����ְ��
			wm.sortEmp();
			break;
		case 7:  // ����ļ�
			wm.cleanFile();
			break;
		default:
			system("cls");  // ����
			break;
		}
	}

	system("pause");
	return 0;
}