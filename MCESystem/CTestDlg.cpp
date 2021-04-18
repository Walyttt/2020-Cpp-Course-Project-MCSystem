// CTestDlg.cpp: 实现文件
//

#include "pch.h"
#include "MCESystem.h"
#include "CTestDlg.h"
#include "afxdialogex.h"


// CTestDlg 对话框

IMPLEMENT_DYNAMIC(CTestDlg, CDialogEx)

CTestDlg::CTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TestDlg, pParent)
{

}

CTestDlg::~CTestDlg()
{
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_StemTEXT, Text_stem);
	DDX_Control(pDX, IDC_CHECK1, Check_option1);
	DDX_Control(pDX, IDC_CHECK2, Check_option2);
	DDX_Control(pDX, IDC_CHECK3, Check_option3);
	DDX_Control(pDX, IDC_CHECK4, Check_option4);
	DDX_Control(pDX, IDC_BUTTON1, Button_previous);
	DDX_Control(pDX, IDC_BUTTON2, Button_next);
	DDX_Control(pDX, IDC_PROMPT, Text_prompt);

	//申请答案空间
	Stu_answer = new int*[this->paper.GetQcount()];
	for (int i = 0; i < this->paper.GetQcount(); i++) {
		Stu_answer[i] = new int[4];
		for (int j = 0; j < 4; j++)
			Stu_answer[i][j] = 0;
	}



	//第一题
	this->counter = 1;
	Button_previous.EnableWindow(FALSE);	//在第一题，前一题按钮失活

	Text_stem.SetWindowTextW(CA2T(this->paper.GetStem(1).c_str()));		//设置题干
	Check_option1.SetWindowTextW(CA2T(this->paper.GetOption(1, 1).c_str()));
	Check_option2.SetWindowTextW(CA2T(this->paper.GetOption(1, 2).c_str()));
	Check_option3.SetWindowTextW(CA2T(this->paper.GetOption(1, 3).c_str()));
	Check_option4.SetWindowTextW(CA2T(this->paper.GetOption(1, 4).c_str()));	//设置答案

	//单选多选提示
	if (this->paper.GetSinCount() != 0)
		Text_prompt.SetWindowTextW(TEXT("(单选)"));
	else
		Text_prompt.SetWindowTextW(TEXT("(多选)"));
}


BEGIN_MESSAGE_MAP(CTestDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CTestDlg::Next)
	ON_BN_CLICKED(IDC_BUTTON1, &CTestDlg::Previous)
	ON_BN_CLICKED(IDC_CHECK1, &CTestDlg::SelectOptionA)
	ON_BN_CLICKED(IDC_CHECK2, &CTestDlg::SelectOptionB)
	ON_BN_CLICKED(IDC_CHECK3, &CTestDlg::SelectOptionC)
	ON_BN_CLICKED(IDC_CHECK4, &CTestDlg::SelectOptionD)
END_MESSAGE_MAP()


// CTestDlg 消息处理程序


void CTestDlg::Next()
{
	// TODO: 在此添加控件通知处理程序代码

	//若不是最后一题
	if (this->counter < this->paper.GetQcount()) {

		//先记录答案
		if (Check_option1.GetCheck())
			this->Stu_answer[this->counter - 1][0] = 1;
		else
			this->Stu_answer[this->counter - 1][0] = 0;
		if (Check_option2.GetCheck())
			this->Stu_answer[this->counter - 1][1] = 1;
		else
			this->Stu_answer[this->counter - 1][1] = 0;
		if (Check_option3.GetCheck())
			this->Stu_answer[this->counter - 1][2] = 1;
		else
			this->Stu_answer[this->counter - 1][2] = 0;
		if (Check_option4.GetCheck())
			this->Stu_answer[this->counter - 1][3] = 1;
		else
			this->Stu_answer[this->counter - 1][3] = 0;

		//跳转到下一题
		this->counter++;
		Text_stem.SetWindowTextW(CA2T(this->paper.GetStem(this->counter).c_str()));		//设置题干
		Check_option1.SetWindowTextW(CA2T(this->paper.GetOption(this->counter, 1).c_str()));
		Check_option2.SetWindowTextW(CA2T(this->paper.GetOption(this->counter, 2).c_str()));
		Check_option3.SetWindowTextW(CA2T(this->paper.GetOption(this->counter, 3).c_str()));
		Check_option4.SetWindowTextW(CA2T(this->paper.GetOption(this->counter, 4).c_str()));	//设置答案

		//单选多选提示
		if (this->counter == this->paper.GetSinCount() + 1)
			Text_prompt.SetWindowTextW(TEXT("(多选)"));

		//显示目前所选择答案
		if (Stu_answer[this->counter - 1][0])
			Check_option1.SetCheck(BST_CHECKED);
		else
			Check_option1.SetCheck(BST_UNCHECKED);
		if (Stu_answer[this->counter - 1][1])
			Check_option2.SetCheck(BST_CHECKED);
		else
			Check_option2.SetCheck(BST_UNCHECKED);
		if (Stu_answer[this->counter - 1][2])
			Check_option3.SetCheck(BST_CHECKED);
		else
			Check_option3.SetCheck(BST_UNCHECKED);
		if (Stu_answer[this->counter - 1][3])
			Check_option4.SetCheck(BST_CHECKED);
		else
			Check_option4.SetCheck(BST_UNCHECKED);

		//激活上一题按钮
		Button_previous.EnableWindow(TRUE);

		//若下一题即为最后一题，按钮文本替换为提交
		if (counter == this->paper.GetQcount())
			Button_next.SetWindowTextW(TEXT("提交"));
	}

	//若该题即为最后一题
	else {
		if (MessageBox(TEXT("确认提交？"), TEXT("提示"), MB_OKCANCEL) == IDOK) {	//确认提示
			//先记录答案
			if (Check_option1.GetCheck())
				this->Stu_answer[this->counter - 1][0] = 1;
			else
				this->Stu_answer[this->counter - 1][0] = 0;
			if (Check_option2.GetCheck())
				this->Stu_answer[this->counter - 1][1] = 1;
			else
				this->Stu_answer[this->counter - 1][1] = 0;
			if (Check_option3.GetCheck())
				this->Stu_answer[this->counter - 1][2] = 1;
			else
				this->Stu_answer[this->counter - 1][2] = 0;
			if (Check_option4.GetCheck())
				this->Stu_answer[this->counter - 1][3] = 1;
			else
				this->Stu_answer[this->counter - 1][3] = 0;

			//获得分数
			int* checkvector;
			checkvector = new int[this->paper.GetQcount()];
			int Stu_Score = this->paper.Check(this->Stu_answer,checkvector);

			//教师处记录
			fstream file;
			char path[1024];
			int num;

			this->paper.GetLogPath(path);
			file.open(path, ios::in | ios::out);
			file >> num;
			file.get();

			file.seekp(ios::beg);
			file << (++num) << endl;
			file.seekp(0, ios::end);
			file << this->stu.name << '|' << Stu_Score<< endl;
			file.close();

			//学生处记录
			strcpy(path, _D_Student);
			strcat(path, this->stu.id.c_str());
			strcat(path, "//log.txt");

			file.open(path, ios::in | ios::out);
			file >> num;
			file.get();

			file.seekp(ios::beg);
			file << (++num) << endl;
			file.seekp(0, ios::end);
			file << this->paper.GetName() << '|' << Stu_Score << endl;
			file.close();

			//将错题添入错题本
			strcpy(path, _D_Student);
			strcat(path, this->stu.id.c_str());
			strcat(path, "//WrongCollection.txt");

			file.open(path, ios::in | ios::out);
			file >> num;
			file.get();

			file.seekp(0, ios::end);
			for (int i = 1; i <= this->paper.GetQcount(); i++) {
				if (!checkvector[i - 1]) {
					num++;
					file << this->paper.GetStem(i) << '|'
						<< this->paper.GetOption(i, 1) << '|' << this->paper.GetOption(i, 2) << '|' << this->paper.GetOption(i, 3) << '|' << this->paper.GetOption(i, 4) << '|'
						<< this->paper.GetAnswer(i, 1) << this->paper.GetAnswer(i, 2) << this->paper.GetAnswer(i, 3) << this->paper.GetAnswer(i, 4)
						<< endl;
				}
			}
			file.seekp(ios::beg);
			file << num << endl;

			file.close();

			//给学生查看成绩
			CString str;
			str.Format(TEXT("最终成绩：%d/%d"), Stu_Score, this->paper.GetTotalScore());
			MessageBox(str);

			//结束考试
			this->EndDialog(0);
		}
	}

}


void CTestDlg::Previous()
{
	// TODO: 在此添加控件通知处理程序代码
	//先记录答案
	if (Check_option1.GetCheck())
		this->Stu_answer[this->counter - 1][0] = 1;
	else
		this->Stu_answer[this->counter - 1][0] = 0;
	if (Check_option2.GetCheck())
		this->Stu_answer[this->counter - 1][1] = 1;
	else
		this->Stu_answer[this->counter - 1][1] = 0;
	if (Check_option3.GetCheck())
		this->Stu_answer[this->counter - 1][2] = 1;
	else
		this->Stu_answer[this->counter - 1][2] = 0;
	if (Check_option4.GetCheck())
		this->Stu_answer[this->counter - 1][3] = 1;
	else
		this->Stu_answer[this->counter - 1][3] = 0;

	//跳转到上一题
	this->counter--;
	Text_stem.SetWindowTextW(CA2T(this->paper.GetStem(this->counter).c_str()));		//设置题干
	Check_option1.SetWindowTextW(CA2T(this->paper.GetOption(this->counter, 1).c_str()));
	Check_option2.SetWindowTextW(CA2T(this->paper.GetOption(this->counter, 2).c_str()));
	Check_option3.SetWindowTextW(CA2T(this->paper.GetOption(this->counter, 3).c_str()));
	Check_option4.SetWindowTextW(CA2T(this->paper.GetOption(this->counter, 4).c_str()));	//设置答案
	
	//单选多选提示
	if (this->counter == this->paper.GetSinCount())
		Text_prompt.SetWindowTextW(TEXT("(单选)"));

	//显示目前所选择答案
	if (Stu_answer[this->counter - 1][0])
		Check_option1.SetCheck(BST_CHECKED);
	else
		Check_option1.SetCheck(BST_UNCHECKED);
	if (Stu_answer[this->counter - 1][1])
		Check_option2.SetCheck(BST_CHECKED);
	else
		Check_option2.SetCheck(BST_UNCHECKED);
	if (Stu_answer[this->counter - 1][2])
		Check_option3.SetCheck(BST_CHECKED);
	else
		Check_option3.SetCheck(BST_UNCHECKED);
	if (Stu_answer[this->counter - 1][3])
		Check_option4.SetCheck(BST_CHECKED);
	else
		Check_option4.SetCheck(BST_UNCHECKED);

	//若当前题为最后一题，修改回下一题按钮
	if (this->counter + 1 == this->paper.GetQcount())
		Button_next.SetWindowTextW(TEXT("下一题"));

	//若上一题即为第一题，上一题按钮失活
	if (this->counter == 1)
		Button_previous.EnableWindow(FALSE);
}


void CTestDlg::SelectOptionA()
{
	// TODO: 在此添加控件通知处理程序代码

	//单选题时只能选一个
	if (this->counter <= this->paper.GetSinCount()) {
		Check_option2.SetCheck(BST_UNCHECKED);
		Check_option3.SetCheck(BST_UNCHECKED);
		Check_option4.SetCheck(BST_UNCHECKED);
	}
}


void CTestDlg::SelectOptionB()
{
	// TODO: 在此添加控件通知处理程序代码
	if (this->counter <= this->paper.GetSinCount()) {
		Check_option1.SetCheck(BST_UNCHECKED);
		Check_option3.SetCheck(BST_UNCHECKED);
		Check_option4.SetCheck(BST_UNCHECKED);
	}
}


void CTestDlg::SelectOptionC()
{
	// TODO: 在此添加控件通知处理程序代码
	if (this->counter <= this->paper.GetSinCount()) {
		Check_option1.SetCheck(BST_UNCHECKED);
		Check_option2.SetCheck(BST_UNCHECKED);
		Check_option4.SetCheck(BST_UNCHECKED);
	}
}


void CTestDlg::SelectOptionD()
{
	// TODO: 在此添加控件通知处理程序代码
	if (this->counter <= this->paper.GetSinCount()) {
		Check_option1.SetCheck(BST_UNCHECKED);
		Check_option2.SetCheck(BST_UNCHECKED);
		Check_option3.SetCheck(BST_UNCHECKED);
	}
}
