#pragma once
#ifndef BLOB_H
#define BLOB_H

#include<vector>
#include<initializer_list>
#include<memory>
#include <stdexcept>
#include <string>

//ǰ����������Blob��������Ԫ����Ҫ��
template <typename> class BlonPtr;
template <typename> class Blob;//�����==�еĲ�����Ҫ��
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
		return (*p)[curr];//(*P)Ϊ������ָ���vector
	}
	//�����͵ݼ�
	BlobPtr& operator++(int);//ǰ�������
	BlobPtr& operator--();
private:
	//�����ɹ���check����һ��ָ��vector��shared_ptr
	std::shared_ptr<std::vector<T>>
		check ( std::size_t, const std::string&) const;
	//����һ��weak_ptr����ʾ�ײ�vector���ܱ�����
	std::weak_ptr<std::vector<T>> wptr;
	std::size_t curr;//�����еĵ�ǰλ��
};


template <typename T> class Blob {
	//ÿ��Blobʵ��������Ȩ����������ͬ����ʵ������BlobPtr����������
	friend class BlobPtr<T>;
	friend bool operator==<T>
		(const Blob<T>&, const Blob<T>&);
public:
	typedef T value_type;
	typedef typename std::vector<T>::size_type size_type;
	//���캯��
	Blob();
	Blob(std::initializer_list<T> il);
	//Blob�е�Ԫ����Ŀ
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	//��Ӻ�ɾ��Ԫ��
	void push_back(const T &t) { data->push_back(t); }
	//�ƶ��汾
	void push_back(T &&t) { data->push_back(std::move(t)); }
	void pop_back();
	//Ԫ�ط���
	T& back();
	T& operator[](size_type i);

private:
	std::shared_ptr<std::vector<T>> data;
	//��data[i]��Ч�����׳�msg
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


//���ã��������ݼ����󵫷���ԭֵ
template <typename T>
BlobPtr<T>& BlobPtr<T>::operator++(int)
{
	//�˴������飻����ǰ�õ���ʱ����м��
	BlobPtr ret = *this;//���浱ǰֵ
	++*this;//�ƽ�һ��Ԫ�أ�ǰ��++�������Ƿ�Ϸ�
	return ret;//���ر����״̬
}


#endif // ! BLOB_H