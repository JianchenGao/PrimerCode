#include "StrBlobPtr.h"
#include "StrBlob.h"

StrBlobPtr::StrBlobPtr(StrBlob &a, size_t sz) :
	wptr(a.data), curr(sz) { }

std::shared_ptr<std::vector<std::string>>
StrBlobPtr::check(std::size_t i, const std::string& msg) const
{
	auto ret = wptr.lock();	//vector��������
	if (!ret)
		throw std::runtime_error("unbound StrBlobPtr");
	if (i >= ret->size())
		throw std::out_of_range(msg);
	return ret;	//���򣬷���ָ��vector��shared_ptr
}

std::string& StrBlobPtr::deref() const
{
	auto p = check(curr, "dereference past end");
	return (*p)[curr];	//(*p)�Ƕ�����ָ���vector
}

StrBlobPtr& StrBlobPtr::incr()
{
	//���curr�Ѿ�ָ��������β��λ�ã��Ͳ��ܵ�����
	check(curr, "increment past end of StrBlobPtr");
	++curr;	//�ƽ���ǰλ��
	return *this;
}

StrBlobPtr StrBlob::begin()  // can't be defined until StrBlobPtr is
{
	return StrBlobPtr(*this);
}
StrBlobPtr StrBlob::end()
{
	auto ret = StrBlobPtr(*this, data->size());
	return ret;
}

StrBlobPtr& StrBlobPtr::operator++()
{
	//���curr�Ѿ�ָ����������β��λ�ã����޷�������
	check(curr, "increment past end of StrBlobPtr");
	++curr;
	return *this;
}

StrBlobPtr& StrBlobPtr::operator--()
{
	//���curr��0��������ݼ���������һ����Ч�±�
	--curr;
	check(curr, "decrement past end of StrBlobPtr");
	return *this;
}

StrBlobPtr& StrBlobPtr::operator++(int)
{
	StrBlobPtr ret = *this;
	++*this;
	return ret;
}

StrBlobPtr& StrBlobPtr::operator--(int)
{
	StrBlobPtr ret = *this;
	--*this;
	return ret;
}