#pragma once


// CTeacherCreatePaperDlg 对话框
#include "User.h"

class CTeacherCreatePaperDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTeacherCreatePaperDlg)

public:
	CTeacherCreatePaperDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CTeacherCreatePaperDlg();
	User user;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TeacherCreatePaper };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CEdit Edit_papername;
	CButton Radio_type_single;
	CButton Radio_type_mul;
	CButton Radio_level_easy;
	CButton Radio_level_normal;
	CButton Radio_level_hard;
	CListCtrl List_question;
	CListCtrl List_question_selected;
	CButton Button_select;
	CButton Button_throw;
	CButton Button_create;


public:
	afx_msg void ClickSingle();
	afx_msg void ClickMul();
	afx_msg void ClickEasy();
	afx_msg void ClickNoraml();
	afx_msg void ClickHard();
	afx_msg void Select();
	afx_msg void Throw();
	afx_msg void Create();

};
