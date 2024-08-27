#include"Manager.h"
using namespace std;


Manager::Manager() {
	//文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open()) {
		cout << "文件不存在！" << endl;
		this->worker_num = 0;
		this->workerArray = NULL;
		this->flagFile = true;
		ifs.close();
		return;
	}
	//文件存在，但为空
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout << "文件为空！" << endl;
		this->worker_num = 0;
		this->workerArray = NULL;
		this->flagFile = true;
		ifs.close();
		return;
	}
	//文件存在，且其中有数据
	int num = this->getFileWorker_num();
	cout << "当前职工个数:" << num << endl;
	this->worker_num = num;
	this->workerArray = new Worker * [this->worker_num];//开辟空间，将文件的数据存放在其中
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
	cout << "** 欢迎使用职工管理系统！***" << endl;
	cout << "****** 1、添加联系人 *******" << endl;
	cout << "****** 2、显示联系人 *******" << endl;
	cout << "****** 3、删除联系人 *******" << endl;
	cout << "****** 4、查找联系人 *******" << endl;
	cout << "****** 5、修改联系人 *******" << endl;
	cout << "****** 6、清空联系人 *******" << endl;
	cout << "****** 7、排序联系人 *******" << endl;
	cout << "****** 0、退出联系人 *******" << endl;
	cout << "****************************" << endl;
}
//退出联系人
void Manager::exitSystem(){
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);//强制退出系统
}

//添加职工
void Manager::AddWorker() {
	int add_num = 0;
	cout << "请输入添加职工人数:" << endl;
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
				cout << "请输入第" << i + 1 << "个员工编号:" << endl;
				int id = 0;
				cin >> id;
			   flag = this->Same_work(id);
			   if (!flag) {
				   return;
			   }
			
			cout << "请输入第" << i + 1 << "个员工姓名:" << endl;
			string name;
			cin >> name;
			cout << "请输入第" << i + 1 << "个员工部门编号:" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
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
		cout << "添加职工完成！" << endl;
		delete this->workerArray;
		this->worker_num = size;
		this->workerArray = workers;
		this->flagFile = false;

		this->saveFile();
	}
	else {
		cout << "输入数据有误" << endl;
	}

	system("pause");
	system("cls");
}
//判断职编号是否重复
bool Manager::Same_work(int ID){
	for (int i = 0; i < this->worker_num; i++) {
		if (ID == this->workerArray[i]->m_ID) {
			cout << "职工编号重复" << endl;
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

//显示职工信息
void Manager::show_worker() {
	if (this->flagFile) {
		cout << "文件不存在或为空" << endl;
	}
	else {
		for (int i = 0; i < this->worker_num; i++) {
			this->workerArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}

//判断具体职工是否存在,返回职工id
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

//删除职工
void Manager::Delete_worker(int ID) {
	for (int i = ID; i < this->worker_num - 1; i++) {
		this->workerArray[i] = this->workerArray[i + 1];
	}
	this->worker_num--;
	this->saveFile();
	cout << "删除成功！" << endl;
	system("pause");
	system("cls");
}

//修改职工信息
void Manager::Revise_worker() {
	if (this->flagFile) {
		cout << "文件不存在或为空" << endl;

	}
	else {
		cout << "请输入所要修改职工的编号" << endl;
		int id = 0;
		cin >> id;
		int ret = this->Exist_worker(id);
		if (ret == ERROR) {
			cout << "所要修改的职工不存在！" << endl;
			system("pause");
			system("cls");
		}
		else {
			delete this->workerArray[ret];
			bool flag = false;
			int id = 0;
			string name;
			int deptid = 0;
			cout << "请输入职工的ID: " << endl;
			cin >> id;
			flag = this->Same_work(id);
			if (!flag) {
				return;
			}
			cout << "请输入职工的姓名: " << endl;
			cin >> name;
			cout << "请输入职工的部门ID: " << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
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
			cout << "修改成功！" << endl;
			this->saveFile();

			system("pause");
			system("cls");
		}
	}
}

//查找职工
void Manager::Find_worker(){
	cout << "请输入查找方式: " << endl;
	cout << "1、按职工编号查找 " << endl;
	cout << "2、按职工姓名查找 " << endl;
	int choice = 0;
	cin >> choice;
	switch (choice)
	{
	case 1://按职工编号查找
	{
		cout << "请输入要查找的职工编号: " << endl;
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
			cout << "无编号为" << id << "的职工" << endl;
		}
		break;
	}
	case 2://按职工姓名查找
	{
		cout << "请输入要查找的职工姓名: " << endl;
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
			cout << "无姓名为" << name << "的职工" << endl;
		}
		break;
	}
	default:
		cout << "输入错误" << endl;
		break;
	}
	system("pause");
	system("cls");
}

//职工排序
void Manager::Sort_worker() {
	if (this->flagFile) {
		cout << "文件为空或不存在" << endl;
		system("pause");
		system("cls");
	}
	else {
		cout << "请选择排序方式: " << endl;
		cout << "1、按职工编号升序排序 " << endl;
		cout << "2、按职工编号降序排序 " << endl;
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
			cout << "输入错误" << endl;
			break;
		}
		cout << "排序成功！排序结果为: " << endl;
		this->saveFile();
		this->show_worker();

	}

}

void Manager::Clean_File() {
	cout << "确定清空文件内容？: " << endl;
	cout << "1、确定 " << endl;
	cout << "2、返回 " << endl;
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
			cout << "清空成功！" << endl;

		}

	}
	system("pause");
	system("cls");
}