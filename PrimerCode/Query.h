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
	using line_no = TextQuery::line_no;	//用于eval函数
	virtual ~Query_base() = default;
private:
	//eval 返回与当前Query匹配的QueryResult
	virtual TextQuery::QueryResult eval(const TextQuery&) const = 0;
	//rep是表示查询的一个string
	virtual std::string rep() const = 0;
};

//这是一个管理Query_base继承体系的接口类
class Query {
	//这些运算符需要访问接受shared_ptr的构造函数，而该函数是私有的
	friend Query operator~(const Query &);
	friend Query operator|(const Query &,const Query &);
	friend Query operator&(const Query &,const Query &);
public:
	Query(const std::string&);	//构建一个新的WordQuery
	//接口函数：调用对应的Query_base操作
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
	friend class Query;		//Query使用WordQuery构造函数
	WordQuery(const std::string &s):query_word(s){ }
	//具体的类：WordQuery将定义所有继承而来的纯虚函数
	TextQuery::QueryResult eval(const TextQuery &t) const
	{
		return t.query(query_word);
	}
	std::string rep() const { return query_word; }
	std::string query_word;		//要查找的单词
};

inline
Query::Query(const std::string &s):q(new WordQuery(s)){ }

class NotQuery :public Query_base {
	friend Query operator~(const Query &);
	NotQuery(const Query &q):query(q) { }
	//具体的类：NotQuery将定义所有继承而来的纯虚函数
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
	//抽象类：BinaryQuery不定义eval
	std::string rep() const { return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")"; }
	Query lhs, rhs;	//	左侧和右侧运算符
	std::string opSym;	//运算符的名字
};

class AndQuery :public BinaryQuery {
	friend Query operator&(const Query &, const Query &);
	AndQuery(const Query &left,const Query &right):
		BinaryQuery(left,right,"&"){ }
	//具体的类：AndQuery继承了rep并且定义了其他纯虚函数
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