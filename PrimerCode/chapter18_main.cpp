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

	//ʹ��֮ǰ�趨���������쳣��
	cplusplus_primer::Sales_data item1, item2, sum;
	cout << "�������������룺���� ���� ���� " << endl;
	while (cin >> item1 >> item2) {
		try {
			sum = item1 + item2;//��Ϊ+�ŵĲ�����Salse_data���ͣ����Ի��Զ���Salse_data���ڵ������ռ���ȥѰ��
		}
		catch (const isbn_mismatch &e) {
			cerr << e.what() << ": left isbn(" << e.left
				<< ") right isbn(" << e.right << ")" << endl;
		}
		print(cout,sum);//��Ϊprint��sum������Salse_data���ͣ����Ի��Զ���Salse_data���ڵ������ռ���ȥѰ��
	}
	return 0;
}
