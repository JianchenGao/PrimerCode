#include<memory>
#include<set>
#include<algorithm>
#include<iterator>

#include"Query.h"

using namespace std;


QueryResult
OrQuery::eval(const TextQuery& text) const
{
	//ͨ��Query��Աlhs��rhs���е������
	//����eval����ÿ����������QueryResult
	auto right = rhs.eval(text), left = lhs.eval(text);
	//��������������кſ��������set��
	auto ret_lines =
		make_shared<set<line_no>>(left.begin(), left.end());
	//�����Ҳ�����������õ��к�
	ret_lines->insert(right.begin(), right.end());
	//����һ���µ�QueryResult������ʾlhs��rhs�Ĳ���
	return QueryResult(rep(), ret_lines, left.get_file());
}

QueryResult
AndQuery::eval(const TextQuery& text) const
{
	//ͨ��Query���������е�����ã��Ի���������Ĳ�ѯ���set
	auto left = lhs.eval(text), right = rhs.eval(text);
	//����left��right������set
	auto ret_lines = make_shared<set<line_no>>();
	//��������Χ�Ľ���д��һ��Ŀ�ĵ�������
	//���ε��õ�Ŀ�ĵ�������ret���Ԫ��
	set_intersection(left.begin(), left.end(),
		right.begin(), right.end(),
		inserter(*ret_lines, ret_lines->begin()));
	return QueryResult(rep(), ret_lines, left.get_file());
}

QueryResult
NotQuery::eval(const TextQuery& text) const
{
	//ͨ��Query��������eval���������
	auto result = query.eval(text);
	//��ʼʱ���setΪ��
	auto ret_lines = make_shared<set<line_no>>();
	//���Ǳ��������������ֵ��������н��е���
	auto beg = result.begin(), end = result.end();
	//�������ļ���ÿһ�У�������в���result���У�������ӵ�ret_lines
	auto sz = result.get_file()->size();
	for (size_t n = 0; n != sz; ++n) {
		//������ǻ�û�д�����result��������
		//��鵱ǰ�Ƿ����
		if (beg == end || *beg != n)
			ret_lines->insert(n);	//�������result���У������һ��
		else if (beg != end)
			++beg;	//���������ȡresult����һ�У�����еĻ���
	}
	return QueryResult(rep(), ret_lines, result.get_file());
}

