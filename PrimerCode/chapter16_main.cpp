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
//compare������汾�������ַ������ָ��
template <>
int compare(const char* const &p1, const char* const &p2);

int main()
{
	//ʵ����Blob<int>
	Blob<int> squares = { 0,1,2,3,4,5,6,7,8,9 };
	//ʵ����Blob<int>::size() const
	for (size_t i = 0; i != squares.size(); ++i)
		squares[i] = i*i;

	//���Գ�Աģ��
	double *p = new double;
	DebugDelete d;	//����delete���ʽһ��ʹ�õĶ���
	d(p);	//����DebugDelete::operator()(double*),�ͷ�p
	int *ip = new int;
	//��һ����ʱDebugDelete�����ϵ���operator()(int*)
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

//��ӡ�κ����ǲ��ܴ��������
template <typename T> string debug_rep(const T &t)
{
	ostringstream ret;
	ret << t;	//	ʹ��T������������ӡt��һ����ʾ��ʽ
	return ret.str();	//����ret�󶨵�string��һ������
}

//��ӡָ���ֵ�����ָ��ָ��Ķ���
//ע�⣺�˺�����������char*;
template <typename T> string debug_rep(T *p)
{
	ostringstream ret;
	ret << "pointer : " << p;	//��ӡָ�뱾���ֵ
	if (p)
		ret << " " << debug_rep(*p);	//��ӡpָ���ֵ
	else
		ret << " null pointer ";	//��ָ��pΪ��
	return ret.str();	//����ret�󶨵�string��һ������
}

//��ӡ˫���Ű�Χ��string
string debug_rep(const string &s)
{
	return '"' + s + '"';
}

//���ַ�ָ��ת��Ϊstring��������string�汾��debug_reg
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

//������ֹ�ݹ鲢��ӡ���һ��Ԫ�صĺ���
//�˺��������ڿɱ�����汾��print����֮ǰ����
template<typename T>
ostream &print(ostream &os, const T &t)
{
	return os << t;	//�������һ��Ԫ��֮�󲻴�ӡ�ָ���
}

//���г������һ��Ԫ��֮�������Ԫ�ض����������汾��print
template <typename T,typename... Args>
ostream &print(ostream &os, const T &t, const Args&... rest)
{
	os << t << ",";	//��ӡ��һ��ʵ��
	return print(os, rest...);	//�ݹ���ã���ӡ����ʵ��
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

//compare������汾�������ַ������ָ��
template <>
int compare(const char* const &p1, const char* const &p2)
{
	return strcmp(p1, p2);
}
