#pragma once
#ifndef TEXTQUERY_H
#define TEXTQUERY_H

#include"StrVec.h"
#include<vector>
#include<memory>
#include<map>
#include<set>
//using line_no = std::vector<std::string>::size_type;//因为在其他头文件中也要使用，所以不能像书中所写的放到类里面

//class QueryResult;//为了定义函数query的返回类型，这个定义是必须的
class TextQuery {
public:
	class QueryResult;	//嵌套类稍后定义
	using line_no = std::vector<std::string>::size_type;
	TextQuery(std::ifstream&);
	QueryResult query(const std::string&) const;
private:
	
	//用于测试StrVec
	//std::shared_ptr<StrVec> file;	//输入文件

	std::shared_ptr<std::vector<std::string>> file;	//输入文件
	//每个单词到它所在的行号的集合的映射
	std::map<std::string, std::shared_ptr<std::set<line_no> > > wm;

};

#endif // !TEXTQUERY_H
