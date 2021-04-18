// CAdmin_AddDlg.cpp: 实现文件
//

#include "pch.h"
#include "MCESystem.h"
#include "CAdmin_AddDlg.h"
#include "afxdialogex.h"

#include "User.h"


// CAdmin_AddDlg 对话框

IMPLEMENT_DYNAMIC(CAdmin_AddDlg, CDialogEx)

CAdmin_AddDlg::CAdmin_AddDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Admin_Adddlg, pParent)
	, user_id(_T(""))
	, user_pwd(_T(""))
	, user_name(_T(""))
{

}

CAdmin_AddDlg::~CAdmin_AddDlg()
{
}

void CAdmin_AddDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, user_id);
	DDX_Text(pDX, IDC_EDIT6, user_pwd);
	DDX_Text(pDX, IDC_EDIT7, user_name);
	DDX_Control(pDX, IDC_RADIO3, as_tec);
	DDX_Control(pDX, IDC_RADIO4, as_stu);
	DDX_Control(pDX, IDC_BUTTON1, button_add);
}


BEGIN_MESSAGE_MAP(CAdmin_AddDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CAdmin_AddDlg::Add)
END_MESSAGE_MAP()


// CAdmin_AddDlg 消息处理程序


void CAdmin_AddDlg::Add()
{
	// TODO: 在此添加控件通知处理程序代码
		// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	string name(CT2A(user_name.GetString()));
	string id(CT2A(user_id.GetString()));
	string pwd(CT2A(user_pwd.GetString()));

	if (name.empty() || id.empty() || pwd.empty()) {
		MessageBox(TEXT("请完整填写"));
		return;
	}
	if (!as_tec.GetCheck() && !as_stu.GetCheck()) {	//未选择类型
		MessageBox(TEXT("请选择用户类型"));
		return;
	}

	//填写完整，尝试注册
	User user(id, pwd, name);

	if (as_stu.GetCheck() && !as_tec.GetCheck())	//学生账户注册
		user.identity = "S";
	else if (as_tec.GetCheck() && !as_stu.GetCheck()) //教师账户注册
		user.identity = "T";

	if (!user.Register()) {
		MessageBox(TEXT("账号已存在"));
		return;
	}
	else {
		MessageBox(TEXT("添加成功"));
		this->EndDialog(0);
	}


	return;
}
