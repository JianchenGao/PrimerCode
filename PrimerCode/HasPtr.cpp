#include"HasPtr.h"

using namespace std;

HasPtr& HasPtr::operator=(const HasPtr &rhs)
{
	auto newp = new string(*rhs.ps);	//�����ײ�string
	delete ps;	//�ͷž��ڴ�
	ps = newp;	//���Ҳ�������󿽱����ݵ�������
	i = rhs.i;
	return *this;	//���ر�����
}