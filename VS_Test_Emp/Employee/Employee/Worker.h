#pragma once
#include<iostream>
#include<string>
using namespace std;

//职工
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

//普通员工
class Employee :public Worker {
public:
	Employee(int id, string name, int deptid);
	void showInfo();
	string office();
	string department_Information();
};

//经理
class Manger :public Worker {
public:
	Manger(int id, string name, int deptid);
	void showInfo();
	string office();
	string department_Information();
};

//老板
class Boss :public Worker {
public:
	Boss(int id, string name, int deptid);
	void showInfo();
	string office();
	string department_Information();
};