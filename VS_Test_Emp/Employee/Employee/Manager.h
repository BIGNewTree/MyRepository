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
	//构造
	Manager();
	//展示菜单
	void show_Menu();
	//退出系统
	void exitSystem();
	//添加职工
	void AddWorker();
	//判断职编号是否重复
	bool Same_work(int ID);
	//文件操作
	void saveFile();
	bool flagFile;//判断文件是否存在，是否为空
	int getFileWorker_num();//记录文件中的人数
	void init_worker();//读文件中数据
	//显示职工信息
	void show_worker();
	//判断具体职工是否存在
	int Exist_worker(int id);
	//删除职工
	void Delete_worker(int ID);
	//修改职工信息
	void Revise_worker();
	//查找职工
	void Find_worker();
	//职工排序
	void Sort_worker();
	//清空文件
	void Clean_File();
	//析构
	~Manager();
public:
	//职工人数
	int worker_num;
	Worker** workerArray;
};
