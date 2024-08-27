#pragma once
#include<iostream>
#include<string>
#include"Worker.h"
#include<fstream>
using namespace std;
#define FILENAME "empFile.txt"
#define ERROR -1
#define MAX 1000
#define MIN 0

class Manager {

public:
	//����
	Manager();
	//չʾ�˵�
	void show_Menu();
	//�˳�ϵͳ
	void exitSystem();
	//���ְ��
	void AddWorker();
	//�ж�ְ����Ƿ��ظ�
	bool Same_work(int ID);
	//�ļ�����
	void saveFile();
	bool flagFile;//�ж��ļ��Ƿ���ڣ��Ƿ�Ϊ��
	int getFileWorker_num();//��¼�ļ��е�����
	void init_worker();//���ļ�������
	//��ʾְ����Ϣ
	void show_worker();
	//�жϾ���ְ���Ƿ����
	int Exist_worker(int id);
	//ɾ��ְ��
	void Delete_worker(int ID);
	//�޸�ְ����Ϣ
	void Revise_worker();
	//����ְ��
	void Find_worker();
	//ְ������
	void Sort_worker();
	//����ļ�
	void Clean_File();
	//����
	~Manager();
public:
	//ְ������
	int worker_num;
	Worker** workerArray;
};
