#include "manager.h"

Manager::Manager(int id, string name, int did)
{
	this->m_id = id;
	this->m_Name = name;
	this->dId = did;
}

void Manager::showinfo()
{
	cout << "ְ�����:" << this->m_id
		<< "\tְ������:" << this->m_Name
		<< "\t��λ:" << this->getDeptName() << '\n';
}

string Manager::getDeptName()
{
	return string("����");
}