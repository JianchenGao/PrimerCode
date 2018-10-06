#pragma once
#ifndef STRBLOBPTR_H
#define STRBLOBPTR_H
#include<memory>
#include<vector>
#include<string>
#include"StrBlob.h"

class StrBlob;
class StrBlobPtr {
	friend StrBlob;
public:
	StrBlobPtr():curr(0){ }
	StrBlobPtr(StrBlob &a, size_t sz = 0);
	std::string& deref() const;
	StrBlobPtr& incr();
	//递增和递减运算符
	StrBlobPtr& operator++();	//前置运算符
	StrBlobPtr& operator--();
	StrBlobPtr& operator++(int);	//后置运算符
	StrBlobPtr& operator--(int);

	std::string& operator*() const
	{
		auto p = check(curr, "dereference past end");
		return (*p)[curr];//(*P)是对象所指的vector
	}
	std::string* operator->() const
	{
		return & this->operator*();
	}
	
private:
	//若检查成功，check返回一个指向vector的share_ptr
	std::shared_ptr<std::vector<std::string>>
		check(std::size_t, const std::string&) const;
	//保存一个weak_ptr，意味着底层vector可能会被销毁
	std::weak_ptr<std::vector<std::string>> wptr;
	std::size_t curr;	//在数组中的当前位置
};

#endif // !STRBLOBPTR_