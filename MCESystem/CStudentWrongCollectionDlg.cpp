// CStudentWrongCollectionDlg.cpp: 实现文件
//

#include "pch.h"
#include "MCESystem.h"
#include "CStudentWrongCollectionDlg.h"
#include "afxdialogex.h"

int counter;
int num;
// CStudentWrongCollectionDlg 对话框

IMPLEMENT_DYNAMIC(CStudentWrongCollectionDlg, CDialogEx)

CStudentWrongCollectionDlg::CStudentWrongCollectionDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WrongCollDlg, pParent)
{

}

CStudentWrongCollectionDlg::~CStudentWrongCollectionDlg()
{
}

void CStudentWrongCollectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_StemTEXT, Edit_Stem);
	DDX_Control(pDX, IDC_RADIO1, Radio_option[0]);
	DDX_Control(pDX, IDC_RADIO2, Radio_option[1]);
	DDX_Control(pDX, IDC_RADIO6, Radio_option[2]);
	DDX_Control(pDX, IDC_RADIO7, Radio_option[3]);
	DDX_Control(pDX, IDC_BUTTON2, Button_next);
	DDX_Control(pDX, IDC_BUTTON1, Button_previous);

	//从文件中读错题
	ifstream file;
	char path[1024];

	strcpy(path, _D_Student);
	strcat(path, this->stu.id.c_str());
	strcat(path, "//WrongCollection.txt");

	file.open(path);
	file >> num;
	file.get();

	if (num != 0) {		//错题本内有题
		W = new WQuestion[num];
		for (int i = 0; i < num; i++) {
			char buf[1024];
			file.getline(buf, sizeof(buf));

			W[i].stem = strtok(buf, "|");
			for (int j = 0; j < 4; j++)
				W[i].option[j] = strtok(NULL, "|");

			strcpy(W[i].answer, strtok(NULL, "|"));
		}

		file.close();

		//设置选项不可变
		for (int i = 0; i < 4; i++)
			Radio_option[i].EnableWindow(FALSE);

		//给出第一题
		counter = 0;

		CString Cstem(W[counter].stem.c_str());
		Edit_Stem.SetWindowTextW(Cstem);

		for (int i = 0; i < 4; i++) {
			CString Coption(W[counter].option[i].c_str());
			Radio_option[i].SetWindowTextW(Coption);
			if (W[counter].answer[i] == '1')
				Radio_option[i].SetCheck(BST_CHECKED);
			else
				Radio_option[i].SetCheck(BST_UNCHECKED);
		}
	}

	else {	//错题本内无题
		file.close();
		MessageBox(TEXT("无错题记录"));
		this->EndDialog(0);
	}
}


BEGIN_MESSAGE_MAP(CStudentWrongCollectionDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CStudentWrongCollectionDlg::Next)
	ON_BN_CLICKED(IDC_BUTTON1, &CStudentWrongCollectionDlg::Previous)
END_MESSAGE_MAP()


// CStudentWrongCollectionDlg 消息处理程序


void CStudentWrongCollectionDlg::Next()
{
	// TODO: 在此添加控件通知处理程序代码
	//下一题
	counter++;
	if (counter == num)
		counter = 0;

	CString Cstem(W[counter].stem.c_str());
	Edit_Stem.SetWindowTextW(Cstem);

	for (int i = 0; i < 4; i++) {
		CString Coption(W[counter].option[i].c_str());
		Radio_option[i].SetWindowTextW(Coption);
		if (W[counter].answer[i] == '1')
			Radio_option[i].SetCheck(BST_CHECKED);
		else
			Radio_option[i].SetCheck(BST_UNCHECKED);
	}
}


void CStudentWrongCollectionDlg::Previous()
{
	// TODO: 在此添加控件通知处理程序代码
	counter--;
	if (counter < 0)
		counter = num-1;

	CString Cstem(W[counter].stem.c_str());
	Edit_Stem.SetWindowTextW(Cstem);

	for (int i = 0; i < 4; i++) {
		CString Coption(W[counter].option[i].c_str());
		Radio_option[i].SetWindowTextW(Coption);
		if (W[counter].answer[i] == '1')
			Radio_option[i].SetCheck(BST_CHECKED);
		else
			Radio_option[i].SetCheck(BST_UNCHECKED);
	}
}
