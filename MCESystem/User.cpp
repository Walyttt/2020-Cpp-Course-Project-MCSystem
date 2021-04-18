#include"User.h"

User::User(string id, string pwd, string name, string identity) {
	this->id = id;
	this->pwd = pwd;
	this->name = name;
	this->identity = identity;
}

int User::Login() {
	ifstream file;		//指向用户文件
	int usernum;	//用户总数
	int status = -1;		//返回值

	//对管理员账户特殊判断
	if (this->id == "Admin"&&this->pwd == "000000")
		return 0;

	file.open(_F_LOGIN);
	file >> usernum;
	file.get();

	while (usernum--) {
		//每行格式为  "id|pwd|name|identity"
		char buf[1024] = { 0 };
		file.getline(buf, sizeof(buf));


		char *id_temp = strtok(buf, "|");//开始切割
		char *pwd_temp = strtok(NULL, "|");
		char *name_temp = strtok(NULL, "|");
		char *identity_temp = strtok(NULL, "|");

		if (!(strcmp((this->id).c_str(), id_temp))) { //账号匹配
			if (!(strcmp((this->pwd).c_str(), pwd_temp))) {	//密码也匹配
				this->name = name_temp;
				this->identity = identity_temp;
				status = (!strcmp(identity_temp, "S")) ? 1 : 2;
				break;
			}
			else
				break;
		}
	}
	file.close();
	return status;
}

int User::Register() {
	fstream file;		//指向用户文件
	int usernum;	//用户总数
	int status = -1;		//返回值

	//对管理员账户特殊判断
	if (this->id == "Admin"&&this->pwd == "000000")
		return 0;

	//开始检测是否已存在用户
	file.open(_F_LOGIN, ios::in | ios::out);
	file >> usernum;
	file.get();

	for (int i = 0; i < usernum; i++) {
		//每行格式为  "id|pwd|name|identity"
		char buf[1024] = { 0 };
		file.getline(buf, sizeof(buf));


		char *id_temp = strtok(buf, "|");//开始切割
		char *pwd_temp = strtok(NULL, "|");
		char *name_temp = strtok(NULL, "|");
		char *identity_temp = strtok(NULL, "|");

		if (!(strcmp((this->id).c_str(), id_temp))) {	//找到相同账号，注册失败退出
			file.close();
			return 0;
		}	
	}

	//没有找到相同账号，可以注册
	file.seekp(ios::beg);
	file << (++usernum) << endl;
	file.seekp(0, ios::end);
	file << this->id << '|' << this->pwd << '|' << this->name << '|' << this->identity << endl;
	file.close();

	//创建用户目录
	if (!strcmp((this->identity).c_str(), "T")) {
		char dir[1024] = _D_Teacher;
		strcat(dir, this->id.c_str());
		_mkdir(dir);

		strcat(dir, "\\PaperList.txt");
		file.open(dir, ios::out);
		file << '0' << endl;
		file.close();
	}
	else {
		char dir[1024] = _D_Student;
		strcat(dir, this->id.c_str());
		_mkdir(dir);

		//记录文件
		strcat(dir, "\\log.txt");
		file.open(dir, ios::out);
		file << '0' << endl;
		file.close();

		//错题本文件
		strcpy(dir, _D_Student);
		strcat(dir, this->id.c_str());
		strcat(dir, "\\WrongCollection.txt");
		file.open(dir, ios::out);
		file << '0' << endl;
		file.close();

	}

	return 1;
	
}

void User::Delete() {
	ifstream file_in;		//指向用户文件
	int usernum;			//用户总数
	int user_to_delete;		//所删除用户的行数
	char buf[1024][1024] = { 0 }, buf_to_save[1024][1024] = { 0 };	//buf_to_save作为不进行切割的完整用户列表
	int i = 0;

	//开始检测是否已存在用户
	file_in.open(_F_LOGIN, ios::in);
	file_in >> usernum;
	file_in.get();

	for (i = 0; i < usernum; i++) {
		//寻找待删除用户行数
		//每行格式为  "id|pwd|name|identity"
		file_in.getline(buf[i], sizeof(buf[i]));
		strcpy(buf_to_save[i], buf[i]);

		char *id_temp = strtok(buf[i], "|");//切割出账号用于比较

		if (!(strcmp((this->id).c_str(), id_temp))) {//找到用户信息所在行,记录行数
			user_to_delete = i;
			usernum--;
			break;
		}	
	}

	//找到待删除用户后，读取剩余用户列表
	for (++i; i < usernum + 1; i++)
		file_in.getline(buf_to_save[i], sizeof(buf_to_save[i]));
	file_in.close();

	//开始重新写用户文件
 	ofstream file_out;
	file_out.open(_F_LOGIN);
	file_out << usernum << endl;
	for (i = 0; i < usernum + 1; i++) {
		if (i != user_to_delete)
			file_out << buf_to_save[i]<<endl;
	}
	file_out.close();

	//删除用户目录
	if (buf_to_save[user_to_delete][strlen(buf_to_save[user_to_delete] - 1) ] == 'T') {
		char path[1024] = _D_Teacher;
		strcat(path, this->id.c_str());
		strcat(path, "\\PaperList.txt");
		remove(path);

		strcpy(path, _D_Teacher);
		strcat(path, this->id.c_str());
		_rmdir(path);


	}
	else {
		char path[1024] = _D_Student;
		strcat(path, this->id.c_str());
		strcat(path, "\\log.txt");
		remove(path);

		strcpy(path, _D_Student);
		strcat(path, this->id.c_str());
		strcat(path, "\\WrongCollection.txt");
		remove(path);

		strcpy(path, _D_Student);
		strcat(path, this->id.c_str());
		_rmdir(path);
	}
}


void User::Chg_pwd(string new_pwd) {
	ifstream file_in;		//指向用户文件
	int usernum;			//用户总数
	int user_to_chg;		//目标用户的行数
	char buf[1024][1024] = { 0 }, buf_to_save[1024][1024] = { 0 };	//buf_to_save作为不进行切割的完整用户列表
	int i = 0;

	//开始查找用户
	file_in.open(_F_LOGIN, ios::in);
	file_in >> usernum;
	file_in.get();

	for (i = 0; i < usernum; i++) {
		//寻找待修改用户行数
		//每行格式为  "id|pwd|name|identity"
		file_in.getline(buf[i], sizeof(buf[i]));
		strcpy(buf_to_save[i], buf[i]);

		char *id_temp = strtok(buf[i], "|");//切割出账号用于比较

		if (!(strcmp((this->id).c_str(), id_temp))) {//找到用户信息所在行,记录行数
			user_to_chg = i;
			break;
		}
	}

	//找到待修改用户后，读取剩余用户列表
	for (++i; i < usernum ; i++)
		file_in.getline(buf_to_save[i], sizeof(buf_to_save[i]));
	file_in.close();

	//开始重新写用户文件
	ofstream file_out;
	file_out.open(_F_LOGIN);
	file_out << usernum << endl;
	for (i = 0; i < usernum ; i++) {
		if (i != user_to_chg)
			file_out << buf_to_save[i] << endl;
		else
			file_out << this->id << '|' << new_pwd << '|' << this->name << '|' << this->identity;
	}
	file_out.close();
}