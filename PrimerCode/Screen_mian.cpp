#include <string>
#include <iostream>
#include<initializer_list>

#include "Window_mgr.h"
#include "Sales_data.h"
#include "Screen.h"

using namespace std;



int Screen_main()
{
	Screen myScreen(5,3);
	const Screen blank(5, 3);

	myScreen.set('#').display(cout);
	blank.display(cout);
	system("pause");
	return 0;
}