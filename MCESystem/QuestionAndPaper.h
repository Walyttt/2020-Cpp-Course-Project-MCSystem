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
	Question& operator=(const Question &source);	//赋值构造
	void setStem(string stem);
	void setOption(string *option);
	void setAnswer(int *answer);
	void setType(int type);
	void setLevel(int level);
	void Add();			//添加题目到题库
	void Delete(int);	//参数为题目序号

	
private:
	string stem;
	string option[4];
	int answer[4];
	int type;
	int level;			//type:0为单选，1为多选  level：1，2，3依次为简单，普通，困难
};



class Paper
{
public:
	Paper(char *name = NULL, char *path_to_paper = NULL, char *path_to_log = NULL);
	Paper& operator=(const Paper &source);				//赋值构造
	~Paper();											//析构
	string GetName();									//获取试卷名
	string GetStem(int counter);						//获取题干
	string GetOption(int counter, int option);			//获取选项
	int GetAnswer(int counter, int option);				//获取答案
	int GetQcount();									//获取总题数
	int GetSinCount();									//获取单选题数
	int GetTotalScore();								//获取试卷总成绩
	void GetLogPath(char* path);						//获取记录路径字符串指针
	int Check(int** Stu_answer, int* checkvector);						//批改试卷,参数为学生答案

private:
	string name;
	string path_to_paper;
	string path_to_log;

	int total_score;		//总分值
	int amount_single, amount_mul;	//单选题数目和多选题数目
	Question *question;				//题目数组
};
