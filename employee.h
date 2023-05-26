#pragma once
#include <iostream>
#include <string>
using namespace std;
#include "woker.h"
class Employee : public Woker
{
public:
	Employee(int id, string name, int did);
	void showinfo();
	string getDeptName();
};