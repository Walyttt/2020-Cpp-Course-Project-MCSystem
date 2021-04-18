#pragma once


// CTeacherChgpwdDlg 对话框
#include "User.h"

class CChgpwdDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CChgpwdDlg)

public:
	CChgpwdDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CChgpwdDlg();
	User user;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TeacherChgpwd_Dlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CString Edit_newpwd;
	CString Edit_newpwd_verify;
	CButton Button_chg;
public:
	afx_msg void ChgPwd();
};
