// CRegisterDlg.cpp: 实现文件
//

#include "pch.h"
#include "MCESystem.h"
#include "CRegisterDlg.h"
#include "afxdialogex.h"
#include "User.h"


// CRegisterDlg 对话框

IMPLEMENT_DYNAMIC(CRegisterDlg, CDialogEx)

CRegisterDlg::CRegisterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Resgister, pParent)
	, user_name(_T(""))
	, user_id(_T(""))
	, user_pwd(_T(""))
	, user_pwd_verify(_T(""))

{

}

CRegisterDlg::~CRegisterDlg()
{
}

void CRegisterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT4, user_name);
	DDX_Text(pDX, IDC_EDIT1, user_id);
	DDX_Text(pDX, IDC_EDIT3, user_pwd);
	DDX_Text(pDX, IDC_EDIT5, user_pwd_verify);

	DDX_Control(pDX, IDC_RADIO1, as_stu);
	DDX_Control(pDX, IDC_RADIO2, as_tec);
}


BEGIN_MESSAGE_MAP(CRegisterDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CRegisterDlg::Register)
END_MESSAGE_MAP()


// CRegisterDlg 消息处理程序


void CRegisterDlg::Register()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	string name(CT2A(user_name.GetString()));
	string id(CT2A(user_id.GetString()));
	string pwd(CT2A(user_pwd.GetString()));
	string pwd_verify(CT2A(user_pwd_verify.GetString()));

	if (name.empty() || id.empty() || pwd.empty() || pwd_verify.empty()) {
		MessageBox(TEXT("请完整填写"));
		return;
	}
	if (!as_tec.GetCheck() && !as_stu.GetCheck()) {	//未选择类型
		MessageBox(TEXT("请选择注册类型"));
		return;
	}
	if (pwd != pwd_verify) {
		MessageBox(TEXT("两次输入密码不相同！"));
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
		MessageBox(TEXT("注册成功！请返回登录！"));
		this->EndDialog(0);
	}


	return;
}
