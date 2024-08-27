#include"Manager.h"
using namespace std;


Manager::Manager() {
	//�ļ�������
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open()) {
		cout << "�ļ������ڣ�" << endl;
		this->worker_num = 0;
		this->workerArray = NULL;
		this->flagFile = true;
		ifs.close();
		return;
	}
	//�ļ����ڣ���Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout << "�ļ�Ϊ�գ�" << endl;
		this->worker_num = 0;
		this->workerArray = NULL;
		this->flagFile = true;
		ifs.close();
		return;
	}
	//�ļ����ڣ�������������
	int num = this->getFileWorker_num();
	cout << "��ǰְ������:" << num << endl;
	this->worker_num = num;
	this->workerArray = new Worker * [this->worker_num];//���ٿռ䣬���ļ������ݴ��������
	this->init_worker();
	//this->worker_num = 0;
	//this->workerArray = NULL;
}
Manager::~Manager() {
	if (this->workerArray != NULL) {
		for (int i = 0; i < this->worker_num; i++) {
			if (this->workerArray[i] != 0) {
				delete this->workerArray[i];
				this->workerArray[i] = NULL;
			}
		}
		delete[] this->workerArray;
		this->workerArray = NULL;
	}
}
void Manager::show_Menu() {
	cout << "****************************" << endl;
	cout << "** ��ӭʹ��ְ������ϵͳ��***" << endl;
	cout << "****** 1�������ϵ�� *******" << endl;
	cout << "****** 2����ʾ��ϵ�� *******" << endl;
	cout << "****** 3��ɾ����ϵ�� *******" << endl;
	cout << "****** 4��������ϵ�� *******" << endl;
	cout << "****** 5���޸���ϵ�� *******" << endl;
	cout << "****** 6�������ϵ�� *******" << endl;
	cout << "****** 7��������ϵ�� *******" << endl;
	cout << "****** 0���˳���ϵ�� *******" << endl;
	cout << "****************************" << endl;
}
//�˳���ϵ��
void Manager::exitSystem(){
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);//ǿ���˳�ϵͳ
}

//���ְ��
void Manager::AddWorker() {
	int add_num = 0;
	cout << "���������ְ������:" << endl;
	cin >> add_num;
	if (add_num > 0) {
		int size = this->worker_num + add_num;
		Worker** workers = new Worker * [size];
		if (this->workerArray != NULL) {
			for (int i = 0; i < this->worker_num; i++) {
				workers[i] = this->workerArray[i];
			}
		}

		for(int i =0;i<add_num;i++){
			bool flag = false;
				cout << "�������" << i + 1 << "��Ա�����:" << endl;
				int id = 0;
				cin >> id;
			   flag = this->Same_work(id);
			   if (!flag) {
				   return;
			   }
			
			cout << "�������" << i + 1 << "��Ա������:" << endl;
			string name;
			cin >> name;
			cout << "�������" << i + 1 << "��Ա�����ű��:" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
			int dept_id;
			cin >> dept_id;

			Worker* worker = NULL;
			switch (dept_id)
			{
			case 1:
				worker = new Employee(id, name, dept_id);
				break;
			case 2:
				worker = new Manger(id, name, dept_id);
				break;
			case 3:
				worker = new Boss(id, name, dept_id);
				break;
			default:
				break;
			}
			workers[this->worker_num + i] = worker;
		}
		cout << "���ְ����ɣ�" << endl;
		delete this->workerArray;
		this->worker_num = size;
		this->workerArray = workers;
		this->flagFile = false;

		this->saveFile();
	}
	else {
		cout << "������������" << endl;
	}

	system("pause");
	system("cls");
}
//�ж�ְ����Ƿ��ظ�
bool Manager::Same_work(int ID){
	for (int i = 0; i < this->worker_num; i++) {
		if (ID == this->workerArray[i]->m_ID) {
			cout << "ְ������ظ�" << endl;
			return false;
		}
		return true;
	}
}


void Manager::saveFile() {
	ofstream ofs;
	ofs.open(FILENAME,ios::out);

	for (int i = 0; i < this->worker_num; i++) {
		ofs << this->workerArray[i]->m_ID << "  "
			<< this->workerArray[i]->m_Name << "  "
			<< this->workerArray[i]->m_DepartmentID << endl;
	}
	ofs.close();
}
int Manager::getFileWorker_num() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int deptid;
	int num = 0;
	while (ifs>>id && ifs>>name && ifs>>deptid) {
		num++;
	}
	return num;
}
void Manager::init_worker() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int deptid;
	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> deptid) {
		Worker* worker = NULL;
		if (deptid == 1) {
			worker = new Employee(id, name, deptid);
		}
		else if (deptid == 2) {
			worker = new Manger(id, name, deptid);
		}
		else if (deptid == 3) {
			worker = new Boss(id, name, deptid);
		}
		this->workerArray[index] = worker;
		index++;
	}
	ifs.close();
}

//��ʾְ����Ϣ
void Manager::show_worker() {
	if (this->flagFile) {
		cout << "�ļ������ڻ�Ϊ��" << endl;
	}
	else {
		for (int i = 0; i < this->worker_num; i++) {
			this->workerArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}

//�жϾ���ְ���Ƿ����,����ְ��id
int Manager::Exist_worker(int id) {
	if (this->flagFile) {
		return ERROR;
	}
	else {
		for (int i = 0; i < this->worker_num;i++) {
			if (this->workerArray[i]->m_ID == id) {
				return i;
			}
		}
		return ERROR;
	}
}

//ɾ��ְ��
void Manager::Delete_worker(int ID) {
	for (int i = ID; i < this->worker_num - 1; i++) {
		this->workerArray[i] = this->workerArray[i + 1];
	}
	this->worker_num--;
	this->saveFile();
	cout << "ɾ���ɹ���" << endl;
	system("pause");
	system("cls");
}

//�޸�ְ����Ϣ
void Manager::Revise_worker() {
	if (this->flagFile) {
		cout << "�ļ������ڻ�Ϊ��" << endl;

	}
	else {
		cout << "��������Ҫ�޸�ְ���ı��" << endl;
		int id = 0;
		cin >> id;
		int ret = this->Exist_worker(id);
		if (ret == ERROR) {
			cout << "��Ҫ�޸ĵ�ְ�������ڣ�" << endl;
			system("pause");
			system("cls");
		}
		else {
			delete this->workerArray[ret];
			bool flag = false;
			int id = 0;
			string name;
			int deptid = 0;
			cout << "������ְ����ID: " << endl;
			cin >> id;
			flag = this->Same_work(id);
			if (!flag) {
				return;
			}
			cout << "������ְ��������: " << endl;
			cin >> name;
			cout << "������ְ���Ĳ���ID: " << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
			cin >> deptid;
			Worker* worker = NULL;
			switch (deptid)
			{
			case 1:
				worker = new Employee(id, name, deptid);
				break;
			case 2:
				worker = new Manger(id, name, deptid);
				break;
			case 3:
				worker = new Boss(id, name, deptid);
				break;
			default:
				break;
			}
			this->workerArray[ret] = worker;
			cout << "�޸ĳɹ���" << endl;
			this->saveFile();

			system("pause");
			system("cls");
		}
	}
}

//����ְ��
void Manager::Find_worker(){
	cout << "��������ҷ�ʽ: " << endl;
	cout << "1����ְ����Ų��� " << endl;
	cout << "2����ְ���������� " << endl;
	int choice = 0;
	cin >> choice;
	switch (choice)
	{
	case 1://��ְ����Ų���
	{
		cout << "������Ҫ���ҵ�ְ�����: " << endl;
		int id;
		cin >> id;
		bool flag = false;
		for (int i = 0; i < this->worker_num; i++) {
			if (id == this->workerArray[i]->m_ID) {
				this->workerArray[i]->showInfo();
				flag = true;
				break;
			}
		}
		if (!flag) {
			cout << "�ޱ��Ϊ" << id << "��ְ��" << endl;
		}
		break;
	}
	case 2://��ְ����������
	{
		cout << "������Ҫ���ҵ�ְ������: " << endl;
		string name;
		cin >> name;
		bool flag = false;
		for (int i = 0; i < this->worker_num; i++) {
			if (name == this->workerArray[i]->m_Name) {
				this->workerArray[i]->showInfo();
				flag = true;
			}
		}
		if (!flag) {
			cout << "������Ϊ" << name << "��ְ��" << endl;
		}
		break;
	}
	default:
		cout << "�������" << endl;
		break;
	}
	system("pause");
	system("cls");
}

//ְ������
void Manager::Sort_worker() {
	if (this->flagFile) {
		cout << "�ļ�Ϊ�ջ򲻴���" << endl;
		system("pause");
		system("cls");
	}
	else {
		cout << "��ѡ������ʽ: " << endl;
		cout << "1����ְ������������� " << endl;
		cout << "2����ְ����Ž������� " << endl;
		int choice = 0;
		cin >> choice;
		switch (choice)
		{
		case 1: 
		{
			for (int j = 0; j < this->worker_num; j++) {
				int min = j;
				for (int i = j+1; i < this->worker_num; i++) {
					if (this->workerArray[min]->m_ID > this->workerArray[i]->m_ID) {
						min = i;
					}
				}
				if (min != j) {
					Worker* temp = this->workerArray[min];
					this->workerArray[min] = this->workerArray[j];
					this->workerArray[j] = temp;
				}
			}
			this->saveFile();
			break;
		}
		case 2:
		{
			for (int j = 0; j < this->worker_num; j++) {
				int max = j;
				for (int i = j + 1; i < this->worker_num; i++) {
					if (this->workerArray[max]->m_ID < this->workerArray[i]->m_ID) {
						max = i;
					}
				}
				if (max != j) {
					Worker* temp = this->workerArray[max];
					this->workerArray[max] = this->workerArray[j];
					this->workerArray[j] = temp;
				}
			}
			break;
		}
		default:
			cout << "�������" << endl;
			break;
		}
		cout << "����ɹ���������Ϊ: " << endl;
		this->saveFile();
		this->show_worker();

	}

}

void Manager::Clean_File() {
	cout << "ȷ������ļ����ݣ�: " << endl;
	cout << "1��ȷ�� " << endl;
	cout << "2������ " << endl;
	int choice = 0;
	cin >> choice;
	if (choice == 1) {
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();
		if (this->workerArray != NULL) {
			for (int i = 0; i < this->worker_num; i++) {
				if (this->workerArray[i] != 0) {
					delete this->workerArray[i];
					this->workerArray[i] = NULL;
				}
			}
			delete[] this->workerArray;
			this->workerArray = NULL;
			this->worker_num = 0;
			this->flagFile = true;
			cout << "��ճɹ���" << endl;

		}

	}
	system("pause");
	system("cls");
}