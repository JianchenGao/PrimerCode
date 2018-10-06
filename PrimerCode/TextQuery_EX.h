#pragma once
#ifndef TEXTQUERY_EX
#define TEXTQUERY_EX
#include<string>
#include<iostream>
#include<map>
#include<set>
#include<vector>


class TextQuery_EX
{
public:
	int ReadText(const std::string &path);
	int Serchword(const std::string &word);
	void print_test(const std::string &str);

private:
	std::vector<std::string> line;
	std::map< std::string, std::set<int> > word;

};


#endif