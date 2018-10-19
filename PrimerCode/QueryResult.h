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
	//���붨��QueryResult::line_no
	//Ƕ�������ֱ��ʹ��������Ա������Ըó�Ա�����ֽ����޶�
	typedef std::set<line_no>::const_iterator line_it;
	//���ڲ���StrVec
	//std::shared_ptr<StrVec> f):
	QueryResult(std::string s,
		std::shared_ptr<std::set<line_no >> p,
		std::shared_ptr<std::vector<std::string>> f);

		line_it begin() const { return lines->cbegin(); }
		line_it end() const { return lines->cend(); }
		std::shared_ptr<std::vector<std::string>> get_file() { return file; }


private:
	std::string sought;	//��ѯ����
	std::shared_ptr<std::set<TextQuery::line_no>> lines;	//���ֵ��к�
	std::shared_ptr<std::vector<std::string>> file;	//�����ļ�

	//���ڲ���StrVec
	//std::shared_ptr<StrVec> file;	//�����ļ�

};

#endif // !QUERYRESULT_H
