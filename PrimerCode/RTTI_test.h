#ifndef RTTI_TEST_H
#define RTTI_TEST_H
#include<typeinfo>
#include<string>

class Base {
	friend bool operator==(const Base&, const Base&);
public:
	//Base的接口成员
	std::string get_name() { return name; }
	float get_weight() { return weight; }
	Base(std::string n,float w):name(n),weight(w){ }
protected:
	virtual bool equal(const Base&) const;
	//Base的数据成员和其他用于实现的成员
private:
	std::string name;
	float weight;
};
class Derived :public Base {
public:
	//Derived的其他接口成员
	int get_number() { return number; }
	Derived(std::string n,float w,int num):Base(n,w),number(num){ }
protected:
	bool equal(const Base&) const;
	//Derived 的数据成员和其他用于实现的成员
private:
	int number;
};

bool operator==(const Base &lhs, const Base &rhs);
#endif // !RTTI_TEST_H
#pragma once
