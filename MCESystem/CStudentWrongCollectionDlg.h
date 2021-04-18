#pragma once

#include "User.h"
// CStudentWrongCollectionDlg 对话框

typedef struct {
	string stem;
	string option[4];
	char answer[4];
}WQuestion;

class CStudentWrongCollectionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CStudentWrongCollectionDlg)

public:
	CStudentWrongCollectionDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CStudentWrongCollectionDlg();
	User stu;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WrongCollDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CStatic Edit_Stem;
	CButton Radio_option[4];
	CButton Button_next;
	CButton Button_previous;
	WQuestion *W;
public:
	afx_msg void Next();
	afx_msg void Previous();
};
