// CQManagementDlg.cpp: 实现文件
//

#include "pch.h"
#include "MCESystem.h"
#include "CQManagementDlg.h"
#include "afxdialogex.h"
#include "CQAddDlg.h"
#include "QuestionAndPaper.h"


// CQManagementDlg 对话框

IMPLEMENT_DYNAMIC(CQManagementDlg, CDialogEx)

CQManagementDlg::CQManagementDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_QuestionManageDlg, pParent)
{

}

CQManagementDlg::~CQManagementDlg()
{
}

void CQManagementDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO1, type_single);
	DDX_Control(pDX, IDC_RADIO2, type_mul);
	DDX_Control(pDX, IDC_RADIO5, level_easy);
	DDX_Control(pDX, IDC_RADIO6, level_normal);
	DDX_Control(pDX, IDC_RADIO7, level_hard);
	DDX_Control(pDX, IDC_LIST1, list_q);
	DDX_Control(pDX, IDC_BUTTON3, button_add);
	DDX_Control(pDX, IDC_BUTTON4, button_delete);
	DDX_Control(pDX, IDC_BUTTON1, button_inquire);

	CString head[] = { TEXT("题干"), TEXT("选项A"), TEXT("选项B"), TEXT("选项C"), TEXT("选项D"), TEXT("正确答案") };
	for (int i = 0; i < 6; i++)
		list_q.InsertColumn(i, head[i], LVCFMT_LEFT, 250);
}


BEGIN_MESSAGE_MAP(CQManagementDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON3, &CQManagementDlg::AddQuestion)
	ON_BN_CLICKED(IDC_BUTTON1, &CQManagementDlg::Inquire)
	ON_BN_CLICKED(IDC_BUTTON4, &CQManagementDlg::DeleteQuestion)
END_MESSAGE_MAP()


// CQManagementDlg 消息处理程序


void CQManagementDlg::AddQuestion()
{
	// TODO: 在此添加控件通知处理程序代码
	//跳转至添加题目页面
	CQAddDlg add_dlg;
	add_dlg.DoModal();
}




void CQManagementDlg::Inquire()
{
	// TODO: 在此添加控件通知处理程序代码
	//根据选项插入题目

	//先判断查询类型是否完整
	if (!type_single.GetCheck() && !type_mul.GetCheck()) {
		MessageBox(TEXT("请选择题型"));
		return;
	}

	if (!level_easy.GetCheck() && !level_normal.GetCheck() && !level_hard.GetCheck()) {
		MessageBox(TEXT("请选择难度"));
		return;
	}

	//清空列表
	list_q.DeleteAllItems();

	//根据所选类型打开文件
	ifstream infile;
	if (type_single.GetCheck()) {
		if (level_easy.GetCheck())
			infile.open(_F_SQE);
		if (level_normal.GetCheck())
			infile.open(_F_SQN);
		if (level_hard.GetCheck())
			infile.open(_F_SQH);
	}
	else {
		if (level_easy.GetCheck())
			infile.open(_F_MQE);
		if (level_normal.GetCheck())
			infile.open(_F_MQN);
		if (level_hard.GetCheck())
			infile.open(_F_MQH);
	}

	//开始读取
	int q_num;	//题目总数

	infile >> q_num;
	infile.get();

	for (int i = 0; i < q_num; i++) {
		//每行格式为  "stem|A|B|C|D|answer"
		char buf[1024] = { 0 };
		infile.getline(buf, sizeof(buf));

		CString stem(strtok(buf, "|"));//开始切割
		CString option_1(strtok(NULL, "|"));
		CString option_2(strtok(NULL, "|"));
		CString option_3(strtok(NULL, "|"));
		CString option_4(strtok(NULL, "|"));
		CString answer_num(strtok(NULL, "|"));

		CString answer = TEXT("");
		if (answer_num[0] == '1')
			answer += TEXT("A");
		if (answer_num[1] == '1')
			answer += TEXT("B");
		if (answer_num[2] == '1')
			answer += TEXT("C");
		if (answer_num[3] == '1')
			answer += TEXT("D");

		list_q.InsertItem(i, stem);
		list_q.SetItemText(i, 1, option_1);
		list_q.SetItemText(i, 2, option_2);
		list_q.SetItemText(i, 3, option_3);
		list_q.SetItemText(i, 4, option_4);
		list_q.SetItemText(i, 5, answer);
	}
	//设置列表风格
	list_q.SetExtendedStyle(list_q.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//关闭文件
	infile.close();
}


void CQManagementDlg::DeleteQuestion()
{
	// TODO: 在此添加控件通知处理程序代码
	//删除选中
	int nId;

	POSITION pos = list_q.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(TEXT("请至少选择一项"), TEXT("提示"), MB_ICONEXCLAMATION);
		return;
	}

	//提示是否确认删除
	if (MessageBox(TEXT("确认删除？"), TEXT("提示"), MB_OKCANCEL) == IDOK) {
		//得到行号，通过POSITION转化并得到待删除题目
		nId = (int)list_q.GetNextSelectedItem(pos);

		Question q;
		//设置待删除题目类型和难度
		if (type_single.GetCheck())
			q.setType(0);
		else
			q.setType(1);

		if (level_easy.GetCheck())
			q.setLevel(1);
		else if (level_normal.GetCheck())
			q.setLevel(2);
		else
			q.setLevel(3);

		q.Delete(nId);		
	}
	list_q.DeleteAllItems();
	this->Inquire();
	return;
}
