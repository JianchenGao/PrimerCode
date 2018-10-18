#include"RTTI_test.h"
#include <iostream>

using namespace std;

bool Derived::equal(const Base &rhs) const
{
	//我们清楚这两个类型是相等的，所有转换过程不会抛出异常
	auto r = dynamic_cast<const Derived&>(rhs);
	cout << "Derived's equal" << endl;
	//执行比较两个Derived对象的操作并返回结果
	return ( this->Base::equal(rhs)) && (r.number == this->number);
}

bool Base::equal(const Base &rhs) const
{
	//执行比较Base对象操作
	cout << "Base's rqual" << endl;
	return (this->name == rhs.name) && (this->weight == rhs.weight);
}

bool operator==(const Base &lhs, const Base &rhs)
{
	//如果typeid不相同，返回flase；否则虚调用equal
	return typeid(lhs) == typeid(rhs) && lhs.equal(rhs);
}