#pragma once
#include<iostream>
#include<string>

class PrintString {
public:
	PrintString(std::ostream &o = std::cout,char c = ' '):
		os(o),sep(c) { }
	void operator()(const std::string &s) const { os << s << sep; }
private:
	std::ostream &os;	//用于写入的目的流
	char sep;	//用于将不同输出隔开的字符
};