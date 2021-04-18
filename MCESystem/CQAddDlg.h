#pragma once


// CQAddDlg 对话框

class CQAddDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CQAddDlg)

public:
	CQAddDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CQAddDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_QuestionAddDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CButton button_add;
	CButton type_single;
	CButton type_mul;
	CButton level_easy;
	CButton level_normal;
	CButton level_hard;
	CString stem_c;
	CString option_1_c;
	CString option_2_c;
	CString option_3_c;
	CString option_4_c;
	CButton answer_1;
	CButton answer_2;
	CButton answer_3;
	CButton answer_4;

public:
	afx_msg void Add();
};
