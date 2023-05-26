#include "manager.h"

Manager::Manager(int id, string name, int did)
{
	this->m_id = id;
	this->m_Name = name;
	this->dId = did;
}

void Manager::showinfo()
{
	cout << "职工编号:" << this->m_id
		<< "\t职工姓名:" << this->m_Name
		<< "\t岗位:" << this->getDeptName() << '\n';
}

string Manager::getDeptName()
{
	return string("经理");
}