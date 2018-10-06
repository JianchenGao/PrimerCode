#include"StrVec.h"
#include<string>
#include<memory>

using namespace std;

void StrVec::push_back(const string& s)
{
	chk_n_alloc();	//ȷ���пռ�������Ԫ��
	//��first_freeָ���Ԫ���й���s�ĸ���
	alloc.construct(first_free++, s);
}

void StrVec::push_back(string &&s)
{
	chk_n_alloc();	//�����Ҫ�Ļ�ΪStrVec���·����ڴ�
	alloc.construct(first_free++, std::move(s));
}

pair<string*,string*>
StrVec::alloc_n_copy(const string *b, const string *e)
{
	//����ռ䱣�������Χ�е�Ԫ��
	auto data = alloc.allocate(e - b);
	//��ʼ��������һ��pair����pair��data��uninitialied_copy�ķ���ֵ����
	return{ data,uninitialized_copy(b,e,data) };	//�����ݸ��Ƶ�ָ���ڴ�
}

void StrVec::free()
{
	//���ܴ��ݸ�deallocateһ����ָ�룬���elementsΪ0������ʲôҲ����
	if (elements) {
		//�������پ�Ԫ��
		for (auto p = first_free; p != elements;/*��*/)
			alloc.destroy(--p);
		alloc.deallocate(elements, cap - elements);
	}
}

StrVec::StrVec(const StrVec &s)
{
	//����alloc_n_copy����ռ���������s��һ�����Ԫ��
	auto newdata = alloc_n_copy(s.begin(), s.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}

StrVec::StrVec(initializer_list<string> il)	//ϰ��13.40
{
	//����alloc_n_copy �������б�il��Ԫ����Ŀһ����Ŀռ�
	auto newdata = alloc_n_copy(il.begin(), il.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}

StrVec::~StrVec() { free(); }

StrVec &StrVec::operator=(const StrVec &rhs)
{
	//����alloc_n_copy�����ڴ棬��С��rhs��Ԫ��ռ�ÿռ�һ����
	auto data = alloc_n_copy(rhs.begin(), rhs.end());
	free();
	elements = data.first;
	first_free = cap = data.second;
	return *this;
}
StrVec &StrVec::operator=(std::initializer_list<std::string> il)
{
	//alloc_n_copy�����ڴ�ռ䲢�Ӹ�����Χ�ڿ���Ԫ��
	auto data = alloc_n_copy(il.begin(), il.end());
	free();
	elements = data.first;
	first_free = cap = data.second;
	return *this;
}

StrVec &StrVec::operator=(StrVec &&rhs) noexcept
{
	//ֱ�Ӽ���Ը�ֵ
	if (this != &rhs) {
		free();	//�ͷ�����Ԫ��
		elements = rhs.elements;	//��rhs�ӹ���Դ
		first_free = rhs.first_free;
		cap = rhs.cap;
		//��rhs���ڿ�����״̬
		rhs.elements = rhs.first_free = rhs.cap = nullptr;
	}
	return *this;
}

void StrVec::reallocate()
{
	//���ǽ����䵱ǰ��С�������ڴ�ռ�
	auto newcapacity = size() ? 2 * size() : 1;
	//�������ڴ�
	auto first = alloc.allocate(newcapacity);

	/*�ƶ�����ʹ���ƶ�����������*/
	/*
	//�����ݴӾ��ڴ��ƶ������ڴ�
	auto dest = newdata;	//ָ������������һ������λ��
	auto elem = elements;	//ָ�����������һ��Ԫ��
	for (size_t i = 0; i != size(); ++i)
		alloc.construct(dest++, std::move(*elem++));
	*/

	//�ƶ�Ԫ��
	auto last = uninitialized_copy(make_move_iterator(begin()), make_move_iterator(end()), first);

	free();	//һ�������ƶ���Ԫ�ؾ��ͷ��ڴ�ռ�
	//�������ǵ����ݽṹ��ִ����Ԫ��
	elements = first;
	first_free = last;
	cap = elements + newcapacity;
}

StrVec::StrVec(StrVec &&s) noexcept	//�ƶ�������Ӧ�׳��쳣
	//��Ա��ʼ�����ӹ�s�е���Դ
	:elements(s.elements),first_free(s.first_free),cap(s.cap)
{
	//��s����������״̬----�������������ǰ�ȫ��
	s.elements = s.first_free = s.cap = nullptr;
}





