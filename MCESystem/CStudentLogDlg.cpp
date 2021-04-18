// CStudentLogDlg.cpp: 实现文件
//

#include "pch.h"
#include "MCESystem.h"
#include "CStudentLogDlg.h"
#include "afxdialogex.h"



// CStudentLogDlg 对话框

IMPLEMENT_DYNAMIC(CStudentLogDlg, CDialogEx)

CStudentLogDlg::CStudentLogDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_StudentLogDlg, pParent)
{

}

CStudentLogDlg::~CStudentLogDlg()
{
}

void CStudentLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, List_log);

	List_log.InsertColumn(0, TEXT("试卷"), LVCFMT_LEFT, 210);
	List_log.InsertColumn(1, TEXT("成绩"), LVCFMT_LEFT, 210);

	ifstream file;
	char path[1024];
	int num;

	strcpy(path, _D_Student);
	strcat(path, this->stu.id.c_str());
	strcat(path, "//log.txt");

	file.open(path, ios::in | ios::out);
	file >> num;
	file.get();

	for (int i = 0; i < num; i++) {
		char buf[1024] = { 0 };
		file.getline(buf, sizeof(buf));

		CString papername(strtok(buf, "|"));//开始切割
		CString score(strtok(NULL, "|"));

		List_log.InsertItem(i, papername);
		List_log.SetItemText(i, 1, score);
	}
	file.close();

	List_log.SetExtendedStyle(List_log.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
}


BEGIN_MESSAGE_MAP(CStudentLogDlg, CDialogEx)
END_MESSAGE_MAP()


// CStudentLogDlg 消息处理程序
