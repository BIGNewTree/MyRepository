#include<iostream>
#include<string>
#include"Manager.h"
#include"Worker.h"
using namespace std;



int main() {

	Manager m;
	int choice = 0;
	while (true) {
		m.show_Menu();
		cout << "请进行操作" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0://退出联系人
			m.exitSystem();
			break;
		case 1://添加联系人
			m.AddWorker();
			break;
		case 2://显示联系人
			m.show_worker();
			break;
		case 3://删除联系人
		{
			cout << "请输入所要删除职工的编号" << endl;
			int id;
			cin >> id;
			int ret = m.Exist_worker(id);
			if (ret == ERROR) {
				cout << "所要删除的职工不存在！" << endl;
				system("pause");
				system("cls");
			}
			else {
				m.Delete_worker(ret);
			}
			break;
		}
		case 4://查找联系人
			m.Find_worker();
			break;
		case 5://修改联系人
		{
			m.Revise_worker();
			break;
		}
		case 6://清空联系人
			break;
		case 7://排序联系人
			m.Sort_worker();
			break;
		default:
			cout << "输入有误，请重新输入" << endl;
			system("pause");
			system("cls");//清空回到菜单
			break;
		}


	}
	


	system("pause");
	return 0;
}