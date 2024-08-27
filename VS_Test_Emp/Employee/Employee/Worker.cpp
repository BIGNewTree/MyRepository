#include"Worker.h"

//普通职工
Employee::Employee(int id, string name, int deptid) {
	this->m_ID = id;
	this->m_Name = name;
	this->m_DepartmentID = deptid;
}
void Employee::showInfo() {
	cout << "岗位:" << this->office()
		<< "\t员工编号: " << this->m_ID
		<< "\t员工姓名: " << this->m_Name
		<< "\t员工部门编号: " << this->m_DepartmentID
		<< "\t岗位工作: " << this->department_Information() << endl;
}
string Employee::office() {
	return "普通员工";
}
string Employee::department_Information() {
	return "完成经理给的任务";
}

//经理
Manger::Manger(int id, string name, int deptid) {
	this->m_ID = id;
	this->m_Name = name;
	this->m_DepartmentID = deptid;
}
void Manger::showInfo() {
	cout <<"岗位:"<<this->office() 
		 << "\t员工编号: " << this->m_ID
		 << "\t员工姓名: " << this->m_Name 
		 << "\t员工部门编号: " << this->m_DepartmentID 
		 << "\t岗位工作: " <<this->department_Information()<< endl;
}
string Manger::office() {
	return "经理";
}
string Manger::department_Information() {
	return "完成老板给的任务，将任务下发给普通职员";
}

//老板
Boss::Boss(int id, string name, int deptid) {
	this->m_ID = id;
	this->m_Name = name;
	this->m_DepartmentID = deptid;
}
void Boss::showInfo() {
	cout << "岗位:" << this->office()
		<< "\t员工编号: " << this->m_ID
		<< "\t员工姓名: " << this->m_Name
		<< "\t员工部门编号: " << this->m_DepartmentID
		<< "\t岗位工作: " << this->department_Information() << endl;
}
string Boss::office() {
	return "老板";
}
string Boss::department_Information() {
	return "管理公司，下发任务给经理";
}
