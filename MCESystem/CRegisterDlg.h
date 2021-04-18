﻿#pragma once


// CRegisterDlg 对话框

class CRegisterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRegisterDlg)

public:
	CRegisterDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CRegisterDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Resgister };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CString user_name;
	CString user_id;
	CString user_pwd;
	CString user_pwd_verify;

public:
	afx_msg void Register();
private:
	CButton as_stu;
	CButton as_tec;
};
