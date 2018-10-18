#include"RTTI_test.h"
#include <iostream>

using namespace std;

bool Derived::equal(const Base &rhs) const
{
	//���������������������ȵģ�����ת�����̲����׳��쳣
	auto r = dynamic_cast<const Derived&>(rhs);
	cout << "Derived's equal" << endl;
	//ִ�бȽ�����Derived����Ĳ��������ؽ��
	return ( this->Base::equal(rhs)) && (r.number == this->number);
}

bool Base::equal(const Base &rhs) const
{
	//ִ�бȽ�Base�������
	cout << "Base's rqual" << endl;
	return (this->name == rhs.name) && (this->weight == rhs.weight);
}

bool operator==(const Base &lhs, const Base &rhs)
{
	//���typeid����ͬ������flase�����������equal
	return typeid(lhs) == typeid(rhs) && lhs.equal(rhs);
}