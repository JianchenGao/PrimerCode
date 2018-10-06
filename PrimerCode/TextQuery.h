#pragma once
#ifndef TEXTQUERY_H
#define TEXTQUERY_H

#include"StrVec.h"
#include<vector>
#include<memory>
#include<map>
#include<set>
//using line_no = std::vector<std::string>::size_type;//��Ϊ������ͷ�ļ���ҲҪʹ�ã����Բ�����������д�ķŵ�������

class QueryResult;//Ϊ�˶��庯��query�ķ������ͣ���������Ǳ����
class TextQuery {
public:
	using line_no = std::vector<std::string>::size_type;
	TextQuery(std::ifstream&);
	QueryResult query(const std::string&) const;
private:
	
	//���ڲ���StrVec
	//std::shared_ptr<StrVec> file;	//�����ļ�

	std::shared_ptr<std::vector<std::string>> file;	//�����ļ�
	//ÿ�����ʵ������ڵ��кŵļ��ϵ�ӳ��
	std::map<std::string, std::shared_ptr<std::set<line_no> > > wm;

};

#endif // !TEXTQUERY_H
