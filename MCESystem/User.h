#pragma once

#include<list>
#include<fstream>
#include<iostream>
#include<string>
#include<direct.h>
#include<io.h>

#define _F_LOGIN "D:\\TestSystem\\UserLib.txt"	//账户文件路径
#define _D_Student "D:\\TestSystem\\Student\\"
#define _D_Teacher "D:\\TestSystem\\Teacher\\"

using namespace std;

class User
{
public:
	string name;
	string id;
	string pwd;
	string identity;  //A为管理员，S为学生，T为教师

	User(string id = "", string pwd = "", string name = "", string identity = "");
	int Login();	//返回值情况：-1为登录失败，1为学生，2为教师
	int Register();	//返回值情况：0为已有用户，注册失败；1为注册成功
	void Delete();	//无返回值
	void Chg_pwd(string new_pwd);

};

