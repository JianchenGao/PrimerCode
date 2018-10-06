#include<iostream>
#include<vector>
#include<initializer_list>
#include<memory>
#include<stdexcept>
#include<string>
#include<sstream>

#include"Blob.h"
#include"DebugDelete.h"

using namespace std;

template <typename T> string debug_rep(const T &t);
template <typename T> string debug_rep(T *p);
string debug_rep(const string &s);
string debug_rep(char *p);
string debug_rep(const char *p);

template <typename T, typename... Args>
void foo(const T &t, const Args& ... rest);

template<typename T>
ostream &print(ostream &os, const T &t);
template <typename T, typename... Args>
ostream &print(ostream &os, const T &t, const Args&... rest);

template <typename T>
int compare(const T &v1, const T &v2);
template <unsigned N, unsigned M>
int compare(const char(&p1)[N], const char(&p2)[M]);
//compare的特殊版本，处理字符数组的指针
template <>
int compare(const char* const &p1, const char* const &p2);

int main()
{
	//实例化Blob<int>
	Blob<int> squares = { 0,1,2,3,4,5,6,7,8,9 };
	//实例化Blob<int>::size() const
	for (size_t i = 0; i != squares.size(); ++i)
		squares[i] = i*i;

	//测试成员模板
	double *p = new double;
	DebugDelete d;	//可像delete表达式一样使用的对象
	d(p);	//调用DebugDelete::operator()(double*),释放p
	int *ip = new int;
	//在一个临时DebugDelete对象上调用operator()(int*)
	DebugDelete()(ip);
	
	string s("hi");
	cout << debug_rep(s) << endl;
	cout << debug_rep(&s) << endl;
	cout << debug_rep(s) << endl;

	int i_foo = 0;
	double d_foo = 3.14;
	string s_foo = "how now brown cow";
	foo(i_foo, s_foo, 42, d_foo);
	foo(s_foo, 42, d_foo);
	foo(d_foo, s_foo);
	foo("hi");

	print(cout, i_foo, s_foo, 42);


	cout << "hello word!" << endl;
//	system("pause");
	return 0;
}

//打印任何我们不能处理的类型
template <typename T> string debug_rep(const T &t)
{
	ostringstream ret;
	ret << t;	//	使用T的输出运算符打印t的一个表示形式
	return ret.str();	//返回ret绑定的string的一个副本
}

//打印指针的值，后跟指针指向的对象
//注意：此函数不能用于char*;
template <typename T> string debug_rep(T *p)
{
	ostringstream ret;
	ret << "pointer : " << p;	//打印指针本身的值
	if (p)
		ret << " " << debug_rep(*p);	//打印p指向的值
	else
		ret << " null pointer ";	//或指出p为空
	return ret.str();	//返回ret绑定的string的一个副本
}

//打印双引号包围的string
string debug_rep(const string &s)
{
	return '"' + s + '"';
}

//将字符指针转换为string，并调用string版本的debug_reg
string debug_rep(char *p)
{
	return debug_rep(string(p));
}
string debug_rep(const char *p)
{
	return debug_rep(string(p));
}

template <typename T,typename... Args>
void foo(const T &t, const Args& ... rest)
{
	cout << sizeof...(Args) << endl;
	cout << sizeof...(rest) << endl;
}

//用来终止递归并打印最后一个元素的函数
//此函数必须在可变参数版本的print定义之前声明
template<typename T>
ostream &print(ostream &os, const T &t)
{
	return os << t;	//包含最后一个元素之后不打印分隔符
}

//包中除了最后一个元素之外的其他元素都会调用这个版本的print
template <typename T,typename... Args>
ostream &print(ostream &os, const T &t, const Args&... rest)
{
	os << t << ",";	//打印第一个实参
	return print(os, rest...);	//递归调用，打印其他实参
}

template <typename T>
int compare(const T &v1, const T &v2)
{
	if (v1 < v2) return -1;
	if (v2 < v1) return 1;
	return 0;
}

template <unsigned N,unsigned M>
int compare(const char (&p1)[N], const char(&p2)[M])
{
	return strcmp(p1,p2);
}

//compare的特殊版本，处理字符数组的指针
template <>
int compare(const char* const &p1, const char* const &p2)
{
	return strcmp(p1, p2);
}
