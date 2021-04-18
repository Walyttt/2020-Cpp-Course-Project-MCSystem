// CAdminDlg.cpp: 实现文件
//

#include "pch.h"
#include "MCESystem.h"
#include "CAdminDlg.h"
#include "afxdialogex.h"

#include "User.h"
#include "CAdmin_AddDlg.h"


// CAdminDlg 对话框

IMPLEMENT_DYNAMIC(CAdminDlg, CDialogEx)

CAdminDlg::CAdminDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_AdminDlg, pParent)
{

}

CAdminDlg::~CAdminDlg()
{
}

void CAdminDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, user_list);
	DDX_Control(pDX, IDC_BUTTON1, button_add);
	DDX_Control(pDX, IDC_BUTTON3, button_delete);

	//设置任务栏图标
	this->ModifyStyleEx(0, WS_EX_APPWINDOW);

	//设置表头
	CString head[] = { TEXT("账号"),TEXT("密码"), TEXT("姓名"), TEXT("身份") };
	for (int i = 0; i < 4; i++) 
		user_list.InsertColumn(i, head[i], LVCFMT_LEFT, 135);

	//读取用户列表，设置表内容
	ifstream file;
	int usernum;

	file.open(_F_LOGIN);
	file >> usernum;
	file.get();

	for (int i = 0; i < usernum; i++) {
		//每行格式为  "id|pwd|name|identity"
		char buf[1024] = { 0 };
		file.getline(buf, sizeof(buf));


		CString id(strtok(buf, "|"));//开始切割
		CString pwd(strtok(NULL, "|"));
		CString name(strtok(NULL, "|"));
		CString identity(strtok(NULL, "|"));

		user_list.InsertItem(i, id);
		user_list.SetItemText(i, 1, pwd);
		user_list.SetItemText(i, 2, name);
		if (identity == TEXT("S"))
			user_list.SetItemText(i, 3, TEXT("学生"));
		else
			user_list.SetItemText(i, 3, TEXT("教师"));
	}
	file.close();

	user_list.SetExtendedStyle(user_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

}


BEGIN_MESSAGE_MAP(CAdminDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CAdminDlg::AddUser)
	ON_BN_CLICKED(IDC_BUTTON3, &CAdminDlg::DeleteUser)
END_MESSAGE_MAP()


// CAdminDlg 消息处理程序


void CAdminDlg::AddUser()
{
	// TODO: 在此添加控件通知处理程序代码
	CAdmin_AddDlg dlg_add;
	dlg_add.DoModal();

	//重新读取用户列表，设置表内容
	user_list.DeleteAllItems();

	ifstream file;
	int usernum;

	file.open(_F_LOGIN);
	file >> usernum;
	file.get();

	for (int i = 0; i < usernum; i++) {
		//每行格式为  "id|pwd|name|identity"
		char buf[1024] = { 0 };
		file.getline(buf, sizeof(buf));


		CString id(strtok(buf, "|"));//开始切割
		CString pwd(strtok(NULL, "|"));
		CString name(strtok(NULL, "|"));
		CString identity(strtok(NULL, "|"));

		user_list.InsertItem(i, id);
		user_list.SetItemText(i, 1, pwd);
		user_list.SetItemText(i, 2, name);
		if (identity == TEXT("S"))
			user_list.SetItemText(i, 3, TEXT("学生"));
		else
			user_list.SetItemText(i, 3, TEXT("教师"));
	}
	file.close();

	user_list.SetExtendedStyle(user_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
}


void CAdminDlg::DeleteUser()
{
	// TODO: 在此添加控件通知处理程序代码

	int nId;

	POSITION pos = user_list.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(TEXT("请至少选择一项"), TEXT("提示"), MB_ICONEXCLAMATION);
		return;
	}

	//提示是否确认删除
	if (MessageBox(TEXT("确认删除？"), TEXT("提示"), MB_OKCANCEL) == IDOK) {
		//得到行号，通过POSITION转化并得到待删除账号
		nId = (int)user_list.GetNextSelectedItem(pos);
		string id_to_delete = CT2A(user_list.GetItemText(nId, 0));

		User user(id_to_delete);
		user.Delete();
	}

	//更新列表
	user_list.DeleteAllItems();

	//读取用户列表，设置表内容
	ifstream file;
	int usernum;

	file.open(_F_LOGIN);
	file >> usernum;
	file.get();

	for (int i = 0; i < usernum; i++) {
		//每行格式为  "id|pwd|name|identity"
		char buf[1024] = { 0 };
		file.getline(buf, sizeof(buf));


		CString id(strtok(buf, "|"));//开始切割
		CString pwd(strtok(NULL, "|"));
		CString name(strtok(NULL, "|"));
		CString identity(strtok(NULL, "|"));

		user_list.InsertItem(i, id);
		user_list.SetItemText(i, 1, pwd);
		user_list.SetItemText(i, 2, name);
		if (identity == TEXT("S"))
			user_list.SetItemText(i, 3, TEXT("学生"));
		else
			user_list.SetItemText(i, 3, TEXT("教师"));
	}
	file.close();

	user_list.SetExtendedStyle(user_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
}
