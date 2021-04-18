// CStudentDlg.cpp: 实现文件
//

#include "pch.h"
#include "MCESystem.h"
#include "CStudentDlg.h"
#include "afxdialogex.h"

#include "CChgpwdDlg.h"
#include "User.h"
#include "QuestionAndPaper.h"
#include "CTestDlg.h"
#include "CStudentLogDlg.h"
#include "CStudentWrongCollectionDlg.h"

//教师id,试卷名，试卷数和两个路径设为全局变量
char id[1024][1024];
int papernum;
char papername[1024][1024];
char path_to_paper[1024][1024];
char path_to_log[1024][1024];

// CStudentDlg 对话框

IMPLEMENT_DYNAMIC(CStudentDlg, CDialogEx)

CStudentDlg::CStudentDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_StudentDlg, pParent)
{

}

CStudentDlg::~CStudentDlg()
{
}

void CStudentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//设置任务栏图标
	this->ModifyStyleEx(0, WS_EX_APPWINDOW);

	DDX_Control(pDX, IDC_USERNAME, Text_username);
	DDX_Control(pDX, IDC_COMBO1, Combo_teacher);
	DDX_Control(pDX, IDC_LIST1, List_paper);
	DDX_Control(pDX, IDC_BUTTON1, Button_test);
	DDX_Control(pDX, IDC_BUTTON2, Button_Chgpwd);

	//设置欢迎语句
	CString username = TEXT("你好，");
	username += CA2T(user.name.c_str());
	username += TEXT(" 同学");
	Text_username.SetWindowTextW(username);

	//设置教师选择
	ifstream file_in;
	int usernum, count = 0;

	file_in.open(_F_LOGIN, ios::in);
	file_in >> usernum;
	file_in.get();

	for (int i = 0; i < usernum; i++) {
		char buf[1024] = { 0 };
		file_in.getline(buf, sizeof(buf));

		char *id_temp = strtok(buf, "|");//开始切割
		char *pwd_temp = strtok(NULL, "|");
		char *name_temp = strtok(NULL, "|");
		char *identity_temp = strtok(NULL, "|");

		if (!strcmp(identity_temp, "T")) {	//为教师
			CString name(name_temp);
			Combo_teacher.InsertString(count, name);
			strcpy(id[count], id_temp);		//插入id
			count++;
		}
	}

	file_in.close();
	DDX_Control(pDX, IDC_BUTTON7, Button_log);
	DDX_Control(pDX, IDC_BUTTON8, Button_WrongCollection);
}


BEGIN_MESSAGE_MAP(CStudentDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CStudentDlg::ChgPwd)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CStudentDlg::SelectTeacher)
	ON_BN_CLICKED(IDC_BUTTON1, &CStudentDlg::TestBegin)
	ON_BN_CLICKED(IDC_BUTTON7, &CStudentDlg::CheckLog)
	ON_BN_CLICKED(IDC_BUTTON8, &CStudentDlg::CheckWrongCollection)
END_MESSAGE_MAP()


// CStudentDlg 消息处理程序


void CStudentDlg::ChgPwd()
{
	// TODO: 在此添加控件通知处理程序代码
	CChgpwdDlg chgpwd_dlg;
	chgpwd_dlg.user = this->user;
	chgpwd_dlg.DoModal();
}


void CStudentDlg::SelectTeacher()
{
	// TODO: 在此添加控件通知处理程序代码
	/*选中了老师，在list中给出试卷*/

	//清空列表
	List_paper.DeleteAllItems();

	//获取索引值
	CString Cname;
	int index = Combo_teacher.GetCurSel();	//获取索引值

	//开始拼接试卷列表路径
	char path[1024];
	strcpy(path, _D_Teacher);
	strcat(path, id[index]);
	strcat(path, "\\PaperList.txt");

	//打开列表文件，并将试卷显示在窗口，同时更新全局变量
	ifstream file_in;
	file_in.open(path);

	file_in >> papernum;
	file_in.get();

	for (int i = 0; i < papernum; i++) {
		char buf[1024] = { 0 };
		file_in.getline(buf, sizeof(buf));

		char* papername_temp = strtok(buf, "|");
		char* path_to_paper_temp = strtok(NULL, "|");
		char* path_to_log_temp = strtok(NULL, "|");

		strcpy(papername[i], papername_temp);
		strcpy(path_to_paper[i], path_to_paper_temp);
		strcpy(path_to_log[i], path_to_log_temp);

		CString Cpapername(papername_temp);
		List_paper.InsertItem(i,Cpapername);
	}

}


void CStudentDlg::TestBegin()
{
	// TODO: 在此添加控件通知处理程序代码
	int nId, i;

	POSITION pos = List_paper.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(TEXT("请至少选择一项"), TEXT("提示"), MB_ICONEXCLAMATION);
		return;
	}

	//得到行号，通过POSITION转化并得到待选择试卷
	nId = (int)List_paper.GetNextSelectedItem(pos);

	Paper paper(papername[nId], path_to_paper[nId], path_to_log[nId]);
	
	CTestDlg dlg_text;
	dlg_text.stu = user;
	dlg_text.paper = paper;
	dlg_text.DoModal();

}


void CStudentDlg::CheckLog()
{
	// TODO: 在此添加控件通知处理程序代码
	CStudentLogDlg dlg_log;
	dlg_log.stu = this->user;
	dlg_log.DoModal();

}


void CStudentDlg::CheckWrongCollection()
{
	// TODO: 在此添加控件通知处理程序代码
	CStudentWrongCollectionDlg dlg_wrongcoll;
	dlg_wrongcoll.stu = this->user;
	dlg_wrongcoll.DoModal();
}
