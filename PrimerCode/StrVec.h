#pragma once
#ifndef STRVEC
#define STRVEC

#define  _SCL_SECURE_NO_WARNINGS

#include<string>
#include<initializer_list>
#include<memory>
#include<utility>

//��vector���ڴ������Եļ�ʵ��
class StrVec {
public:
	StrVec() :	//allocator��Ա����Ĭ�ϳ�ʼ��
		elements(nullptr), first_free(nullptr), cap(nullptr) { }
	StrVec(std::initializer_list<std::string> il);
	StrVec(const StrVec&);	//�������캯��
	StrVec(StrVec &&) noexcept;	//�ƶ����캯��
	StrVec &operator=(const StrVec&);	//������ֵ�����
	StrVec &operator=(StrVec &&) noexcept;	//�ƶ���ֵ�����
	StrVec &operator=(std::initializer_list<std::string>);
	~StrVec();	//��������
	void push_back(const std::string&);	//����Ԫ��
	void push_back(std::string&&);	//�ƶ�Ԫ��
	size_t size() const { return first_free - elements; }
	size_t capacity() const { return cap - elements; }
	std::string *begin() const { return elements; }
	std::string *end() const { return first_free; }
	std::string& operator[](std::size_t n)
	{
		return elements[n];
	}
	const std::string& operator[](std::size_t n) const
	{
		return elements[n];
	}

	//ת����ʾ��
	template<class... Args> void emplace_back(Args&&...);

private:
	//static std::allocator<std::string> alloc;	//����Ԫ��
	std::allocator<std::string> alloc;	//����Ԫ��

										//�����Ԫ�صĺ�����ʹ��
	void chk_n_alloc()
	{
		if (size() == capacity()) reallocate();
	}
	//���ߺ�������������������ֵ�����������������ʹ��
	std::pair < std::string*, std::string*> alloc_n_copy
	(const std::string*, const std::string*);
	void free();	//����Ԫ�ز��ͷ��ڴ�
	void reallocate();	//��ø����ڴ沢��������Ԫ��
	std::string *elements;	//ָ��������Ԫ�ص�ָ��
	std::string *first_free;	//ָ�������һ������Ԫ�ص�ָ��
	std::string *cap;	//ָ������β��λ�õ�ָ��
};

template<class... Args>
inline
void StrVec::emplace_back(Args&&... args)
{
	chk_n_alloc();
	alloc.construct(first_free++, std::forward<Args>(args)...);
}

#endif // !STRVEC