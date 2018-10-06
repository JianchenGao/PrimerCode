#pragma once
#ifndef HASPTR_H
#define HASPTR_H

#include<string>

class HasPtr {
	friend void swap(HasPtr&, HasPtr&);
public:
	HasPtr(const std::string &s = std::string()) :
		ps(new std::string(s)), i(0) { }
	HasPtr(const HasPtr &p) :	//�������캯��
		ps(new std::string(*p.ps)), i(p.i) { }
	HasPtr(HasPtr &&p) noexcept : ps(p.ps), i(p.i) { p.ps = 0; }	//�ƶ����캯��
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
	swap(lhs.ps, rhs.ps);	//����ָ�룬������string����
	swap(lhs.i, rhs.i);		//����int��Ա
}

#endif // !SALES_DATA
