#pragma once

#include "User.h"
// CStudentLogDlg 对话框

class CStudentLogDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CStudentLogDlg)

public:
	CStudentLogDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CStudentLogDlg();
	User stu;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_StudentLogDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CListCtrl List_log;
};
