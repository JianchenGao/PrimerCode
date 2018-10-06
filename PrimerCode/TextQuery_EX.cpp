#include"TextQuery_EX.h"
#include<string>
#include<iostream>
#include<fstream>
#include<algorithm>

using namespace std;



void TextQuery_EX::print_test(const string &str)
{
	auto i = word.begin();
	for (int k = 0; k < 10; k++) {
		cout << i->first << endl;
		i++;
		//cout << i->second << endl;
	}
	cout << str << endl;
	//cout << *line.begin() << endl;
}

int TextQuery_EX::ReadText(const string &path)
{
	ifstream in(path);	//打开文件
	if (!in) 
	{
		cerr << "无法打开输入文件" << endl;
		return -1;
	}
	string _line;
	while (getline(in,_line))	//从文件中读取一行
	{
		line.push_back(_line);	//添加到类的line中
	}
	in.close();	//文本读取完毕

	int len = 0;	//记录行号
	for (auto &l : line) {	//先从line中取一行
		string w;
		for (auto &c : l) {	//读取每一行中的所有单词
			if (c != ' '&& c!=','&& c != '\''&& c != '"'&& c != '.') {
				w.push_back(c);	//将单个字符组成一个单词
			}
			else {	//一个完整的单词输入结束，将其存入Word中
				set<int> a = { len };
				auto ret = word.insert({ w,a });
				if (!ret.second) {	//若Word已经存在则对其中的set进行修改
					auto i = word.find(w);
					i->second.insert(len);
				}
				w.clear();
			}
		}
		len++;
	}
	return 0;
}

int TextQuery_EX::Serchword(const string &word_)
{
	if (word_.empty())	//检查输入是否合法
		cout << "the word is none" << endl;

	auto iter = word.find(word_);	//找到需要寻找的单词map结构

	if (iter == word.end()) {
		cout << "the word don't curr in the text" << endl;
		return 0;
	}

	set<int> n_line;
	n_line = iter->second;	//该单词出现的所有行

	auto count = n_line.size();	//出现的行的总数

	//sort(n_line.begin(), n_line.end());	//对出现的行排序

	cout << "the word current in " << count << " lines" << endl;	//先输出行总数

	for (auto i = n_line.begin(); i != n_line.end(); i++) {
		cout << *i << ":: ";	//输出行号
		cout << line.at(*i) << endl; //输出句子
	}
	return 0;
}