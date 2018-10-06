#include"Sales_data.h"
#include"Message.h"
#include"Folder.h"
#include"HasPtr.h"
#include"StrVec.h"
#include"StrBlob.h"
#include"StrBlobPtr.h"
#include"TextQuery.h"
#include"PrintString.h"
#include"Quote.h"
#include"Query.h"

#include<iostream>


using namespace std;



//chapter14_


int chapter14_main(void)
{
	StrBlob a1 = { "hi","bye","now" };
	StrBlobPtr p(a1);	//p指向a1中的vector
	*p = "okey";
	cout << p->size() << endl;
	cout << (*p).size() << endl;
	
	string s =  "ok !" ;
	PrintString printer;
	printer(s);
	PrintString errors(cerr, '\n');
	errors(s);

	Quote base("0-201-82470-1", 50);
	print_total(cout, base, 10);	//调用Quote::net_price
	Bulk_quote derived("0-201-82470-1", 50,5,.19);
	print_total(cout, derived, 10);	//调用Bulk_quote::net_price

	//cout << q << endl;

	cout << "hello word" << endl;
	system("pause");
	return 0;
}

