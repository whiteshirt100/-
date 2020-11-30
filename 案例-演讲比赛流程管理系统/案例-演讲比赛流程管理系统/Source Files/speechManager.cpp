#include "speechManager.h"

// ���캯��
SpeechManager::SpeechManager()
{
	this->reset();
}

// չʾ�˵�
void SpeechManager::showMenu()
{
	cout << "****************************************" << endl;
	cout << "*********** ��ӭ�μ��ݽ����� ***********" << endl;
	cout << "************ 1.��ʼ�ݽ����� ************" << endl;
	cout << "************ 2.�鿴�����¼ ************" << endl;
	cout << "************ 3.��ձ�����¼ ************" << endl;
	cout << "************ 0.�˳��������� ************" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}

// �˳�
void SpeechManager::exitSystem()
{
	cout << "��ӭ�´�ʹ�ã�" << endl;
	system("pause");
	exit(0);
}

// ��ʼ����Ա����
void SpeechManager::initSpeech()
{
	// �������ÿ�
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_speaker.clear();

	// ��ʼ����������
	this->m_index = 1;
	// ����¼������Ҳ���
	this->m_record.clear();
}

// ����12��ѡ��
void SpeechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "ѡ��";
		name += nameSeed[i];

		Speaker sp;
		sp.m_name = name;

		for (int j = 0; j < 2; j++)
		{
			sp.m_score[j] = 0;
		}

		// 12��ѡ�ֱ��
		this->v1.push_back(i + 10001);

		// ѡ�ֱ�� �Լ���Ӧ��ѡ�� �ŵ�map������
		this->m_speaker.insert(make_pair(i + 10001, sp));
	}
}

// ��ʼ���� �����������̿��ƺ���
void SpeechManager::startSpeech()
{
	for (int i = 0; i < 2; i++)
	{
		// ��һ�ֿ�ʼ����
		// 1����ǩ
		this->speechDraw();
		// 2������
		this->speechContest();
		// 3����ʾ����/���ս��
		this->showScore();

		// �ڶ��ֿ�ʼ����
		this->m_index++;
	}

	// 4������������ļ���
	this->saveRecord();

	// ���ñ���
	this->reset();

	cout << "�������������" << endl;
	system("pasue");
	system("cls");
}

// ��ǩ
void SpeechManager::speechDraw()
{
	cout << "�� << " << this->m_index << " >> ��ѡ�����ڳ�ǩ" << endl;
	cout << "--------------------------" << endl;
	cout << "��ǩ������£�" << endl;

	if (this->m_index == 1)
	{
		// ��һ�ֱ���
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		// �ڶ��ֱ���
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	system("pause");
	cout << endl;
}

// ��ʼ����
void SpeechManager::speechContest()
{
	cout << "-------------------- �� << " << this->m_index << " >> �ֱ�����ʽ��ʼ --------------------" << endl;

	multimap<double, int, greater<double>>groupScore;  // ��ʱ����������key���� valueѡ�ֱ��

	int num = 0;  // ��¼��Ա����6��Ϊһ��

	vector<int>vSrc;  // ������Ա����
	if (this->m_index == 1)
	{
		vSrc = v1;
	}
	else
	{
		vSrc = v2;
	}
	
	// �������в���ѡ��
	for (vector<int>::iterator it = vSrc.begin(); it != vSrc.end(); it++)
	{
		num++;;

		// ��ί���
		deque<double>d;

		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.0f;	// 600~1000
			//cout << score << " ";
			d.push_back(score);
		}

		sort(d.begin(), d.end(), greater<double>());		// ����
		d.pop_front();	// ȥ����߷�
		d.pop_back();	// ȥ����ͷ�

		double sum = accumulate(d.begin(), d.end(), 0.0f);	// ��ȡ�ܷ�
		double avg = sum / ((double)d.size());				// ��ȡƽ����

		// ÿ����ƽ����
		//cout << "��ţ�" << *it << " ѡ�֣�" << this->m_speaker[*it].m_name << " ��ȡƽ����Ϊ��" << avg << endl;  // ��ӡ����
		this->m_speaker[*it].m_score[this->m_index - 1] = avg;

		// 6����һ�飬����ʱ��������
		groupScore.insert(make_pair(avg, *it));
		if (num % 6 == 0)
		{
			cout << "��" << num / 6 << "С��������Σ�" << endl;
			for (multimap<double, int>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "��ţ�" << it->second 
					<< " ������" << this->m_speaker[it->second].m_name 
					<< " �ɼ���" << this->m_speaker[it->second].m_score[this->m_index - 1] << endl;
			}

			int count = 0;
			// ȡǰ����
			for (multimap<double, int>::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; it++, count++)
			{
				if (this->m_index == 1)
				{
					v2.push_back((*it).second);
				}
				else
				{
					vVictory.push_back((*it).second);
				}
			}
			groupScore.clear();
			cout << endl;
		}
	}
	cout << "------------- �� << " << this->m_index << " >> �ֱ������ --------------" << endl;
	system("pause");
}

// ��ʾ�������
void SpeechManager::showScore()
{
	cout << "---------------�� << " << this->m_index << " >> �ֽ���ѡ�����£�" << endl;
	vector<int>v;
	if (this->m_index == 1)
	{
		v = v2;
	}
	else
	{
		v = vVictory;
	}

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "ѡ�ֱ�ţ�" << *it 
			<< " ������" << this->m_speaker[*it].m_name 
			<< " �÷֣�" << m_speaker[*it].m_score[this->m_index - 1] << endl;
	}
	cout << endl;

	system("pause");
	system("cls");
	this->showMenu();
}

// �����¼
void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out | ios::app);  // ������ķ�ʽ�򿪣�д�ļ�

	// ��ÿ���˵�����д�뵽�ļ���
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << "," << m_speaker[*it].m_score[1] << ",";
	}
	ofs << endl;

	// �ر��ļ�
	ofs.close();

	cout << "��¼�Ѿ�����" << endl;

	// �����ļ���Ϊ�յ�״̬
	this->fileIsEmpty = false;
}

// ��ȡ��¼
void SpeechManager::loadRecord()
{
	ifstream ifs(FILENAME, ios::in);  // ���ļ�

	// �ļ����������
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		//cout << "�ļ������ڣ�" << endl;
		ifs.close();
		return;
	}

	// �ļ�������
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		this->fileIsEmpty = true;
		//cout << "�ļ�Ϊ�գ�" << endl;
		ifs.close();
		return;
	}

	// �ļ���Ϊ��
	this->fileIsEmpty = false;

	ifs.putback(ch);  // �������ȡ�ĵ����ַ� �Ż���

	string data;
	int index = 0;
	while (ifs >> data)
	{
		//cout << data << endl;
		//10002, 86.675, 10009, 81.3, 10007, 78.55,

		vector<string>v;	// ���6��string�ַ���
		int pos = -1;		// �鵽","λ�õı���
		int start = 0;

		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				// û���ҵ����
				break;
			}
			string temp = data.substr(start, pos - start);
			//cout << temp << endl;
			v.push_back(temp);

			start = pos + 1;
		}

		m_record.insert(make_pair(index, v));
		index++;
	}

	ifs.close();
	//for (map<int, vector<string>>::iterator it = m_record.begin(); it != m_record.end(); it++)
	//{
	//	cout << it->first << "�ھ���ţ�" << it->second[0] << "�ɼ���" << it->second[1] << endl;
	//}
}

// ��ʾ����÷�
void SpeechManager::showRecord()
{
	if (this->fileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_record.size(); i++)
		{
			cout << "��" << i + 1 << "�� "
			<< "�ھ���ţ�" << this->m_record[i][0] << " �÷֣�" << this->m_record[i][1] << " "
			<< "�Ǿ���ţ�" << this->m_record[i][2] << " �÷֣�" << this->m_record[i][3] << " "
			<< "������ţ�" << this->m_record[i][4] << " �÷֣�" << this->m_record[i][5] << " " << endl;
		}
	}
	
	system("pause");
	system("cls");
}

// ����
void SpeechManager::reset()
{
	// ��ʼ������
	this->initSpeech();

	// ����ѡ��
	this->createSpeaker();

	// ��ȡ�����¼
	this->loadRecord();
}

// ��ռ�¼
void SpeechManager::clearRecord()
{
	cout << "�Ƿ�ȷ������ļ���" << endl;
	cout << "1����" << endl;
	cout << "2����" << endl;

	int select = 0;

	while (true)
	{
		// ���Ʊ�����������
		inputInt(cin, select);

		if (select >= 1 && select <= 2)
		{
			break;
		}
		cout << "������������������" << endl;
	}

	if (select == 1)
	{
		// ȷ�����
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();
		this->reset();
		cout << "��ճɹ���" << endl;
	}

	system("pause");
	system("cls");
}

// ��������
SpeechManager::~SpeechManager()
{

}


