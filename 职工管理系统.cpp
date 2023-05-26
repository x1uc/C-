#include "wokerManager.h"
#include "boss.h"
#include "employee.h"
#include "manager.h"

int main()
{
	WorkerManager rm;
	while (true)
	{
		rm.show_maun();
		cout << "请输入你的选择" << '\n';
		int op;
		cin >> op;
		switch (op)
		{
		case 0: //退出选项
			rm.exitSystem();
		case 1:
			rm.add_Emp();
			break;
		case 2:
			rm.Show_Emp();
			break;
		case 3:
			rm.Del_Emp();
			break;
		case 4:
			rm.Mod_Emp();
			break;
		case 5:
			rm.Find_Emp();
			break;
		case 6:
			rm.Sort_Emp();
			break;
		case 7:
			rm.Clean_file();
			break;
		default:
			break;
		}
	}
	return 0;
}

