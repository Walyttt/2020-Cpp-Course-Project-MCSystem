// CChgpwdDlg.cpp: 实现文件
//

#include "pch.h"
#include "MCESystem.h"
#include "CChgpwdDlg.h"
#include "afxdialogex.h"


// CChgpwdDlg 对话框

IMPLEMENT_DYNAMIC(CChgpwdDlg, CDialogEx)

CChgpwdDlg::CChgpwdDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TeacherChgpwd_Dlg, pParent)
	, Edit_newpwd(_T(""))
	, Edit_newpwd_verify(_T(""))
{

}

CChgpwdDlg::~CChgpwdDlg()
{
}

void CChgpwdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, Edit_newpwd);
	DDX_Text(pDX, IDC_EDIT6, Edit_newpwd_verify);
	DDX_Control(pDX, IDC_BUTTON1, Button_chg);
}


BEGIN_MESSAGE_MAP(CChgpwdDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CChgpwdDlg::ChgPwd)
END_MESSAGE_MAP()


// CTeacherChgpwdDlg 消息处理程序


void CChgpwdDlg::ChgPwd()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	string newpwd(CT2A(Edit_newpwd.GetString()));
	string newpwd_verify(CT2A(Edit_newpwd_verify.GetString()));

	//检测两次密码是否相同
	if (newpwd != newpwd_verify) {
		MessageBox(TEXT("两次输入密码不同"));
		return;
	}

	//开始修改密码
	this->user.Chg_pwd(newpwd);
	MessageBox(TEXT("修改成功"));
	this->EndDialog(0);
	return;
}
