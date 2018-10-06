#pragma once
#ifndef BLOB_H
#define BLOB_H

#include<vector>
#include<initializer_list>
#include<memory>
#include <stdexcept>
#include <string>

//前置声明，在Blob中声明友元所需要的
template <typename> class BlonPtr;
template <typename> class Blob;//运算符==中的参数需要的
template <typename T>
bool operator==(const Blob<T>&, const Blob<T>&);

template <typename T> class BlobPtr {
public:
	BlobPtr():curr(0) { }
	BlobPtr(Blob<T> &a, size_t sz = 0):
		wptr(a.data),curr(sz) { }
	T& operator*() const
	{
		auto p = check(curr, "dereference past end");
		return (*p)[curr];//(*P)为本对象指向的vector
	}
	//递增和递减
	BlobPtr& operator++(int);//前置运算符
	BlobPtr& operator--();
private:
	//若检查成功，check返回一个指向vector的shared_ptr
	std::shared_ptr<std::vector<T>>
		check ( std::size_t, const std::string&) const;
	//保存一个weak_ptr，表示底层vector可能被销毁
	std::weak_ptr<std::vector<T>> wptr;
	std::size_t curr;//数组中的当前位置
};


template <typename T> class Blob {
	//每个Blob实例将访问权限授予用相同类型实例化的BlobPtr和相等运算符
	friend class BlobPtr<T>;
	friend bool operator==<T>
		(const Blob<T>&, const Blob<T>&);
public:
	typedef T value_type;
	typedef typename std::vector<T>::size_type size_type;
	//构造函数
	Blob();
	Blob(std::initializer_list<T> il);
	//Blob中的元素数目
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	//添加和删除元素
	void push_back(const T &t) { data->push_back(t); }
	//移动版本
	void push_back(T &&t) { data->push_back(std::move(t)); }
	void pop_back();
	//元素访问
	T& back();
	T& operator[](size_type i);

private:
	std::shared_ptr<std::vector<T>> data;
	//若data[i]无效，则抛出msg
	void check(size_type i, const std::string &msg) const;
};

template <typename T>
void Blob<T>::check(size_type i, const std::string &msg) const
{
	if (i >= data->size())
		throw std::out_of_range(msg);
}

template <typename T>
T& Blob<T>::back()
{
	check(0, "back on empty Blob");
	return data->back();
}

template <typename T>
T& Blob<T>::operator[](size_type i)
{
	check(i, "subscript out of range");
	return (*data)[i];
}

template <typename T>
void Blob<T>::pop_back()
{
	check(0, "pop_back on empyt Blob");
	data->pop_back();
}

template <typename T>
Blob<T>::Blob() :data(std::make_shared<std::vector<T>>()) { }

template <typename T>
Blob<T>::Blob(std::initializer_list<T> il) : data(std::make_shared<std::vector<T>>(il)) { }


//后置：递增、递减对象但返回原值
template <typename T>
BlobPtr<T>& BlobPtr<T>::operator++(int)
{
	//此处无须检查；调用前置递增时会进行检查
	BlobPtr ret = *this;//保存当前值
	++*this;//推进一个元素；前置++检查递增是否合法
	return ret;//返回保存的状态
}


#endif // ! BLOB_H