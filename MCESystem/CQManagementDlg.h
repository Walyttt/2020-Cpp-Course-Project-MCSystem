#pragma once


// CQManagementDlg 对话框

class CQManagementDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CQManagementDlg)

public:
	CQManagementDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CQManagementDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_QuestionManageDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	CButton type_single;
	CButton type_mul;
	CButton level_easy;
	CButton level_normal;
	CButton level_hard;
	CListCtrl list_q;
	CButton button_add;
	CButton button_delete;
	CButton button_inquire;
public:
	afx_msg void AddQuestion();
	afx_msg void Inquire();
	afx_msg void DeleteQuestion();
};
