#include "boss.h"

Boss::Boss(int id, string name, int did)
{
	this->m_id = id;
	this->m_Name = name;
	this->dId = did;
}

void Boss::showinfo()
{
	cout << "ְ�����:" << this->m_id
		<< "\tְ������:" << this->m_Name
		<< "\t��λ:" << this->getDeptName() << '\n';
}

string Boss::getDeptName()
{
	return string("�ϰ�");
}