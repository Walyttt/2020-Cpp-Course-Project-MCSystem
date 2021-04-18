#pragma once

#include<list>
#include<fstream>
#include<iostream>
#include<string>
#include<direct.h>
#include<io.h>

#define _F_LOGIN "D:\\TestSystem\\UserLib.txt"	//�˻��ļ�·��
#define _D_Student "D:\\TestSystem\\Student\\"
#define _D_Teacher "D:\\TestSystem\\Teacher\\"

using namespace std;

class User
{
public:
	string name;
	string id;
	string pwd;
	string identity;  //AΪ����Ա��SΪѧ����TΪ��ʦ

	User(string id = "", string pwd = "", string name = "", string identity = "");
	int Login();	//����ֵ�����-1Ϊ��¼ʧ�ܣ�1Ϊѧ����2Ϊ��ʦ
	int Register();	//����ֵ�����0Ϊ�����û���ע��ʧ�ܣ�1Ϊע��ɹ�
	void Delete();	//�޷���ֵ
	void Chg_pwd(string new_pwd);

};

