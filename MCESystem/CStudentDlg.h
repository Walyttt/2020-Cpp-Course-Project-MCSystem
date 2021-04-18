#pragma once

#include "User.h"
// CStudentDlg 对话框

class CStudentDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CStudentDlg)

public:
	CStudentDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CStudentDlg();
	User user;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_StudentDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CStatic Text_username;
	CComboBox Combo_teacher;
	CListCtrl List_paper;
	CButton Button_test;
	CButton Button_Chgpwd;
	CButton Button_WrongCollection;
	CButton Button_log;

public:
	afx_msg void ChgPwd();
	afx_msg void SelectTeacher();
	afx_msg void TestBegin();
	afx_msg void CheckLog();
	afx_msg void CheckWrongCollection();
};
