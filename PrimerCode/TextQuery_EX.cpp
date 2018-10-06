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
	ifstream in(path);	//���ļ�
	if (!in) 
	{
		cerr << "�޷��������ļ�" << endl;
		return -1;
	}
	string _line;
	while (getline(in,_line))	//���ļ��ж�ȡһ��
	{
		line.push_back(_line);	//��ӵ����line��
	}
	in.close();	//�ı���ȡ���

	int len = 0;	//��¼�к�
	for (auto &l : line) {	//�ȴ�line��ȡһ��
		string w;
		for (auto &c : l) {	//��ȡÿһ���е����е���
			if (c != ' '&& c!=','&& c != '\''&& c != '"'&& c != '.') {
				w.push_back(c);	//�������ַ����һ������
			}
			else {	//һ�������ĵ�������������������Word��
				set<int> a = { len };
				auto ret = word.insert({ w,a });
				if (!ret.second) {	//��Word�Ѿ�����������е�set�����޸�
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
	if (word_.empty())	//��������Ƿ�Ϸ�
		cout << "the word is none" << endl;

	auto iter = word.find(word_);	//�ҵ���ҪѰ�ҵĵ���map�ṹ

	if (iter == word.end()) {
		cout << "the word don't curr in the text" << endl;
		return 0;
	}

	set<int> n_line;
	n_line = iter->second;	//�õ��ʳ��ֵ�������

	auto count = n_line.size();	//���ֵ��е�����

	//sort(n_line.begin(), n_line.end());	//�Գ��ֵ�������

	cout << "the word current in " << count << " lines" << endl;	//�����������

	for (auto i = n_line.begin(); i != n_line.end(); i++) {
		cout << *i << ":: ";	//����к�
		cout << line.at(*i) << endl; //�������
	}
	return 0;
}