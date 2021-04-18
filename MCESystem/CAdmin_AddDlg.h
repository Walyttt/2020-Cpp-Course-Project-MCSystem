#pragma once


// CAdmin_AddDlg 对话框

class CAdmin_AddDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAdmin_AddDlg)

public:
	CAdmin_AddDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CAdmin_AddDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Admin_Adddlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CString user_id;
	CString user_pwd;
	CString user_name;
	CButton as_tec;
	CButton as_stu;
	CButton button_add;
public:
	afx_msg void Add();
};
