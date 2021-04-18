// CQAddDlg.cpp: 实现文件
//

#include "pch.h"
#include "MCESystem.h"
#include "CQAddDlg.h"
#include "afxdialogex.h"
#include "QuestionAndPaper.h"


// CQAddDlg 对话框

IMPLEMENT_DYNAMIC(CQAddDlg, CDialogEx)

CQAddDlg::CQAddDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_QuestionAddDlg, pParent)
	, stem_c(_T(""))
	, option_1_c(_T(""))
	, option_2_c(_T(""))
	, option_3_c(_T(""))
	, option_4_c(_T(""))
{

}

CQAddDlg::~CQAddDlg()
{
}

void CQAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, button_add);
	DDX_Control(pDX, IDC_RADIO1, type_single);
	DDX_Control(pDX, IDC_RADIO2, type_mul);
	DDX_Control(pDX, IDC_RADIO5, level_easy);
	DDX_Control(pDX, IDC_RADIO6, level_normal);
	DDX_Control(pDX, IDC_RADIO7, level_hard);
	DDX_Text(pDX, IDC_EDIT1, stem_c);
	DDX_Text(pDX, IDC_EDIT2, option_1_c);
	DDX_Text(pDX, IDC_EDIT8, option_2_c);
	DDX_Text(pDX, IDC_EDIT9, option_3_c);
	DDX_Text(pDX, IDC_EDIT10, option_4_c);
	DDX_Control(pDX, IDC_CHECK1, answer_1);
	DDX_Control(pDX, IDC_CHECK2, answer_2);
	DDX_Control(pDX, IDC_CHECK3, answer_3);
	DDX_Control(pDX, IDC_CHECK4, answer_4);
}


BEGIN_MESSAGE_MAP(CQAddDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CQAddDlg::Add)
END_MESSAGE_MAP()


// CQAddDlg 消息处理程序


void CQAddDlg::Add()
{
	// TODO: 在此添加控件通知处理程序代码
	//添加题目的按钮

	//同步
	UpdateData(TRUE);

	string stem(CT2A(stem_c.GetString()));
	string option[4]{ CT2A(option_1_c.GetString()),CT2A(option_2_c.GetString()),CT2A(option_3_c.GetString()),CT2A(option_4_c.GetString())};
	int answer[4] = { 0,0,0,0 };
	int type;
	int level;

	//首先判别填写完整
	if (stem.empty() || option[0].empty() || option[1].empty() || option[3].empty() || option[4].empty()) {
		MessageBox(TEXT("请填写完整"));
		return;
	}

	if ((!type_mul.GetCheck() && !type_single.GetCheck()) || (!level_easy.GetCheck() && !level_normal.GetCheck() && !level_hard.GetCheck())) {
		MessageBox(TEXT("请填写完整"));
		return;
	}

	if (!answer_1.GetCheck() && !answer_2.GetCheck() && !answer_3.GetCheck() && !answer_4.GetCheck()) {
		MessageBox(TEXT("请填写完整"));
		return;
	}

	//检测完毕，开始检测是否出现复选框选择情况是否符合题目类型
	//单选题不允许有多个答案，多选题允许只有一个答案
	if(type_single.GetCheck())
		if (!((answer_1.GetCheck() && !answer_2.GetCheck() && !answer_3.GetCheck() && !answer_4.GetCheck()) ||
			(!answer_1.GetCheck() && answer_2.GetCheck() && !answer_3.GetCheck() && !answer_4.GetCheck()) ||
			(!answer_1.GetCheck() && !answer_2.GetCheck() && answer_3.GetCheck() && !answer_4.GetCheck()) ||
			(!answer_1.GetCheck() && !answer_2.GetCheck() && !answer_3.GetCheck() && answer_4.GetCheck())) ) {
			MessageBox(TEXT("题型与答案数量不符！"));
			return;
		}

	//开始添加
	if (answer_1.GetCheck())
		answer[0] = 1;
	if (answer_2.GetCheck())
		answer[1] = 1;
	if (answer_3.GetCheck())
		answer[2] = 1;
	if (answer_4.GetCheck())
		answer[3] = 1;

	if (type_single.GetCheck())
		type = 0;
	else
		type = 1;

	if (level_easy.GetCheck())
		level = 1;
	else if (level_normal.GetCheck())
		level = 2;
	else
		level = 3;

	Question q(stem, option, answer, type, level);

	q.Add();
	MessageBox(TEXT("添加成功"));
	this->EndDialog(0);
	return;

}
