#pragma once
#ifndef QUOTE_H
#define QUOTE_H
#include<string>
#include<set>
#include<ostream>


class Quote {
public:
	//该虚函数返回当前对象的一份动态分配的拷贝
	//这些成员使用的引用限定符参见13.6.3
	virtual Quote* clone() const & { return new Quote(*this); }	//只能返回右值
	virtual Quote* clone() && { return new Quote(std::move(*this)); } //返回左值

	Quote() = default;
	Quote(const std::string &book,double sales_price):
		bookNo(book),price(sales_price){ }
	std::string isbn() const { return bookNo; }
	virtual double net_price(std::size_t n) const { return 0; };
	//如果我们删除的是一个指向派生类对象的基类指针，则需要虚析构函数
	virtual ~Quote() = default;	//动态绑定析构函数
private:
	std::string bookNo;
protected:
	double price = 0.0;
};

//用于保存折扣值和购买量的类，派生类使用这些数据可以实现不同的价格策略
class Disc_quote :public Quote {
public:
	Disc_quote() = default;
	Disc_quote(const std::string& book, double price,
		std::size_t qty, double disc) :
		Quote(book, price){ }
	double net_price(std::size_t) const = 0;	//纯虚函数
};

//当同一书籍的销售量超过某个值启用折扣
//折扣的值是一个小于1的正的小数值，以此来降低正常销售价格
class Bulk_quote :public Disc_quote {	//Bulk_quote继承了Quote
public:
	Bulk_quote* clone() const & { return new Bulk_quote(*this); }	//只能返回右值
	Bulk_quote* clone() && { return new Bulk_quote(std::move(*this)); } //返回左值
	using Disc_quote::Disc_quote;	//继承Disc_quote的构造函数
	Bulk_quote() = default;
	Bulk_quote(const std::string&, double, std::size_t, double);
	//覆盖基类的函数版本以实现基于大量购买的折扣政策
	double net_price(std::size_t) const override;	//显示注明使用此函数改写基类的虚函数
private:
	std::size_t min_qty = 0;	//适用折扣政策的最低购买量
	double discount = 0.0;	//以小数表示的折扣额
};

extern double print_total(std::ostream &os, const Quote &item, size_t n);

#endif