#pragma once
#ifndef QUERY_H
#define QUERY_H

#include<memory>
#include<map>
#include<set>

#include"TextQuery.h"
#include"QueryResult.h"
//extern std::ostream & operator<<(std::ostream &os, const Query &query);

class Query_base {
	friend class Query;
protected:
	using line_no = TextQuery::line_no;	//����eval����
	virtual ~Query_base() = default;
private:
	//eval �����뵱ǰQueryƥ���QueryResult
	virtual TextQuery::QueryResult eval(const TextQuery&) const = 0;
	//rep�Ǳ�ʾ��ѯ��һ��string
	virtual std::string rep() const = 0;
};

//����һ������Query_base�̳���ϵ�Ľӿ���
class Query {
	//��Щ�������Ҫ���ʽ���shared_ptr�Ĺ��캯�������ú�����˽�е�
	friend Query operator~(const Query &);
	friend Query operator|(const Query &,const Query &);
	friend Query operator&(const Query &,const Query &);
public:
	Query(const std::string&);	//����һ���µ�WordQuery
	//�ӿں��������ö�Ӧ��Query_base����
	TextQuery::QueryResult eval(const TextQuery &t) const
	{
		return q->eval(t);
	}
	std::string rep() const { return q->rep(); }

private:
	Query(std::shared_ptr<Query_base> query ):q(query){ }
	std::shared_ptr<Query_base> q;

};

class WordQuery :public Query_base {
	friend class Query;		//Queryʹ��WordQuery���캯��
	WordQuery(const std::string &s):query_word(s){ }
	//������ࣺWordQuery���������м̳ж����Ĵ��麯��
	TextQuery::QueryResult eval(const TextQuery &t) const
	{
		return t.query(query_word);
	}
	std::string rep() const { return query_word; }
	std::string query_word;		//Ҫ���ҵĵ���
};

inline
Query::Query(const std::string &s):q(new WordQuery(s)){ }

class NotQuery :public Query_base {
	friend Query operator~(const Query &);
	NotQuery(const Query &q):query(q) { }
	//������ࣺNotQuery���������м̳ж����Ĵ��麯��
	std::string rep() const { return "~(" + query.rep() + ")"; }
	TextQuery::QueryResult eval(const TextQuery &) const;
	Query query;
};

inline Query operator~(const Query &operand)
{
	return std::shared_ptr<Query_base>(new NotQuery(operand));
}

class BinaryQuery :public Query_base {
protected:
	BinaryQuery(const Query &l,const Query &r,std::string s):
		lhs(l),rhs(r),opSym(s){ }
	//�����ࣺBinaryQuery������eval
	std::string rep() const { return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")"; }
	Query lhs, rhs;	//	�����Ҳ������
	std::string opSym;	//�����������
};

class AndQuery :public BinaryQuery {
	friend Query operator&(const Query &, const Query &);
	AndQuery(const Query &left,const Query &right):
		BinaryQuery(left,right,"&"){ }
	//������ࣺAndQuery�̳���rep���Ҷ������������麯��
	TextQuery::QueryResult eval(const TextQuery&) const;
};

inline Query operator&(const Query &lhs, const Query &rhs)
{
	return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}

class OrQuery :public BinaryQuery {
	friend Query operator|(const Query&, const Query&);
	OrQuery(const Query &left,const Query &right):
		BinaryQuery(left,right,"|"){ }
	TextQuery::QueryResult eval(const TextQuery&) const;
};

inline Query operator|(const Query &lhs, const Query &rhs)
{
	return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}

#endif // !QUERY_H