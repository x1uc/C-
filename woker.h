#pragma once
#include <iostream>
using namespace std;

class Woker
{
public:
	virtual void showinfo()=0;
	virtual string getDeptName() = 0;
	int m_id;
	string m_Name;
	int dId;
};