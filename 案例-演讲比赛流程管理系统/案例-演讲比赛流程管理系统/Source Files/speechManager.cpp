#include "speechManager.h"

// 构造函数
SpeechManager::SpeechManager()
{
	this->reset();
}

// 展示菜单
void SpeechManager::showMenu()
{
	cout << "****************************************" << endl;
	cout << "*********** 欢迎参加演讲比赛 ***********" << endl;
	cout << "************ 1.开始演讲比赛 ************" << endl;
	cout << "************ 2.查看往届记录 ************" << endl;
	cout << "************ 3.清空比赛记录 ************" << endl;
	cout << "************ 0.退出比赛程序 ************" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}

// 退出
void SpeechManager::exitSystem()
{
	cout << "欢迎下次使用！" << endl;
	system("pause");
	exit(0);
}

// 初始化成员属性
void SpeechManager::initSpeech()
{
	// 容器都置空
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_speaker.clear();

	// 初始化比赛轮数
	this->m_index = 1;
	// 将记录的容器也清空
	this->m_record.clear();
}

// 创建12名选手
void SpeechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "选手";
		name += nameSeed[i];

		Speaker sp;
		sp.m_name = name;

		for (int j = 0; j < 2; j++)
		{
			sp.m_score[j] = 0;
		}

		// 12名选手编号
		this->v1.push_back(i + 10001);

		// 选手编号 以及对应的选手 放到map容器中
		this->m_speaker.insert(make_pair(i + 10001, sp));
	}
}

// 开始比赛 比赛整个流程控制函数
void SpeechManager::startSpeech()
{
	for (int i = 0; i < 2; i++)
	{
		// 第一轮开始比赛
		// 1、抽签
		this->speechDraw();
		// 2、比赛
		this->speechContest();
		// 3、显示晋级/最终结果
		this->showScore();

		// 第二轮开始比赛
		this->m_index++;
	}

	// 4、保存分数到文件中
	this->saveRecord();

	// 重置比赛
	this->reset();

	cout << "本届比赛结束！" << endl;
	system("pasue");
	system("cls");
}

// 抽签
void SpeechManager::speechDraw()
{
	cout << "第 << " << this->m_index << " >> 轮选手正在抽签" << endl;
	cout << "--------------------------" << endl;
	cout << "抽签结果如下：" << endl;

	if (this->m_index == 1)
	{
		// 第一轮比赛
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		// 第二轮比赛
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

// 开始比赛
void SpeechManager::speechContest()
{
	cout << "-------------------- 第 << " << this->m_index << " >> 轮比赛正式开始 --------------------" << endl;

	multimap<double, int, greater<double>>groupScore;  // 临时容器，保存key分数 value选手编号

	int num = 0;  // 记录人员数，6个为一组

	vector<int>vSrc;  // 比赛人员容器
	if (this->m_index == 1)
	{
		vSrc = v1;
	}
	else
	{
		vSrc = v2;
	}
	
	// 遍历所有参赛选手
	for (vector<int>::iterator it = vSrc.begin(); it != vSrc.end(); it++)
	{
		num++;;

		// 评委打分
		deque<double>d;

		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.0f;	// 600~1000
			//cout << score << " ";
			d.push_back(score);
		}

		sort(d.begin(), d.end(), greater<double>());		// 排序
		d.pop_front();	// 去除最高分
		d.pop_back();	// 去除最低分

		double sum = accumulate(d.begin(), d.end(), 0.0f);	// 获取总分
		double avg = sum / ((double)d.size());				// 获取平均分

		// 每个人平均分
		//cout << "编号：" << *it << " 选手：" << this->m_speaker[*it].m_name << " 获取平均分为：" << avg << endl;  // 打印分数
		this->m_speaker[*it].m_score[this->m_index - 1] = avg;

		// 6个人一组，用临时容器保存
		groupScore.insert(make_pair(avg, *it));
		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << "小组比赛名次：" << endl;
			for (multimap<double, int>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "编号：" << it->second 
					<< " 姓名：" << this->m_speaker[it->second].m_name 
					<< " 成绩：" << this->m_speaker[it->second].m_score[this->m_index - 1] << endl;
			}

			int count = 0;
			// 取前三名
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
	cout << "------------- 第 << " << this->m_index << " >> 轮比赛完毕 --------------" << endl;
	system("pause");
}

// 显示比赛结果
void SpeechManager::showScore()
{
	cout << "---------------第 << " << this->m_index << " >> 轮晋级选手如下：" << endl;
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
		cout << "选手编号：" << *it 
			<< " 姓名：" << this->m_speaker[*it].m_name 
			<< " 得分：" << m_speaker[*it].m_score[this->m_index - 1] << endl;
	}
	cout << endl;

	system("pause");
	system("cls");
	this->showMenu();
}

// 保存记录
void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out | ios::app);  // 用输出的方式打开，写文件

	// 将每个人的数据写入到文件中
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << "," << m_speaker[*it].m_score[1] << ",";
	}
	ofs << endl;

	// 关闭文件
	ofs.close();

	cout << "记录已经保存" << endl;

	// 更改文件不为空的状态
	this->fileIsEmpty = false;
}

// 读取记录
void SpeechManager::loadRecord()
{
	ifstream ifs(FILENAME, ios::in);  // 读文件

	// 文件不存在情况
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		//cout << "文件不存在！" << endl;
		ifs.close();
		return;
	}

	// 文件清空情况
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		this->fileIsEmpty = true;
		//cout << "文件为空！" << endl;
		ifs.close();
		return;
	}

	// 文件不为空
	this->fileIsEmpty = false;

	ifs.putback(ch);  // 将上面读取的单个字符 放回来

	string data;
	int index = 0;
	while (ifs >> data)
	{
		//cout << data << endl;
		//10002, 86.675, 10009, 81.3, 10007, 78.55,

		vector<string>v;	// 存放6个string字符串
		int pos = -1;		// 查到","位置的变量
		int start = 0;

		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				// 没有找到情况
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
	//	cout << it->first << "冠军编号：" << it->second[0] << "成绩：" << it->second[1] << endl;
	//}
}

// 显示往届得分
void SpeechManager::showRecord()
{
	if (this->fileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_record.size(); i++)
		{
			cout << "第" << i + 1 << "届 "
			<< "冠军编号：" << this->m_record[i][0] << " 得分：" << this->m_record[i][1] << " "
			<< "亚军编号：" << this->m_record[i][2] << " 得分：" << this->m_record[i][3] << " "
			<< "季军编号：" << this->m_record[i][4] << " 得分：" << this->m_record[i][5] << " " << endl;
		}
	}
	
	system("pause");
	system("cls");
}

// 重置
void SpeechManager::reset()
{
	// 初始化属性
	this->initSpeech();

	// 创建选手
	this->createSpeaker();

	// 获取往届记录
	this->loadRecord();
}

// 清空记录
void SpeechManager::clearRecord()
{
	cout << "是否确认清空文件？" << endl;
	cout << "1、是" << endl;
	cout << "2、否" << endl;

	int select = 0;

	while (true)
	{
		// 限制必须输入整数
		inputInt(cin, select);

		if (select >= 1 && select <= 2)
		{
			break;
		}
		cout << "输入有误，请重新输入" << endl;
	}

	if (select == 1)
	{
		// 确认清空
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();
		this->reset();
		cout << "清空成功！" << endl;
	}

	system("pause");
	system("cls");
}

// 析构函数
SpeechManager::~SpeechManager()
{

}


