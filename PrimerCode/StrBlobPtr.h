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
	//�����͵ݼ������
	StrBlobPtr& operator++();	//ǰ�������
	StrBlobPtr& operator--();
	StrBlobPtr& operator++(int);	//���������
	StrBlobPtr& operator--(int);

	std::string& operator*() const
	{
		auto p = check(curr, "dereference past end");
		return (*p)[curr];//(*P)�Ƕ�����ָ��vector
	}
	std::string* operator->() const
	{
		return & this->operator*();
	}
	
private:
	//�����ɹ���check����һ��ָ��vector��share_ptr
	std::shared_ptr<std::vector<std::string>>
		check(std::size_t, const std::string&) const;
	//����һ��weak_ptr����ζ�ŵײ�vector���ܻᱻ����
	std::weak_ptr<std::vector<std::string>> wptr;
	std::size_t curr;	//�������еĵ�ǰλ��
};

#endif // !STRBLOBPTR_