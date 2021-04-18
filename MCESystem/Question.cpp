#include"QuestionAndPaper.h"

Question::Question(string stem, string *option,int *answer, int type, int level) {
	this->stem = stem;
	for (int i = 0; i < 4; i++) {
		if (option != NULL)
			this->option[i] = option[i];
		if (answer != NULL)
			this->answer[i] = answer[i];
	}
	this->type = type;
	this->level = level;
}

Question& Question::operator=(const Question &source) {
	this->stem = source.stem;
	this->type = source.type;
	this->level = source.type;
	for (int i = 0; i < 4; i++) {
		this->option[i] = source.option[i];
		this->answer[i] = source.answer[i];
	}
	return *this;
}

void Question::setStem(string stem) {
	this->stem = stem;
}

void Question::setOption(string *option) {
	for (int i = 0; i++; i < 4) {
		this->option[i] = option[i];
	}
}

void Question::setAnswer(int *answer) {
	for (int i = 0; i++; i < 4) {
		this->answer[i] = answer[i];
	}
}

void Question::setType(int type) {
	this->type = type;
}

void Question::setLevel(int level) {
	this->level = level;
}

void Question::Add() {
	fstream file;		//指向题库文件
	int Qnum;	//题目总数

	//挑选打开文件
	switch (this->level)	
	{
	case 1:
		if (!this->type)
			file.open(_F_SQE, ios::in | ios::out);
		else
			file.open(_F_MQE, ios::in | ios::out);
		break;

	case 2:
		if (!this->type)
			file.open(_F_SQN, ios::in | ios::out);
		else
			file.open(_F_MQN, ios::in | ios::out);
		break;

	case 3:
		if (!this->type)
			file.open(_F_SQH, ios::in | ios::out);
		else
			file.open(_F_MQH, ios::in | ios::out);
		break;
	}

	//获得当前题目数
	file >> Qnum;
	file.get();

	//修改题目数
	file.seekp(ios::beg);
	file << (++Qnum) << endl;
	//添加题目
	file.seekp(0, ios::end);
	file << this->stem << '|'
		<< this->option[0] << '|' << this->option[1] << '|' << this->option[2] << '|' << this->option[3] << '|'
		<< this->answer[0] << this->answer[1] << this->answer[2] << this->answer[3]
		<< endl;
	file.close();
}

void Question::Delete(int order) {
	ifstream file_in;		
	ofstream file_out;
	int Qnum;	//题目总数
	char buf[1024][1024];

	//打开输入文件
	switch (this->level)
	{
	case 1:
		if (!this->type)
			file_in.open(_F_SQE);
		else
			file_in.open(_F_MQE);
		break;

	case 2:
		if (!this->type)
			file_in.open(_F_SQN);
		else
			file_in.open(_F_MQN);
		break;

	case 3:
		if (!this->type)
			file_in.open(_F_SQH);
		else
			file_in.open(_F_MQH);
		break;
	}

	//获得当前题目数
	file_in >> Qnum;
	file_in.get();

	//将题目全部读入
	for (int i = 0; i < Qnum; i++)
		file_in.getline(buf[i], sizeof(buf[i]));
	file_in.close();

	//重写
	switch (this->level)
	{
	case 1:
		if (!this->type)
			file_out.open(_F_SQE);
		else
			file_out.open(_F_MQE);
		break;

	case 2:
		if (!this->type)
			file_out.open(_F_SQN);
		else
			file_out.open(_F_MQN);
		break;

	case 3:
		if (!this->type)
			file_out.open(_F_SQH);
		else
			file_out.open(_F_MQH);
		break;
	}

	file_out << (--Qnum) << endl;
	for (int i = 0; i < Qnum + 1; i++) {
		if (i != order)
			file_out << buf[i] << endl;
	}
	file_out.close();
}