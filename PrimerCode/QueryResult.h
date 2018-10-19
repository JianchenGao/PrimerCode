#pragma once
#ifndef QUERYRESULT_H
#define QUERYRESULT_H

#include"TextQuery.h"
#include<ostream>
#include<memory>
#include<set>
#include<vector>
#include<string>

class TextQuery::QueryResult {
	friend std::ostream& print(std::ostream&, const QueryResult&);
public:
	//typedef std::vector<std::string>::size_type line_no;
	//无须定义QueryResult::line_no
	//嵌套类可以直接使用外层类成员，无须对该成员的名字进行限定
	typedef std::set<line_no>::const_iterator line_it;
	//用于测试StrVec
	//std::shared_ptr<StrVec> f):
	QueryResult(std::string s,
		std::shared_ptr<std::set<line_no >> p,
		std::shared_ptr<std::vector<std::string>> f);

		line_it begin() const { return lines->cbegin(); }
		line_it end() const { return lines->cend(); }
		std::shared_ptr<std::vector<std::string>> get_file() { return file; }


private:
	std::string sought;	//查询单词
	std::shared_ptr<std::set<TextQuery::line_no>> lines;	//出现的行号
	std::shared_ptr<std::vector<std::string>> file;	//输入文件

	//用于测试StrVec
	//std::shared_ptr<StrVec> file;	//输入文件

};

#endif // !QUERYRESULT_H
