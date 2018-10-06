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
	//Query::rep通过它的Query_base指针对rep()进行了虚调用
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
	//infile是一个ifstream,指向我们要处理的文件
	TextQuery tq(infile);	//保存文件并建立查询map
	//与用户交互：提示用户输入要查询的单词，完成查询并打印结果
	while (true){
		cout << "enter word to look for , or q to quit: ";
		string s;
		//若遇到文件尾或用户输入了‘q’时循环终止
		if (!(cin >> s) || s == "q") break;
		//指向查询并打印结果
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
	//如果找到单词，打印出现的次数和所有出现的位置
	os << qr.sought << " occurs " << qr.lines->size() << " "
		<< make_plural(qr.lines->size(), "time", "s") << endl;
	//打印单词出现的每一行
	for (auto num : *qr.lines)	//对set中每个单词
		//避免行号从0开始给用户带来的困惑
		os << "\t(line " << num + 1 << ")"
		<< *(qr.file->begin() + num) << endl;
	return os;
}

//chapter12_
void chapter12_main()
{
	ifstream in("D:\\Code\\C++\\C++ primer\\source\\chapter12-TextQuery\\chapter12-TextQuery\\Text.txt");	//打开文件
	//runQueries(in);
	Query q = Query("was") | Query("I");
	print(cout, q.eval(in)) << endl;

	system("pause");
}
