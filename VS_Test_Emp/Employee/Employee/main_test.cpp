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
		cout << "����в���" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0://�˳���ϵ��
			m.exitSystem();
			break;
		case 1://�����ϵ��
			m.AddWorker();
			break;
		case 2://��ʾ��ϵ��
			m.show_worker();
			break;
		case 3://ɾ����ϵ��
		{
			cout << "��������Ҫɾ��ְ���ı��" << endl;
			int id;
			cin >> id;
			int ret = m.Exist_worker(id);
			if (ret == ERROR) {
				cout << "��Ҫɾ����ְ�������ڣ�" << endl;
				system("pause");
				system("cls");
			}
			else {
				m.Delete_worker(ret);
			}
			break;
		}
		case 4://������ϵ��
			m.Find_worker();
			break;
		case 5://�޸���ϵ��
		{
			m.Revise_worker();
			break;
		}
		case 6://�����ϵ��
			break;
		case 7://������ϵ��
			m.Sort_worker();
			break;
		default:
			cout << "������������������" << endl;
			system("pause");
			system("cls");//��ջص��˵�
			break;
		}


	}
	


	system("pause");
	return 0;
}