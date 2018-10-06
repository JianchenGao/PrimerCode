#include "Quote.h"
#include<iostream>

using namespace std;

Bulk_quote::Bulk_quote(const std::string& book, double price, 
	std::size_t qty, double disc):
	Disc_quote(book,price,qty,disc){ }

double Bulk_quote::net_price(size_t cnt) const
{
	if (cnt >= min_qty)
		return cnt * (1 - discount)*price;
	else
		return cnt*price;
}

//计算并打印销售给定数量的某种书籍所得的费用
double print_total(ostream &os, const Quote &item, size_t n)
{
	//根据传入item形参的对象类型调用Quote::net_price
	//或者Bulk_quote::net_price
	double ret = item.net_price(n);
	os << "ISBN:" << item.isbn()
		<< " # sold: " << n << " total due: " << ret << endl;
	return ret;
}