#pragma once
#include <iostream>
#include "woker.h"
#include <fstream>
#include <istream>
#define FILENAME "filename.txt"

using namespace std;
class WorkerManager
{
public:
	WorkerManager();
	~WorkerManager();
	void show_maun();
	void exitSystem();
	void add_Emp();
	void save();
	void Show_Emp();
	void init_Emp();
	int get_EmpNum();	
	int Isexit(int id);
	void Del_Emp();
	void Mod_Emp();
	void Find_Emp();
	void Sort_Emp();
	void Clean_file();
	int m_EmpNum;
	Woker** m_EmpArray;
	bool m_FileIsEmpty;
};