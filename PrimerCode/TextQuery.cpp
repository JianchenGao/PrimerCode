#include"TextQuery.h"
#include"QueryResult.h"
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>

using namespace std;

TextQuery::TextQuery(ifstream &is) :file(new vector<string>)
//���ڲ���StrVec
//TextQuery::TextQuery(ifstream &is) :file(new StrVec)
{
	string text;
	while (getline(is, text) ) {	//���ļ���ÿһ��
		file->push_back(text);		//���������ı�
		int n = file->size() - 1;	//��ǰ�к�
		istringstream line(text);	//�����ı��ֽ�Ϊ����
		string word;
		while (line >> word) {		//������ÿһ������
			//������ʲ���wm�У���֮Ϊ�±���wm�����һ��
			auto &lines = wm[word];	//lines��һ��shared_ptr
			if (!lines)	//�����ǵ�һ�������������ʱ����ָ��Ϊ��
				lines.reset(new set<line_no>);	//����һ���µ�set
			lines->insert(n);		//�����кŲ���set��
		}
	}
}

QueryResult
TextQuery::query(const string &sought) const
{
	//���Ϊ�ҵ�sought�����ǽ�����һ��ָ���set��ָ��
	static shared_ptr<set<line_no>> nodata(new set<line_no>);
	//ʹ��find�������±�����������ҵ��ʣ����⽫������ӵ�wm�У�
	auto loc = wm.find(sought);
	if (loc == wm.end())
		return QueryResult(sought, nodata, file);	//δ�ҵ�
	else
		return QueryResult(sought, loc->second, file);
}