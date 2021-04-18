#pragma once

#include<list>
#include<fstream>
#include<iostream>
#include<string>
#include<direct.h>
#include<io.h>

#define _F_SQE "D:\\TestSystem\\QLib\\Single_easy.txt"
#define _F_SQN "D:\\TestSystem\\QLib\\Single_normal.txt"
#define _F_SQH "D:\\TestSystem\\QLib\\Single_hard.txt"
#define _F_MQE "D:\\TestSystem\\QLib\\Multiple_easy.txt"
#define _F_MQN "D:\\TestSystem\\QLib\\Multiple_normal.txt"
#define _F_MQH "D:\\TestSystem\\QLib\\Multiple_hard.txt"

#define Sin_score 4
#define Mul_score 6

using namespace std;

class Question
{
	friend class Paper;

public:
	Question(string stem = "", string *option = NULL, int *answer = NULL, int type = -1, int level = -1);
	Question& operator=(const Question &source);	//��ֵ����
	void setStem(string stem);
	void setOption(string *option);
	void setAnswer(int *answer);
	void setType(int type);
	void setLevel(int level);
	void Add();			//�����Ŀ�����
	void Delete(int);	//����Ϊ��Ŀ���

	
private:
	string stem;
	string option[4];
	int answer[4];
	int type;
	int level;			//type:0Ϊ��ѡ��1Ϊ��ѡ  level��1��2��3����Ϊ�򵥣���ͨ������
};



class Paper
{
public:
	Paper(char *name = NULL, char *path_to_paper = NULL, char *path_to_log = NULL);
	Paper& operator=(const Paper &source);				//��ֵ����
	~Paper();											//����
	string GetName();									//��ȡ�Ծ���
	string GetStem(int counter);						//��ȡ���
	string GetOption(int counter, int option);			//��ȡѡ��
	int GetAnswer(int counter, int option);				//��ȡ��
	int GetQcount();									//��ȡ������
	int GetSinCount();									//��ȡ��ѡ����
	int GetTotalScore();								//��ȡ�Ծ��ܳɼ�
	void GetLogPath(char* path);						//��ȡ��¼·���ַ���ָ��
	int Check(int** Stu_answer, int* checkvector);						//�����Ծ�,����Ϊѧ����

private:
	string name;
	string path_to_paper;
	string path_to_log;

	int total_score;		//�ܷ�ֵ
	int amount_single, amount_mul;	//��ѡ����Ŀ�Ͷ�ѡ����Ŀ
	Question *question;				//��Ŀ����
};
