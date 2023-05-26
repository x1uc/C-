#pragma once
#include <iostream>
#include <string>
using namespace std;
#include "woker.h"
class Boss : public Woker
{
public:
	Boss(int id, string name, int did);
	void showinfo();
	string getDeptName();
};