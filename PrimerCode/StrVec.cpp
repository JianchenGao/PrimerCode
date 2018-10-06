#include"StrVec.h"
#include<string>
#include<memory>

using namespace std;

void StrVec::push_back(const string& s)
{
	chk_n_alloc();	//确保有空间容纳新元素
	//在first_free指向的元素中构造s的副本
	alloc.construct(first_free++, s);
}

void StrVec::push_back(string &&s)
{
	chk_n_alloc();	//如果需要的话为StrVec重新分配内存
	alloc.construct(first_free++, std::move(s));
}

pair<string*,string*>
StrVec::alloc_n_copy(const string *b, const string *e)
{
	//分配空间保存给定范围中的元素
	auto data = alloc.allocate(e - b);
	//初始化并返回一个pair，该pair有data和uninitialied_copy的返回值构成
	return{ data,uninitialized_copy(b,e,data) };	//将数据复制到指定内存
}

void StrVec::free()
{
	//不能传递给deallocate一个空指针，如果elements为0，函数什么也不做
	if (elements) {
		//逆序销毁旧元素
		for (auto p = first_free; p != elements;/*空*/)
			alloc.destroy(--p);
		alloc.deallocate(elements, cap - elements);
	}
}

StrVec::StrVec(const StrVec &s)
{
	//调用alloc_n_copy分配空间以容纳与s中一样多的元素
	auto newdata = alloc_n_copy(s.begin(), s.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}

StrVec::StrVec(initializer_list<string> il)	//习题13.40
{
	//调用alloc_n_copy 分配与列表il中元素数目一样多的空间
	auto newdata = alloc_n_copy(il.begin(), il.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}

StrVec::~StrVec() { free(); }

StrVec &StrVec::operator=(const StrVec &rhs)
{
	//调用alloc_n_copy分配内存，大小与rhs中元素占用空间一样多
	auto data = alloc_n_copy(rhs.begin(), rhs.end());
	free();
	elements = data.first;
	first_free = cap = data.second;
	return *this;
}
StrVec &StrVec::operator=(std::initializer_list<std::string> il)
{
	//alloc_n_copy分配内存空间并从给定范围内拷贝元素
	auto data = alloc_n_copy(il.begin(), il.end());
	free();
	elements = data.first;
	first_free = cap = data.second;
	return *this;
}

StrVec &StrVec::operator=(StrVec &&rhs) noexcept
{
	//直接检测自赋值
	if (this != &rhs) {
		free();	//释放已有元素
		elements = rhs.elements;	//从rhs接管资源
		first_free = rhs.first_free;
		cap = rhs.cap;
		//将rhs置于可析构状态
		rhs.elements = rhs.first_free = rhs.cap = nullptr;
	}
	return *this;
}

void StrVec::reallocate()
{
	//我们将分配当前大小两倍的内存空间
	auto newcapacity = size() ? 2 * size() : 1;
	//分配新内存
	auto first = alloc.allocate(newcapacity);

	/*移动操作使用移动迭代器代替*/
	/*
	//将数据从旧内存移动到新内存
	auto dest = newdata;	//指向新数组中下一个空闲位置
	auto elem = elements;	//指向旧数组中下一个元素
	for (size_t i = 0; i != size(); ++i)
		alloc.construct(dest++, std::move(*elem++));
	*/

	//移动元素
	auto last = uninitialized_copy(make_move_iterator(begin()), make_move_iterator(end()), first);

	free();	//一旦我们移动完元素旧释放内存空间
	//更新我们的数据结构，执行新元素
	elements = first;
	first_free = last;
	cap = elements + newcapacity;
}

StrVec::StrVec(StrVec &&s) noexcept	//移动操作不应抛出异常
	//成员初始化器接管s中的资源
	:elements(s.elements),first_free(s.first_free),cap(s.cap)
{
	//令s进入这样的状态----对其析构函数是安全的
	s.elements = s.first_free = s.cap = nullptr;
}





