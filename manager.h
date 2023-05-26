#pragma once
#include <iostream>
#include <string>
using namespace std;
#include "woker.h"
class Manager : public Woker
{
public:
	Manager(int id, string name, int did);
	void showinfo();
	string getDeptName();
};