#include "employee.h"

Employee::Employee(int id, string name, int did)
{
	this->m_id = id;
	this->m_Name = name;
	this->dId = did;
}

void Employee::showinfo()
{
	cout << "职工编号:" << this->m_id
		<< "\t职工姓名:" << this->m_Name
		<< "\t岗位:" << this->getDeptName() << '\n';
}

string Employee::getDeptName()
{
	return string("职工");
}