#ifndef RTTI_TEST_H
#define RTTI_TEST_H
#include<typeinfo>
#include<string>

class Base {
	friend bool operator==(const Base&, const Base&);
public:
	//Base�Ľӿڳ�Ա
	std::string get_name() { return name; }
	float get_weight() { return weight; }
	Base(std::string n,float w):name(n),weight(w){ }
protected:
	virtual bool equal(const Base&) const;
	//Base�����ݳ�Ա����������ʵ�ֵĳ�Ա
private:
	std::string name;
	float weight;
};
class Derived :public Base {
public:
	//Derived�������ӿڳ�Ա
	int get_number() { return number; }
	Derived(std::string n,float w,int num):Base(n,w),number(num){ }
protected:
	bool equal(const Base&) const;
	//Derived �����ݳ�Ա����������ʵ�ֵĳ�Ա
private:
	int number;
};

bool operator==(const Base &lhs, const Base &rhs);
#endif // !RTTI_TEST_H
#pragma once
