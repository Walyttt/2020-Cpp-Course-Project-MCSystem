#pragma once


// CAdminDlg 对话框

class CAdminDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAdminDlg)

public:
	CAdminDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CAdminDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AdminDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CListCtrl user_list;
	CButton button_add;
	CButton button_delete;
public:
	afx_msg void AddUser();
	afx_msg void DeleteUser();
};
