#include"Worker.h"

//��ְͨ��
Employee::Employee(int id, string name, int deptid) {
	this->m_ID = id;
	this->m_Name = name;
	this->m_DepartmentID = deptid;
}
void Employee::showInfo() {
	cout << "��λ:" << this->office()
		<< "\tԱ�����: " << this->m_ID
		<< "\tԱ������: " << this->m_Name
		<< "\tԱ�����ű��: " << this->m_DepartmentID
		<< "\t��λ����: " << this->department_Information() << endl;
}
string Employee::office() {
	return "��ͨԱ��";
}
string Employee::department_Information() {
	return "��ɾ����������";
}

//����
Manger::Manger(int id, string name, int deptid) {
	this->m_ID = id;
	this->m_Name = name;
	this->m_DepartmentID = deptid;
}
void Manger::showInfo() {
	cout <<"��λ:"<<this->office() 
		 << "\tԱ�����: " << this->m_ID
		 << "\tԱ������: " << this->m_Name 
		 << "\tԱ�����ű��: " << this->m_DepartmentID 
		 << "\t��λ����: " <<this->department_Information()<< endl;
}
string Manger::office() {
	return "����";
}
string Manger::department_Information() {
	return "����ϰ�������񣬽������·�����ְͨԱ";
}

//�ϰ�
Boss::Boss(int id, string name, int deptid) {
	this->m_ID = id;
	this->m_Name = name;
	this->m_DepartmentID = deptid;
}
void Boss::showInfo() {
	cout << "��λ:" << this->office()
		<< "\tԱ�����: " << this->m_ID
		<< "\tԱ������: " << this->m_Name
		<< "\tԱ�����ű��: " << this->m_DepartmentID
		<< "\t��λ����: " << this->department_Information() << endl;
}
string Boss::office() {
	return "�ϰ�";
}
string Boss::department_Information() {
	return "����˾���·����������";
}
