#include<iostream>
#include <string>
#include<fstream>
#include"TextQuery_EX.h"
#include"QueryResult.h"
#include"TextQuery.h"
#include"Query.h"

using namespace std;

std::ostream &
operator<<(std::ostream &os, const Query &query)
{
	//Query::repͨ������Query_baseָ���rep()�����������
	return os << query.rep();
}

int main_EX(void)
{
	TextQuery_EX aa;
	aa.ReadText("D:\\Code\\C++\\C++ primer\\source\\chapter12-TextQuery\\chapter12-TextQuery\\Text.txt");
	string serch_w;
	while (true)
	{
		cout << "please input a word" << endl;
		cin >> serch_w;
		aa.Serchword(serch_w);
	}

	system("pause");
	return 0;
}

void runQueries(ifstream &infile)
{
	//infile��һ��ifstream,ָ������Ҫ������ļ�
	TextQuery tq(infile);	//�����ļ���������ѯmap
	//���û���������ʾ�û�����Ҫ��ѯ�ĵ��ʣ���ɲ�ѯ����ӡ���
	while (true){
		cout << "enter word to look for , or q to quit: ";
		string s;
		//�������ļ�β���û������ˡ�q��ʱѭ����ֹ
		if (!(cin >> s) || s == "q") break;
		//ָ���ѯ����ӡ���
		print(cout, tq.query(s)) << endl;
	}
}

string make_plural(size_t ctr, const string &word,
	const string &ending)
{
	return (ctr > 1) ? word + ending : word;
}

ostream &print(ostream &os, const QueryResult &qr)
{
	//����ҵ����ʣ���ӡ���ֵĴ��������г��ֵ�λ��
	os << qr.sought << " occurs " << qr.lines->size() << " "
		<< make_plural(qr.lines->size(), "time", "s") << endl;
	//��ӡ���ʳ��ֵ�ÿһ��
	for (auto num : *qr.lines)	//��set��ÿ������
		//�����кŴ�0��ʼ���û�����������
		os << "\t(line " << num + 1 << ")"
		<< *(qr.file->begin() + num) << endl;
	return os;
}

//chapter12_
void chapter12_main()
{
	ifstream in("D:\\Code\\C++\\C++ primer\\source\\chapter12-TextQuery\\chapter12-TextQuery\\Text.txt");	//���ļ�
	//runQueries(in);
	Query q = Query("was") | Query("I");
	print(cout, q.eval(in)) << endl;

	system("pause");
}
