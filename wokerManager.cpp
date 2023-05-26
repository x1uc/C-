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
		//cout << "文件不存在\n";
		this->m_EmpNum = 0;
		this->m_FileIsEmpty = true;
		this->m_EmpArray = NULL;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch; //读走文件尾部的标志
	if (ifs.eof())
	{
		//cout << "文件为空\n";
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
	cout << "*********  欢迎使用职工管理系统！ **********" << endl;
	cout << "*************  0.退出管理程序  *************" << endl;
	cout << "*************  1.增加职工信息  *************" << endl;
	cout << "*************  2.显示职工信息  *************" << endl;
	cout << "*************  3.删除离职职工  *************" << endl;
	cout << "*************  4.修改职工信息  *************" << endl;
	cout << "*************  5.查找职工信息  *************" << endl;
	cout << "*************  6.按照编号排序  *************" << endl;
	cout << "*************  7.清空所有文档  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}
void WorkerManager::exitSystem()
{
	cout << "欢迎下次使用" << '\n';
	exit(0);
}

void WorkerManager::add_Emp()
{
	cout << "请输入增加职工数量\n";
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
			cout << "请输入第" << i + 1 << "个新职工的编号:";
			cin >> id;
			cout << "请输入第" << i + 1 << "个新职工的姓名:";
			cin >> name;
			cout << "请选择该员工的岗位:" << '\n';
			cout << "1.普通职工"<<'\n';
			cout << "2.经理" << '\n';
			cout << "3.老板" << '\n';
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
		cout << "成功添加" << addNum << "名员工\n";
		this->m_FileIsEmpty = false;
		this->save();
		system("pause");
		system("cls");
	}
	else
	{
		cout << "输入有错误\n";
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
		cout << "文件为空\n";
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
		cout << "文件为空或不存在\n";
	}
	else
	{
		int id;
		cout << "请输入要删除的id";
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
			cout << "删除成功\n";
		}
		else
		{
			cout << "要删除的元素不存在\n";
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件为空或不存在\n";
	}
	else
	{
		cout << "请输入修改的职工号:";
		int id;
		cin >> id;
		int index = this->Isexit(id);
		if (this->Isexit(id) == -1)
		{
			cout << "修改失败 查无此人\n";
		}
		else
		{
			delete this->m_EmpArray[index];
			string newName ;
			int dselect = 0;
			cout << "查到" << id << "号职工，请输入新的职工号：";
			int newid = 0;
			cin >> newid;
			cout << "请输入姓名:";
			cin >> newName;
			cout << "请输入岗位\n";
			cout << "1.普通员工\n";
			cout << "2.经理\n";
			cout << "3.老板" << '\n';
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
			cout << "修改成功" << '\n';
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
		cout << "文件不存在或文件为空\n";
	}
	else
	{
		cout << "请输入查找的方式：\n" ;
		cout << "1、按职工编号查找\n";
		cout << "2、按姓名查找" ;
		int select;
		cin >> select;
		if (select == 1)
		{
			int id;
			cout << "请输入要查找的职工编号:";
			cin >> id;
			int idx = this->Isexit(id);
			if (idx == -1)
			{
				cout << "查无此人\n";
			}
			else
			{
				cout << "查找成功,该职工信息如下\n";
				this->m_EmpArray[idx]->showinfo();
			}
		}
		else if (select == 2)
		{
			string name;
			cout << "请输入要查找员工:";
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
				cout << "查无此人\n";
			}
		}
		else
		{
			cout << "输入选项有误\n";
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空\n";
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择排序方式： \n";
		cout << "1、按职工号进行升序\n";
		cout << "2、按职工号进行降序\n";
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
	cout << "排序成功,排序结果为\n";
	this->save();
	this->Show_Emp();
}

void WorkerManager::Clean_file()
{
	cout << "确认清空？" << endl;
	cout << "1、确认" << endl;
	cout << "2、返回" << endl;
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
		cout << "清空成功\n";
	}
	system("pause");
	system("cls");
}