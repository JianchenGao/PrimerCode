#include"HasPtr.h"

using namespace std;

HasPtr& HasPtr::operator=(const HasPtr &rhs)
{
	auto newp = new string(*rhs.ps);	//拷贝底层string
	delete ps;	//释放旧内存
	ps = newp;	//从右侧运算对象拷贝数据到本对象
	i = rhs.i;
	return *this;	//返回本对象
}