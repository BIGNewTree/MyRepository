#pragma once
#include<iostream>
#include<string>
using namespace std;

//ְ��
class Worker {

public:
	virtual string office() = 0;
	virtual string department_Information() = 0;
	virtual void showInfo() = 0;
public:
	int m_ID;
	string m_Name;
	int m_DepartmentID;
};

//��ͨԱ��
class Employee :public Worker {
public:
	Employee(int id, string name, int deptid);
	void showInfo();
	string office();
	string department_Information();
};

//����
class Manger :public Worker {
public:
	Manger(int id, string name, int deptid);
	void showInfo();
	string office();
	string department_Information();
};

//�ϰ�
class Boss :public Worker {
public:
	Boss(int id, string name, int deptid);
	void showInfo();
	string office();
	string department_Information();
};