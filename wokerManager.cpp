#include "wokerManager.h"
#include "woker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
WorkerManager::WorkerManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open())
	{
		//cout << "�ļ�������\n";
		this->m_EmpNum = 0;
		this->m_FileIsEmpty = true;
		this->m_EmpArray = NULL;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch; //�����ļ�β���ı�־
	if (ifs.eof())
	{
		//cout << "�ļ�Ϊ��\n";
		this->m_EmpNum = 0;
		this->m_FileIsEmpty = true;
		this->m_EmpArray = NULL;
		ifs.close();
		return;
	}
	this->m_EmpNum = this->get_EmpNum();
	this->m_EmpArray = new Woker * [this->m_EmpNum];
	init_Emp();
}

WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != NULL)
	{
		delete[] this->m_EmpArray;
	}
}
void WorkerManager::show_maun()
{
	cout << "********************************************" << endl;
	cout << "*********  ��ӭʹ��ְ������ϵͳ�� **********" << endl;
	cout << "*************  0.�˳��������  *************" << endl;
	cout << "*************  1.����ְ����Ϣ  *************" << endl;
	cout << "*************  2.��ʾְ����Ϣ  *************" << endl;
	cout << "*************  3.ɾ����ְְ��  *************" << endl;
	cout << "*************  4.�޸�ְ����Ϣ  *************" << endl;
	cout << "*************  5.����ְ����Ϣ  *************" << endl;
	cout << "*************  6.���ձ������  *************" << endl;
	cout << "*************  7.��������ĵ�  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}
void WorkerManager::exitSystem()
{
	cout << "��ӭ�´�ʹ��" << '\n';
	exit(0);
}

void WorkerManager::add_Emp()
{
	cout << "����������ְ������\n";
	int addNum = 0;
	cin >> addNum;
	if (addNum > 0)
	{
		int newsize = this->m_EmpNum+addNum;
		Woker** newSpace = new Woker * [newsize];
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		for (int i = 0; i < addNum; i++)
		{
			int id;
			string name;
			int dselect;
			cout << "�������" << i + 1 << "����ְ���ı��:";
			cin >> id;
			cout << "�������" << i + 1 << "����ְ��������:";
			cin >> name;
			cout << "��ѡ���Ա���ĸ�λ:" << '\n';
			cout << "1.��ְͨ��"<<'\n';
			cout << "2.����" << '\n';
			cout << "3.�ϰ�" << '\n';
			cin >> dselect;
			Woker* worker = NULL;
			switch (dselect)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}
			if (worker != NULL)
			{
				newSpace[this->m_EmpNum + i] = worker;
			}
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray = newSpace;
		this->m_EmpNum = newsize;
		cout << "�ɹ����" << addNum << "��Ա��\n";
		this->m_FileIsEmpty = false;
		this->save();
		system("pause");
		system("cls");
	}
	else
	{
		cout << "�����д���\n";
	}
	
}
void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_id << ' ' << this->m_EmpArray[i]->m_Name << ' ' << this->m_EmpArray[i]->dId << '\n';
	}
	ofs.close();
}

int WorkerManager::get_EmpNum()
{
	int num = 0;
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int did;
	while (ifs >> id && ifs >> name && ifs >> did)
	{
		num++;
	}
	ifs.close();
	return num;
}
void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int did;
	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> did)
	{
		Woker* woker = NULL;                                                                                                                                                                                                                                                                                                              
		if (did == 1)
		{
			woker = new Employee(id, name, did);
		}                                                                                                
		else if (did == 2)
		{
			woker = new Manager(id, name, did);
		}
		else
		{
			woker = new Boss(id, name, did);
		}
		this->m_EmpArray[index] = woker;
		index++;
	}
}
void WorkerManager::Show_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ�Ϊ��\n";
	}
	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			this->m_EmpArray[i]->showinfo();
		}
	}
	system("pause");
	system("cls");
}

int WorkerManager::Isexit(int id)
{
	int idx = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_id == id)
		{
			idx = i;
		}
	}
	return idx;
}

void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ�Ϊ�ջ򲻴���\n";
	}
	else
	{
		int id;
		cout << "������Ҫɾ����id";
		cin >> id;
		int target = this->Isexit(id);
		if (target != -1)
		{
			for (int i = target; i < this->m_EmpNum-1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;
			if (this->m_EmpNum == 0)
			{
				this->m_FileIsEmpty = true;
			}
			this->save();
			cout << "ɾ���ɹ�\n";
		}
		else
		{
			cout << "Ҫɾ����Ԫ�ز�����\n";
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ�Ϊ�ջ򲻴���\n";
	}
	else
	{
		cout << "�������޸ĵ�ְ����:";
		int id;
		cin >> id;
		int index = this->Isexit(id);
		if (this->Isexit(id) == -1)
		{
			cout << "�޸�ʧ�� ���޴���\n";
		}
		else
		{
			delete this->m_EmpArray[index];
			string newName ;
			int dselect = 0;
			cout << "�鵽" << id << "��ְ�����������µ�ְ���ţ�";
			int newid = 0;
			cin >> newid;
			cout << "����������:";
			cin >> newName;
			cout << "�������λ\n";
			cout << "1.��ͨԱ��\n";
			cout << "2.����\n";
			cout << "3.�ϰ�" << '\n';
			cin >> dselect;

			Woker* worker = NULL;
			switch (dselect)
			{
			case 1:
				worker = new Employee(newid, newName, 1);
				break;
			case 2:
				worker = new Manager(newid, newName, 2);
				break;
			case 3:
				worker = new Boss(newid, newName, 3);
				break;
			default:
				break;
			}
			this->m_EmpArray[index] = worker;
			cout << "�޸ĳɹ�" << '\n';
			this->save();
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��ļ�Ϊ��\n";
	}
	else
	{
		cout << "��������ҵķ�ʽ��\n" ;
		cout << "1����ְ����Ų���\n";
		cout << "2������������" ;
		int select;
		cin >> select;
		if (select == 1)
		{
			int id;
			cout << "������Ҫ���ҵ�ְ�����:";
			cin >> id;
			int idx = this->Isexit(id);
			if (idx == -1)
			{
				cout << "���޴���\n";
			}
			else
			{
				cout << "���ҳɹ�,��ְ����Ϣ����\n";
				this->m_EmpArray[idx]->showinfo();
			}
		}
		else if (select == 2)
		{
			string name;
			cout << "������Ҫ����Ա��:";
			cin >> name;
			bool flag = 0;
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					flag = 1;
					this->m_EmpArray[i]->showinfo();
				}
			}
			if (!flag)
			{
				cout << "���޴���\n";
			}
		}
		else
		{
			cout << "����ѡ������\n";
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��\n";
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��ѡ������ʽ�� \n";
		cout << "1����ְ���Ž�������\n";
		cout << "2����ְ���Ž��н���\n";
		int select;
		cin >> select;
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int minirmax = i;
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1)
				{
					if (this->m_EmpArray[minirmax]->m_id > this->m_EmpArray[j]->m_id)
					{
						minirmax = j;
					}
				}
				else
				{
					if (this->m_EmpArray[minirmax]->m_id < this->m_EmpArray[j]->m_id)
					{
						minirmax = j;
					}
				}
			}
			Woker* woker = m_EmpArray[minirmax];
			m_EmpArray[minirmax] = m_EmpArray[i];
			m_EmpArray[i] = woker;
		}
	}
	cout << "����ɹ�,������Ϊ\n";
	this->save();
	this->Show_Emp();
}

void WorkerManager::Clean_file()
{
	cout << "ȷ����գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;
	int select;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs;
		ofs.open(FILENAME, ios::trunc);
		ofs.close();
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i] != NULL)
				{
					delete this->m_EmpArray[i];
				}
			}
			this->m_EmpNum = 0;
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_FileIsEmpty = true;
		}
		cout << "��ճɹ�\n";
	}
	system("pause");
	system("cls");
}