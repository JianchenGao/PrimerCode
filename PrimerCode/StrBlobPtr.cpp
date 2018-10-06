#include "StrBlobPtr.h"
#include "StrBlob.h"

StrBlobPtr::StrBlobPtr(StrBlob &a, size_t sz) :
	wptr(a.data), curr(sz) { }

std::shared_ptr<std::vector<std::string>>
StrBlobPtr::check(std::size_t i, const std::string& msg) const
{
	auto ret = wptr.lock();	//vector还存在吗？
	if (!ret)
		throw std::runtime_error("unbound StrBlobPtr");
	if (i >= ret->size())
		throw std::out_of_range(msg);
	return ret;	//否则，返回指向vector的shared_ptr
}

std::string& StrBlobPtr::deref() const
{
	auto p = check(curr, "dereference past end");
	return (*p)[curr];	//(*p)是对象所指向的vector
}

StrBlobPtr& StrBlobPtr::incr()
{
	//如果curr已经指向容器的尾后位置，就不能递增它
	check(curr, "increment past end of StrBlobPtr");
	++curr;	//推进当前位置
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
	//如果curr已经指向了容器的尾后位置，则无法递增它
	check(curr, "increment past end of StrBlobPtr");
	++curr;
	return *this;
}

StrBlobPtr& StrBlobPtr::operator--()
{
	//如果curr是0，则继续递减它将产生一个无效下标
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