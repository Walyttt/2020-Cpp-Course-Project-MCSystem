#pragma once

#include "User.h"
// CTeacherDlg 对话框

class CTeacherDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTeacherDlg)

public:
	User user;
	CTeacherDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CTeacherDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TeacherDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()


private:
	CStatic Edit_username;
	CButton Button_manage;
	CButton Button_chgpwd;
	CButton Button_createpaper;
	CComboBox Combo_paper;
	CEdit Edit_SinCount;
	CEdit Edit_MulCount;
	CEdit Edit_TotalScore;
	CListCtrl List_StuScore;

public:
	afx_msg void ManageQuestion();
	afx_msg void ChangePwd();
	afx_msg void CreatePaper();
	afx_msg void CheckResult();
};
