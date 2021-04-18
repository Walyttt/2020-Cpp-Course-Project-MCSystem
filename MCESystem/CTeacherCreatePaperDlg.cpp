// CTeacherCreatePaperDlg.cpp: 实现文件
//

#include "pch.h"
#include "MCESystem.h"
#include "CTeacherCreatePaperDlg.h"
#include "afxdialogex.h"
#include "QuestionAndPaper.h"

int s_count = 0, m_count = 0;
string letter[] = { "A","B","C","D" };

// CTeacherCreatePaperDlg 对话框

IMPLEMENT_DYNAMIC(CTeacherCreatePaperDlg, CDialogEx)

CTeacherCreatePaperDlg::CTeacherCreatePaperDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TeacherCreatePaper, pParent)
{

}

CTeacherCreatePaperDlg::~CTeacherCreatePaperDlg()
{
}

void CTeacherCreatePaperDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO1, Radio_type_single);
	DDX_Control(pDX, IDC_RADIO2, Radio_type_mul);
	DDX_Control(pDX, IDC_RADIO5, Radio_level_easy);
	DDX_Control(pDX, IDC_RADIO6, Radio_level_normal);
	DDX_Control(pDX, IDC_RADIO7, Radio_level_hard);
	DDX_Control(pDX, IDC_LIST1, List_question);
	DDX_Control(pDX, IDC_LIST2, List_question_selected);
	DDX_Control(pDX, IDC_BUTTON1, Button_select);
	DDX_Control(pDX, IDC_BUTTON4, Button_create);
	DDX_Control(pDX, IDC_BUTTON6, Button_throw);
	DDX_Control(pDX, IDC_EDIT1, Edit_papername);

	s_count = 0, m_count = 0;
	CString head[] = { TEXT("题干"), TEXT("选项A"), TEXT("选项B"), TEXT("选项C"), TEXT("选项D"), TEXT("正确答案"), TEXT("题型") };
	for (int i = 0; i < 7; i++) {
		List_question.InsertColumn(i, head[i], LVCFMT_LEFT, 250);
		List_question_selected.InsertColumn(i, head[i], LVCFMT_LEFT, 250);
	}
	List_question.SetExtendedStyle(List_question.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	List_question_selected.SetExtendedStyle(List_question.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

}


BEGIN_MESSAGE_MAP(CTeacherCreatePaperDlg, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO1, &CTeacherCreatePaperDlg::ClickSingle)
	ON_BN_CLICKED(IDC_RADIO2, &CTeacherCreatePaperDlg::ClickMul)
	ON_BN_CLICKED(IDC_RADIO5, &CTeacherCreatePaperDlg::ClickEasy)
	ON_BN_CLICKED(IDC_RADIO6, &CTeacherCreatePaperDlg::ClickNoraml)
	ON_BN_CLICKED(IDC_RADIO7, &CTeacherCreatePaperDlg::ClickHard)
	ON_BN_CLICKED(IDC_BUTTON1, &CTeacherCreatePaperDlg::Select)
	ON_BN_CLICKED(IDC_BUTTON6, &CTeacherCreatePaperDlg::Throw)
	ON_BN_CLICKED(IDC_BUTTON4, &CTeacherCreatePaperDlg::Create)
END_MESSAGE_MAP()


// CTeacherCreatePaperDlg 消息处理程序


void CTeacherCreatePaperDlg::ClickSingle()
{
	// TODO: 在此添加控件通知处理程序代码
	//点击了“单选”
	ifstream infile;

	//清空列表
	List_question.DeleteAllItems();

	//若选择了难度，打开对应文件，否则返回
	if (Radio_level_easy.GetCheck())
		infile.open(_F_SQE);
	else if (Radio_level_normal.GetCheck())
		infile.open(_F_SQN);
	else if (Radio_level_hard.GetCheck())
		infile.open(_F_SQH);
	else
		return;

	//开始读取
	int q_num;	//题目总数

	infile >> q_num;
	infile.get();

	for (int i = 0; i < q_num; i++) {
		//每行格式为  "stem|A|B|C|D|answer"
		char buf[1024] = { 0 };
		infile.getline(buf, sizeof(buf));

		CString stem(strtok(buf, "|"));//开始切割
		CString option_1(strtok(NULL, "|"));
		CString option_2(strtok(NULL, "|"));
		CString option_3(strtok(NULL, "|"));
		CString option_4(strtok(NULL, "|"));
		CString answer_num(strtok(NULL, "|"));

		CString answer = TEXT("");
		if (answer_num[0] == '1')
			answer += TEXT("A");
		if (answer_num[1] == '1')
			answer += TEXT("B");
		if (answer_num[2] == '1')
			answer += TEXT("C");
		if (answer_num[3] == '1')
			answer += TEXT("D");

		List_question.InsertItem(i, stem);
		List_question.SetItemText(i, 1, option_1);
		List_question.SetItemText(i, 2, option_2);
		List_question.SetItemText(i, 3, option_3);
		List_question.SetItemText(i, 4, option_4);
		List_question.SetItemText(i, 5, answer);
	}

	//关闭文件
	infile.close();

}


void CTeacherCreatePaperDlg::ClickMul()
{
	// TODO: 在此添加控件通知处理程序代码
		//点击了“多选”
	ifstream infile;

	//清空列表
	List_question.DeleteAllItems();

	//若选择了难度，打开对应文件，否则返回
	if (Radio_level_easy.GetCheck())
		infile.open(_F_MQE);
	else if (Radio_level_normal.GetCheck())
		infile.open(_F_MQN);
	else if (Radio_level_hard.GetCheck())
		infile.open(_F_MQH);
	else
		return;

	//开始读取
	int q_num;	//题目总数

	infile >> q_num;
	infile.get();

	for (int i = 0; i < q_num; i++) {
		//每行格式为  "stem|A|B|C|D|answer"
		char buf[1024] = { 0 };
		infile.getline(buf, sizeof(buf));

		CString stem(strtok(buf, "|"));//开始切割
		CString option_1(strtok(NULL, "|"));
		CString option_2(strtok(NULL, "|"));
		CString option_3(strtok(NULL, "|"));
		CString option_4(strtok(NULL, "|"));
		CString answer_num(strtok(NULL, "|"));

		CString answer = TEXT("");
		if (answer_num[0] == '1')
			answer += TEXT("A");
		if (answer_num[1] == '1')
			answer += TEXT("B");
		if (answer_num[2] == '1')
			answer += TEXT("C");
		if (answer_num[3] == '1')
			answer += TEXT("D");

		List_question.InsertItem(i, stem);
		List_question.SetItemText(i, 1, option_1);
		List_question.SetItemText(i, 2, option_2);
		List_question.SetItemText(i, 3, option_3);
		List_question.SetItemText(i, 4, option_4);
		List_question.SetItemText(i, 5, answer);

	}

	//关闭文件
	infile.close();
}


void CTeacherCreatePaperDlg::ClickEasy()
{
	// TODO: 在此添加控件通知处理程序代码
	//点击了“简单”
	ifstream infile;

	//清空列表
	List_question.DeleteAllItems();

	//若选择了题型，打开对应文件，否则返回
	if (Radio_type_single.GetCheck())
		infile.open(_F_SQE);
	else if (Radio_type_mul.GetCheck())
		infile.open(_F_MQE);
	else
		return;

	//开始读取
	int q_num;	//题目总数

	infile >> q_num;
	infile.get();

	for (int i = 0; i < q_num; i++) {
		//每行格式为  "stem|A|B|C|D|answer"
		char buf[1024] = { 0 };
		infile.getline(buf, sizeof(buf));

		CString stem(strtok(buf, "|"));//开始切割
		CString option_1(strtok(NULL, "|"));
		CString option_2(strtok(NULL, "|"));
		CString option_3(strtok(NULL, "|"));
		CString option_4(strtok(NULL, "|"));
		CString answer_num(strtok(NULL, "|"));

		CString answer = TEXT("");
		if (answer_num[0] == '1')
			answer += TEXT("A");
		if (answer_num[1] == '1')
			answer += TEXT("B");
		if (answer_num[2] == '1')
			answer += TEXT("C");
		if (answer_num[3] == '1')
			answer += TEXT("D");

		List_question.InsertItem(i, stem);
		List_question.SetItemText(i, 1, option_1);
		List_question.SetItemText(i, 2, option_2);
		List_question.SetItemText(i, 3, option_3);
		List_question.SetItemText(i, 4, option_4);
		List_question.SetItemText(i, 5, answer);
	}

	//关闭文件
	infile.close();
}


void CTeacherCreatePaperDlg::ClickNoraml()
{
	// TODO: 在此添加控件通知处理程序代码
	//点击了“普通”
	ifstream infile;

	//清空列表
	List_question.DeleteAllItems();

	//若选择了题型，打开对应文件，否则返回
	if (Radio_type_single.GetCheck())
		infile.open(_F_SQN);
	else if (Radio_type_mul.GetCheck())
		infile.open(_F_MQN);
	else
		return;

	//开始读取
	int q_num;	//题目总数

	infile >> q_num;
	infile.get();

	for (int i = 0; i < q_num; i++) {
		//每行格式为  "stem|A|B|C|D|answer"
		char buf[1024] = { 0 };
		infile.getline(buf, sizeof(buf));

		CString stem(strtok(buf, "|"));//开始切割
		CString option_1(strtok(NULL, "|"));
		CString option_2(strtok(NULL, "|"));
		CString option_3(strtok(NULL, "|"));
		CString option_4(strtok(NULL, "|"));
		CString answer_num(strtok(NULL, "|"));

		CString answer = TEXT("");
		if (answer_num[0] == '1')
			answer += TEXT("A");
		if (answer_num[1] == '1')
			answer += TEXT("B");
		if (answer_num[2] == '1')
			answer += TEXT("C");
		if (answer_num[3] == '1')
			answer += TEXT("D");

		List_question.InsertItem(i, stem);
		List_question.SetItemText(i, 1, option_1);
		List_question.SetItemText(i, 2, option_2);
		List_question.SetItemText(i, 3, option_3);
		List_question.SetItemText(i, 4, option_4);
		List_question.SetItemText(i, 5, answer);
	}

	//关闭文件
	infile.close();
}


void CTeacherCreatePaperDlg::ClickHard()
{
	// TODO: 在此添加控件通知处理程序代码
	//点击了“困难”
	ifstream infile;

	//清空列表
	List_question.DeleteAllItems();

	//若选择了题型，打开对应文件，否则返回
	if (Radio_type_single.GetCheck())
		infile.open(_F_SQH);
	else if (Radio_type_mul.GetCheck())
		infile.open(_F_MQH);
	else
		return;

	//开始读取
	int q_num;	//题目总数

	infile >> q_num;
	infile.get();

	for (int i = 0; i < q_num; i++) {
		//每行格式为  "stem|A|B|C|D|answer"
		char buf[1024] = { 0 };
		infile.getline(buf, sizeof(buf));

		CString stem(strtok(buf, "|"));//开始切割
		CString option_1(strtok(NULL, "|"));
		CString option_2(strtok(NULL, "|"));
		CString option_3(strtok(NULL, "|"));
		CString option_4(strtok(NULL, "|"));
		CString answer_num(strtok(NULL, "|"));

		CString answer = TEXT("");
		if (answer_num[0] == '1')
			answer += TEXT("A");
		if (answer_num[1] == '1')
			answer += TEXT("B");
		if (answer_num[2] == '1')
			answer += TEXT("C");
		if (answer_num[3] == '1')
			answer += TEXT("D");

		List_question.InsertItem(i, stem);
		List_question.SetItemText(i, 1, option_1);
		List_question.SetItemText(i, 2, option_2);
		List_question.SetItemText(i, 3, option_3);
		List_question.SetItemText(i, 4, option_4);
		List_question.SetItemText(i, 5, answer);
	}

	//关闭文件
	infile.close();

}


void CTeacherCreatePaperDlg::Select()
{
	// TODO: 在此添加控件通知处理程序代码
	int nId, next;

	POSITION pos = List_question.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(TEXT("请至少选择一项"), TEXT("提示"), MB_ICONEXCLAMATION);
		return;
	}

	//得到行号，通过POSITION转化并得到待选择题目
	nId = (int)List_question.GetNextSelectedItem(pos);
	if (Radio_type_single.GetCheck())
		next = s_count++;
	else {
		next = s_count + m_count;
		m_count++;
	}

	List_question_selected.InsertItem(next, List_question.GetItemText(nId, 0));

	for (int i = 1; i < 6; i++) {
		List_question_selected.SetItemText(next, i, List_question.GetItemText(nId, i));
	}
	if (Radio_type_single.GetCheck())
		List_question_selected.SetItemText(next, 6, TEXT("S"));
	else
		List_question_selected.SetItemText(next, 6, TEXT("M"));


	
}


void CTeacherCreatePaperDlg::Throw()
{
	// TODO: 在此添加控件通知处理程序代码
	int nId;

	POSITION pos = List_question_selected.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(TEXT("请至少选择一项"), TEXT("提示"), MB_ICONEXCLAMATION);
		return;
	}

	nId = (int)List_question_selected.GetNextSelectedItem(pos);

	//全局变量自减
	if (List_question_selected.GetItemText(nId, 6) == TEXT("S"))
		s_count--;
	else
		m_count--;


	List_question_selected.DeleteItem(nId);

	return;
}


void CTeacherCreatePaperDlg::Create()
{
	// TODO: 在此添加控件通知处理程序代码

	//发布试卷：1、修改教师本人试卷列表 2、创建试卷文件夹，内有试卷和学生考试记录
	
	
	fstream file;
	ofstream outfile;
	int papernum;

	CString temp;
	Edit_papername.GetWindowTextW(temp);
	string papername(CT2A(temp.GetString()));

	//检测试卷名填写
	if (papername.empty()) {
		MessageBox(TEXT("请填写试卷名"));
		return;
	}

	//检测题目数是否大于0
	if (s_count + m_count == 0) {
		MessageBox(TEXT("请选择题目"));
		return;
	}


	//文件路径
	char path_ori[1024] = { 0 },		//教师文件夹
		path_paperlist[1024] = { 0 },	//教师试卷列表
		path_paper_dir[1024] = { 0 },	//试卷文件夹
		buf[1024] = { 0 };

	//1、将试卷名和路径写进试卷列表，每行为一试卷，格式：试卷名|试卷路径|试卷考试记录路径
	strcpy(path_ori, _D_Teacher);		//"D:\\TestSystem\\Teacher\\"
	strcat(path_ori, user.id.c_str());	//"D:\\TestSystem\\Teacher\\id"
	strcpy(path_paperlist, path_ori);	
	strcat(path_paperlist, "\\PaperList.txt");	//"D:\\TestSystem\\Teacher\\id\\PaperList.txt"
	strcpy(path_paper_dir, path_ori);
	strcat(path_paper_dir, "\\");
	strcat(path_paper_dir, papername.c_str());	//"D:\\TestSystem\\Teacher\\id\\papername"

	file.open(path_paperlist, ios::in | ios::out);
	file >> papernum;
	file.get();

	file.seekp(ios::beg);
	file << (++papernum) << endl;
	file.seekp(0, ios::end);
	file << papername << '|'
		<< _D_Teacher << user.id << "\\" << papername << "\\" << "paper.txt" << '|'
		<< _D_Teacher << user.id << "\\" << papername << "\\" << "log.txt" << endl;
	file.close();

	//2、创建试卷目录
	_mkdir(path_paper_dir);
	
	//3、创建试卷文件和记录文件
	file.open(path_paperlist, ios::in);
	file >> papernum;
	file.get();

	while (papernum--)
		file.getline(buf, sizeof(buf));

	file.close();
	strtok(buf, "|");
	char* path_paper = strtok(NULL, "|");	//试卷路径
	char* path_log = strtok(NULL, "|");		//记录路径

	outfile.open(path_log);
	outfile << 0 << endl;
	outfile.close();

	/*试卷文件格式：第一行：试卷名
					第二行：单选题数 多选题数
					第三行开始：每行为 题目|选项A|B|C|D|答案
	*/
	
	outfile.open(path_paper);
	outfile << papername << endl;
	outfile << s_count << ' ' << m_count << endl;
	for (int i = 0; i < s_count + m_count; i++) {
		string stem(CT2A(List_question_selected.GetItemText(i, 0).GetString()));
		string option_1(CT2A(List_question_selected.GetItemText(i, 1).GetString()));
		string option_2(CT2A(List_question_selected.GetItemText(i, 2).GetString()));
		string option_3(CT2A(List_question_selected.GetItemText(i, 3).GetString()));
		string option_4(CT2A(List_question_selected.GetItemText(i, 4).GetString()));
		string answer(CT2A(List_question_selected.GetItemText(i, 5).GetString()));
		string type(CT2A(List_question_selected.GetItemText(i, 6).GetString()));

		outfile << stem << '|' << option_1 << '|' << option_2 << '|' << option_3 << '|' << option_4 << '|';
		for (int j = 0; j < 4; j++) {
			if (answer.find(letter[j]) == string::npos)
				outfile << 0;
			else
				outfile << 1;
		}
		outfile << '|' << type << endl;
	}
	outfile.close();

	MessageBox(TEXT("发布成功"));
	this->EndDialog(0);

	return;
}
