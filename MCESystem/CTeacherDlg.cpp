// CTeacherDlg.cpp: 实现文件
//

#include "pch.h"
#include "MCESystem.h"
#include "CTeacherDlg.h"
#include "afxdialogex.h"
#include "CQManagementDlg.h"
#include "CChgpwdDlg.h"
#include "CTeacherCreatePaperDlg.h"
#include "QuestionAndPaper.h"

char paper[1024][1024];
char path_paper[1024][1024];
char path_log[1024][1024];

// CTeacherDlg 对话框

IMPLEMENT_DYNAMIC(CTeacherDlg, CDialogEx)

CTeacherDlg::CTeacherDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TeacherDlg, pParent)
{

}

CTeacherDlg::~CTeacherDlg()
{
}

void CTeacherDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_USERNAME, Edit_username);
	DDX_Control(pDX, IDC_BUTTON3, Button_manage);
	DDX_Control(pDX, IDC_BUTTON5, Button_chgpwd);
	DDX_Control(pDX, IDC_BUTTON1, Button_createpaper);
	DDX_Control(pDX, IDC_COMBO1, Combo_paper);
	DDX_Control(pDX, IDC_EDIT4, Edit_SinCount);
	DDX_Control(pDX, IDC_EDIT5, Edit_MulCount);
	DDX_Control(pDX, IDC_EDIT8, Edit_TotalScore);
	DDX_Control(pDX, IDC_LIST1, List_StuScore);

	//设置任务栏图标
	this->ModifyStyleEx(0, WS_EX_APPWINDOW);

	//设置欢迎语句
	CString username = TEXT("您好，");
	username += CA2T(user.name.c_str());
	username += TEXT(" 老师");
	Edit_username.SetWindowTextW(username);

	//拼接路径,设置试卷选项
	char path[1024];
	strcpy(path, _D_Teacher);
	strcat(path, user.id.c_str());
	strcat(path, "\\PaperList.txt");	//试卷列表路径

										//打开列表文件，并将试卷显示在窗口，同时更新全局变量
	ifstream file_in;
	file_in.open(path);

	int papernum;
	file_in >> papernum;
	file_in.get();

	for (int i = 0; i < papernum; i++) {
		char buf[1024] = { 0 };
		file_in.getline(buf, sizeof(buf));

		char* papername_temp = strtok(buf, "|");
		char* path_to_paper_temp = strtok(NULL, "|");
		char* path_to_log_temp = strtok(NULL, "|");

		strcpy(paper[i], papername_temp);
		strcpy(path_paper[i], path_to_paper_temp);
		strcpy(path_log[i], path_to_log_temp);

		CString Cpapername(papername_temp);
		Combo_paper.InsertString(i, Cpapername);
	}

	//添加列表标头
	List_StuScore.InsertColumn(0, TEXT("姓名"), LVCFMT_LEFT, 220);
	List_StuScore.InsertColumn(0, TEXT("成绩"), LVCFMT_LEFT, 220);
}


BEGIN_MESSAGE_MAP(CTeacherDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON3, &CTeacherDlg::ManageQuestion)
	ON_BN_CLICKED(IDC_BUTTON5, &CTeacherDlg::ChangePwd)
	ON_BN_CLICKED(IDC_BUTTON1, &CTeacherDlg::CreatePaper)
	ON_BN_CLICKED(IDC_BUTTON2, &CTeacherDlg::CheckResult)
END_MESSAGE_MAP()


// CTeacherDlg 消息处理程序


void CTeacherDlg::ManageQuestion()
{
	// TODO: 在此添加控件通知处理程序代码
	CQManagementDlg manage_dlg;
	manage_dlg.DoModal();
}


void CTeacherDlg::ChangePwd()
{
	// TODO: 在此添加控件通知处理程序代码
	CChgpwdDlg chgpwd_dlg;
	chgpwd_dlg.user = this->user;
	chgpwd_dlg.DoModal();
}



void CTeacherDlg::CreatePaper()
{
	// TODO: 在此添加控件通知处理程序代码
	CTeacherCreatePaperDlg createpaper_dlg;
	createpaper_dlg.user = this->user;
	createpaper_dlg.DoModal();
}


void CTeacherDlg::CheckResult()
{
	// TODO: 在此添加控件通知处理程序代码
	//清空列表
	List_StuScore.DeleteAllItems();

	//获取索引值
	int index = Combo_paper.GetCurSel();

	//根据索引值找到试卷文件，并导出相关信息
	ifstream file;
	char temp[1024];
	int sin, mul;

	file.open(path_paper[index]);
	file.getline(temp, sizeof(temp));
	file >> sin >> mul;
	file.close();

	CString Csin, Cmul, Ctotal;
	Csin.Format(TEXT("%d"), sin);
	Cmul.Format(TEXT("%d"), mul);
	Ctotal.Format(TEXT("%d"), sin*Sin_score+mul*Mul_score);

	Edit_SinCount.SetWindowTextW(Csin);
	Edit_MulCount.SetWindowTextW(Cmul);
	Edit_TotalScore.SetWindowTextW(Ctotal);

	//根据索引值找到记录文件，并导出学生考试记录
	int lognum;

	file.open(path_log[index]);
	file >> lognum;
	file.get();

	for (int i = 0; i < lognum; i++) {
		char buf[1024] = { 0 };
		file.getline(buf, sizeof(buf));

		CString name(strtok(buf, "|"));//开始切割
		CString score(strtok(NULL, "|"));

		List_StuScore.InsertItem(i, name);
		List_StuScore.SetItemText(i, 1, score);
	}
	file.close();

	List_StuScore.SetExtendedStyle(List_StuScore.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
}
