#include "employee.h"

Employee::Employee(int id, string name, int did)
{
	this->m_id = id;
	this->m_Name = name;
	this->dId = did;
}

void Employee::showinfo()
{
	cout << "ְ�����:" << this->m_id
		<< "\tְ������:" << this->m_Name
		<< "\t��λ:" << this->getDeptName() << '\n';
}

string Employee::getDeptName()
{
	return string("ְ��");
}