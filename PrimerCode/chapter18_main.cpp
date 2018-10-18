#include"Sales_data.h"
#include"ExceptionForSalesdata.h"
#include<iostream>

using namespace std;

void print()
{
	cout << "print???main" << endl;
}

int chapter18_main()
{
	//using cplusplus_primer::Sales_data;
	//using cplusplus_primer::operator+;
	//using cplusplus_primer::print;

	//使用之前设定的书店程序异常类
	cplusplus_primer::Sales_data item1, item2, sum;
	cout << "请输入依次输入：书名 单价 数量 " << endl;
	while (cin >> item1 >> item2) {
		try {
			sum = item1 + item2;//因为+号的参数是Salse_data类型，所以会自动到Salse_data所在的命名空间里去寻找
		}
		catch (const isbn_mismatch &e) {
			cerr << e.what() << ": left isbn(" << e.left
				<< ") right isbn(" << e.right << ")" << endl;
		}
		print(cout,sum);//因为print的sum参数是Salse_data类型，所以会自动到Salse_data所在的命名空间里去寻找
	}
	return 0;
}
