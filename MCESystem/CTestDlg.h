#pragma once

#include "QuestionAndPaper.h"
#include "User.h"
// CTestDlg 对话框

class CTestDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTestDlg)

public:
	CTestDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CTestDlg();
	Paper paper;
	User stu;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TestDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	int counter;			//题数记录
	int **Stu_answer;
	CStatic Text_stem;
	CButton Check_option1;
	CButton Check_option2;
	CButton Check_option3;
	CButton Check_option4;
	CButton Button_previous;
	CButton Button_next;
	CStatic Text_prompt;
public:
	afx_msg void Next();
	afx_msg void Previous();
	afx_msg void SelectOptionA();
	afx_msg void SelectOptionB();
	afx_msg void SelectOptionC();
	afx_msg void SelectOptionD();

};
