#include "QuestionAndPaper.h"

Paper::Paper(char *name, char *path_to_paper, char *path_to_log) {
	if (path_to_paper) {
		string name_temp(name), path_to_paper_temp(path_to_paper), path_to_log_temp(path_to_log);
		this->name = name_temp;
		this->path_to_paper = path_to_paper_temp;
		this->path_to_log = path_to_log_temp;
	

		char buf[1024];
		ifstream file;

		//打开试卷文件
		file.open(path_to_paper);
		file.getline(buf, sizeof(buf));

		//获取单选数与多选数
		file >> this->amount_single >> this->amount_mul;
		file.get();

		//总分值
		this->total_score = this->amount_single*Sin_score + this->amount_mul*Mul_score;

		//开始读取题目
		this->question = new Question[this->amount_single + this->amount_mul];
		for (int i = 0; i < this->amount_single + this->amount_mul; i++) {
			file.getline(buf, sizeof(buf));

			this->question[i].stem = strtok(buf, "|");//开始切割
			this->question[i].option[0] = strtok(NULL, "|");
			this->question[i].option[1] = strtok(NULL, "|");
			this->question[i].option[2] = strtok(NULL, "|");
			this->question[i].option[3] = strtok(NULL, "|");

			char *answer = strtok(NULL, "|");
			char *type = strtok(NULL, "|");

			for (int j = 0; j < 4; j++) {
				if (answer[j] == '1')
					this->question[i].answer[j] = 1;
				else
					this->question[i].answer[j] = 0;
			}
			if (type[0] == 'S')
				this->question[i].type = 0;
			else
				this->question[i].type = 1;

		}
		file.close();
	}

}

Paper& Paper::operator=(const Paper &source) {
	this->name = source.name;
	this->path_to_paper = source.path_to_paper;
	this->path_to_log = source.path_to_log;
	this->total_score = source.total_score;
	this->amount_single = source.amount_single;
	this->amount_mul = source.amount_mul;
	
	this->question = new Question[this->amount_single + this->amount_mul];
	for (int i = 0; i < this->amount_single + this->amount_mul; i++)
		this->question[i] = source.question[i];

	return *this;
}


Paper::~Paper() {
	delete [](this->question);
}

string Paper::GetName() {
	return this->name;
}

string Paper::GetStem(int counter) {
	return this->question[counter - 1].stem;
}

string Paper::GetOption(int counter, int option) {
	return this->question[counter - 1].option[option - 1];
}

int Paper::GetAnswer(int counter, int option) {
	return this->question[counter - 1].answer[option - 1];
}

int Paper::GetQcount() {
	return this->amount_single + this->amount_mul;
}

int Paper::GetSinCount() {
	return this->amount_single;
}

int Paper::GetTotalScore() {
	return this->total_score;
}

void Paper::GetLogPath(char* path) {
	strcpy(path, this->path_to_log.c_str());
}

int Paper::Check(int** Stu_answer, int* checkvector) {
	int Stu_score = 0;
	//单选题判题
	for (int i = 0; i < this->amount_single; i++) {
		if (Stu_answer[i][0] == this->question[i].answer[0] &&
			Stu_answer[i][1] == this->question[i].answer[1] &&
			Stu_answer[i][2] == this->question[i].answer[2] &&
			Stu_answer[i][3] == this->question[i].answer[3]) {
			Stu_score += Sin_score;
			checkvector[i] = 1;
		}
		else
			checkvector[i] = 0;
	}
	//多选题判题
	for (int i = this->amount_single; i < this->GetQcount(); i++) {
		if (Stu_answer[i][0] == this->question[i].answer[0] &&
			Stu_answer[i][1] == this->question[i].answer[1] &&
			Stu_answer[i][2] == this->question[i].answer[2] &&
			Stu_answer[i][3] == this->question[i].answer[3]) {
			Stu_score += Mul_score;
			checkvector[i] = 1;
		}
		else
			checkvector[i] = 0;
	}
	return Stu_score;
}