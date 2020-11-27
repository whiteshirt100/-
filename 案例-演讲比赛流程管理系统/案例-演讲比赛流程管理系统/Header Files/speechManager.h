#pragma once

#include <iostream>
using namespace std;

#include <vector>
#include <map>
#include <deque>
#include "speaker.h"
#include <algorithm>
#include <functional>
#include <numeric>
#include <string>
#include <fstream>

//const static string FILENAME = "speech.csv";
#define FILENAME "speech.csv"

// �ݽ�������
class SpeechManager
{
public:
	// ���캯��
	SpeechManager();
	
	// չʾ�˵�
	void showMenu();

	// �˳�
	void exitSystem();

	// ��ʼ����Ա����
	void initSpeech();

	// ����12��ѡ��
	void createSpeaker();

	// ��ʼ���� �����������̿��ƺ���
	void startSpeech();

	// ��ǩ
	void speechDraw();

	// ��ʼ����
	void speechContest();

	// ��ʾ�������
	void showScore();

	// �����¼
	void saveRecord();

	// ��ȡ��¼
	void loadRecord();

	// ��ʾ����÷�
	void showRecord();

	// ����
	void reset();

	// ��ռ�¼
	void clearRecord();

	// ���Ʊ�����������
	static void isInt(istream & in, int& num);

	// ��������
	~SpeechManager();



public:
	//��Ա����
	// �����һ�ֱ���ѡ�ֱ������
	vector<int>v1;

	// ��һ�ֽ���ѡ�ֱ������
	vector<int>v2;

	// ʤ��ǰ����ѡ�ֱ������
	vector<int>vVictory;

	// ��ű���Լ���Ӧ����ѡ������
	map<int, Speaker>m_speaker;

	// ��������
	int m_index;

	// �ж��ļ��Ƿ�Ϊ��
	bool fileIsEmpty;

	// �����¼
	map<int, vector<string>>m_record;
};
