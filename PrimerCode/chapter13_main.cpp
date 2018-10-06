#include"Sales_data.h"
#include"Message.h"
#include"Folder.h"
#include"HasPtr.h"
#include"StrVec.h"

#include<iostream>


using namespace std;

int chapter13_main(void)
{
	Folder folder1;
	Folder folder2;

	Message M1("this is frist 1 msg!!");
	Message M2("this is second 2 msg!!");
	Message M3("this is thrid 3 msg!!");
	Message M4("this is forth 4 msg!!");

	M1.save(folder1);
	M2.save(folder1);
	M3.save(folder2);
	M4.save(folder2);

	folder1.print_msg();
	folder2.print_msg();

	cout << "hello word" << endl;

	M4 = M1;
	folder1.print_msg();
	folder2.print_msg();


	cout << "hello word" << endl;
	system("pause");
	return 0;
}

