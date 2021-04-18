
// MCESystemDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MCESystem.h"
#include "MCESystemDlg.h"
#include "afxdialogex.h"

#include "CRegisterDlg.h"
#include "User.h"
#include "CAdminDlg.h"
#include "CTeacherDlg.h"
#include "CStudentDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMCESystemDlg 对话框



CMCESystemDlg::CMCESystemDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MCESYSTEM_DIALOG, pParent)
	, user_id(_T(""))
	, user_pwd(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMCESystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, user_id);
	DDX_Text(pDX, IDC_EDIT2, user_pwd);
	DDX_Control(pDX, IDC_BUTTON1, Button_Login);
	DDX_Control(pDX, IDC_BUTTON2, Button_Register);
}

BEGIN_MESSAGE_MAP(CMCESystemDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMCESystemDlg::Login)
	ON_BN_CLICKED(IDC_BUTTON2, &CMCESystemDlg::Register)
END_MESSAGE_MAP()


// CMCESystemDlg 消息处理程序

BOOL CMCESystemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMCESystemDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMCESystemDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMCESystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMCESystemDlg::Login()
{
	// TODO: 在此添加控件通知处理程序代码
		// TODO: 在此添加控件通知处理程序代码
	int status;
	CAdminDlg dlg_admin;
	CTeacherDlg dlg_teacher;
	CStudentDlg dlg_student;

	UpdateData(TRUE);

	string id(CT2A(user_id.GetString()));
	string pwd(CT2A(user_pwd.GetString()));

	User user(id, pwd);
	status = user.Login();

	switch (status)
	{
	case 0:
		this->ShowWindow(SW_HIDE);
		dlg_admin.DoModal();
		this->DestroyWindow();
		break;

	case 1:
		this->ShowWindow(SW_HIDE);
		dlg_student.user = user;		//传入用户参数
		dlg_student.DoModal();
		this->DestroyWindow();
		break;

	case 2:
		this->ShowWindow(SW_HIDE);
		dlg_teacher.user = user;		//传入用户参数
		dlg_teacher.DoModal();
		this->DestroyWindow();
		break;

	case -1:
		MessageBox(TEXT("登录失败"));
		break;

	default:

		break;
	}

}


void CMCESystemDlg::Register()
{
	// TODO: 在此添加控件通知处理程序代码
	CRegisterDlg dlg;

	dlg.DoModal();

}
