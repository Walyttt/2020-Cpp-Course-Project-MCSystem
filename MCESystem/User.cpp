#include"User.h"

User::User(string id, string pwd, string name, string identity) {
	this->id = id;
	this->pwd = pwd;
	this->name = name;
	this->identity = identity;
}

int User::Login() {
	ifstream file;		//ָ���û��ļ�
	int usernum;	//�û�����
	int status = -1;		//����ֵ

	//�Թ���Ա�˻������ж�
	if (this->id == "Admin"&&this->pwd == "000000")
		return 0;

	file.open(_F_LOGIN);
	file >> usernum;
	file.get();

	while (usernum--) {
		//ÿ�и�ʽΪ  "id|pwd|name|identity"
		char buf[1024] = { 0 };
		file.getline(buf, sizeof(buf));


		char *id_temp = strtok(buf, "|");//��ʼ�и�
		char *pwd_temp = strtok(NULL, "|");
		char *name_temp = strtok(NULL, "|");
		char *identity_temp = strtok(NULL, "|");

		if (!(strcmp((this->id).c_str(), id_temp))) { //�˺�ƥ��
			if (!(strcmp((this->pwd).c_str(), pwd_temp))) {	//����Ҳƥ��
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
	fstream file;		//ָ���û��ļ�
	int usernum;	//�û�����
	int status = -1;		//����ֵ

	//�Թ���Ա�˻������ж�
	if (this->id == "Admin"&&this->pwd == "000000")
		return 0;

	//��ʼ����Ƿ��Ѵ����û�
	file.open(_F_LOGIN, ios::in | ios::out);
	file >> usernum;
	file.get();

	for (int i = 0; i < usernum; i++) {
		//ÿ�и�ʽΪ  "id|pwd|name|identity"
		char buf[1024] = { 0 };
		file.getline(buf, sizeof(buf));


		char *id_temp = strtok(buf, "|");//��ʼ�и�
		char *pwd_temp = strtok(NULL, "|");
		char *name_temp = strtok(NULL, "|");
		char *identity_temp = strtok(NULL, "|");

		if (!(strcmp((this->id).c_str(), id_temp))) {	//�ҵ���ͬ�˺ţ�ע��ʧ���˳�
			file.close();
			return 0;
		}	
	}

	//û���ҵ���ͬ�˺ţ�����ע��
	file.seekp(ios::beg);
	file << (++usernum) << endl;
	file.seekp(0, ios::end);
	file << this->id << '|' << this->pwd << '|' << this->name << '|' << this->identity << endl;
	file.close();

	//�����û�Ŀ¼
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

		//��¼�ļ�
		strcat(dir, "\\log.txt");
		file.open(dir, ios::out);
		file << '0' << endl;
		file.close();

		//���Ȿ�ļ�
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
	ifstream file_in;		//ָ���û��ļ�
	int usernum;			//�û�����
	int user_to_delete;		//��ɾ���û�������
	char buf[1024][1024] = { 0 }, buf_to_save[1024][1024] = { 0 };	//buf_to_save��Ϊ�������и�������û��б�
	int i = 0;

	//��ʼ����Ƿ��Ѵ����û�
	file_in.open(_F_LOGIN, ios::in);
	file_in >> usernum;
	file_in.get();

	for (i = 0; i < usernum; i++) {
		//Ѱ�Ҵ�ɾ���û�����
		//ÿ�и�ʽΪ  "id|pwd|name|identity"
		file_in.getline(buf[i], sizeof(buf[i]));
		strcpy(buf_to_save[i], buf[i]);

		char *id_temp = strtok(buf[i], "|");//�и���˺����ڱȽ�

		if (!(strcmp((this->id).c_str(), id_temp))) {//�ҵ��û���Ϣ������,��¼����
			user_to_delete = i;
			usernum--;
			break;
		}	
	}

	//�ҵ���ɾ���û��󣬶�ȡʣ���û��б�
	for (++i; i < usernum + 1; i++)
		file_in.getline(buf_to_save[i], sizeof(buf_to_save[i]));
	file_in.close();

	//��ʼ����д�û��ļ�
 	ofstream file_out;
	file_out.open(_F_LOGIN);
	file_out << usernum << endl;
	for (i = 0; i < usernum + 1; i++) {
		if (i != user_to_delete)
			file_out << buf_to_save[i]<<endl;
	}
	file_out.close();

	//ɾ���û�Ŀ¼
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
	ifstream file_in;		//ָ���û��ļ�
	int usernum;			//�û�����
	int user_to_chg;		//Ŀ���û�������
	char buf[1024][1024] = { 0 }, buf_to_save[1024][1024] = { 0 };	//buf_to_save��Ϊ�������и�������û��б�
	int i = 0;

	//��ʼ�����û�
	file_in.open(_F_LOGIN, ios::in);
	file_in >> usernum;
	file_in.get();

	for (i = 0; i < usernum; i++) {
		//Ѱ�Ҵ��޸��û�����
		//ÿ�и�ʽΪ  "id|pwd|name|identity"
		file_in.getline(buf[i], sizeof(buf[i]));
		strcpy(buf_to_save[i], buf[i]);

		char *id_temp = strtok(buf[i], "|");//�и���˺����ڱȽ�

		if (!(strcmp((this->id).c_str(), id_temp))) {//�ҵ��û���Ϣ������,��¼����
			user_to_chg = i;
			break;
		}
	}

	//�ҵ����޸��û��󣬶�ȡʣ���û��б�
	for (++i; i < usernum ; i++)
		file_in.getline(buf_to_save[i], sizeof(buf_to_save[i]));
	file_in.close();

	//��ʼ����д�û��ļ�
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