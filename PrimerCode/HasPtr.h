#pragma once
#ifndef HASPTR_H
#define HASPTR_H

#include<string>

class HasPtr {
	friend void swap(HasPtr&, HasPtr&);
public:
	HasPtr(const std::string &s = std::string()) :
		ps(new std::string(s)), i(0) { }
	HasPtr(const HasPtr &p) :	//拷贝构造函数
		ps(new std::string(*p.ps)), i(p.i) { }
	HasPtr(HasPtr &&p) noexcept : ps(p.ps), i(p.i) { p.ps = 0; }	//移动构造函数
	HasPtr& operator=(HasPtr &rhs)
	{
		swap(*this, rhs); return *this;
	}
	HasPtr& operator=(const HasPtr &);
	~HasPtr() { delete ps; }

private:
	std::string *ps;
	int i;
};

inline
void swap(HasPtr &lhs, HasPtr &rhs)
{
	using std::swap;
	swap(lhs.ps, rhs.ps);	//交换指针，而不是string数据
	swap(lhs.i, rhs.i);		//交换int成员
}

#endif // !SALES_DATA
