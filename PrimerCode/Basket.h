#pragma once
#ifndef BASKET_H
#define BASKET_H

#include<memory>
#include<set>

#include"Quote.h"

class Basket {
public:
	//Basket使用合成的默认构造函数和拷贝控制成员
	void add_item(const std::shared_ptr<Quote> &sale)
	{
		items.insert(sale);
	}
	//add_item新版本
	void add_item(const Quote& sale) //拷贝给定对象
	{
		items.insert(std::shared_ptr<Quote>(sale.clone()));
	}
	void add_item(const Quote&& sale) //移动给定对象
	{
		items.insert(std::shared_ptr<Quote>(std::move(sale).clone()));
	}
	//打印每本书的总价和购物篮中所有书的总价
	double total_receipt(std::ostream&) const;

private:
	//该函数用于比较shared_ptr,multiset成员会用到它
	static bool compare(const std::shared_ptr<Quote> &lhs,
		const std::shared_ptr<Quote> &rhs)
	{
		return lhs->isbn() < rhs->isbn();
	}
	//multiset 保存多个报价，按照compare成员排序
	std::multiset < std::shared_ptr<Quote>, decltype(compare)* > items{ compare };//用法在书的P377
};

#endif // !BASKET_H