#include<iostream>

#include"RTTI_test.h"
#include"Screen.h"
#include<string>
#include<vector>
#include<algorithm>
#include<functional>

using namespace std;

void rtti_test();
void pointerToMember_example();
ostream & operator<<(ostream& os, vector<string> vec_s);
ostream & operator<<(ostream& os, vector<string*> vec_s);

union Token {
	//默认情况下成员是公有的
	char cval;
	int ival;
	double dval;
};

//chapter19_
int main()
{
	cout << "hello word!" << endl;
	//rtti_test();
	//pointerToMember_example();


	
	return 0;
}


void pointerToMember_example()
{

	char (Screen::*pmf)() const;
	pmf = &Screen::get;

	char (Screen::*pmf2)(Screen::pos, Screen::pos) const;
	pmf2 = &Screen::get;

	Screen myScreen, *pScreen = &myScreen;

	char c1 = (pScreen->*pmf)();
	char c2 = (myScreen.*pmf2)(0, 0);

	Screen s;
	s = s.move(Screen::Directions::HOME);

	vector<string> v;
	vector<string*> pvec;
	string s1("ppp");
	string s2("");
	string *pn = &s2, *ps = &s1;
	for (int i = 1; i < 20; i++) {
		if (i % 4 == 0) {
			v.push_back("");
			pvec.push_back(pn);
		}
		else {
			v.push_back("abc");
			pvec.push_back(ps);
		}
	}

	function<bool(const string)> fp = &string::empty;
	auto i = find_if(v.begin(), v.end(), fp);
	*i = "iii";

	auto n = count_if(v.begin(), v.end(), fp);
	cout << "n is : " << n << endl;

	cout << v << endl;
	cout << pvec << endl;
}

void rtti_test()
{
	Base b1("b1", 0.1f);
	Base b2("b2", 0.2f);
	Base B1("b1", 0.1f);
	Derived d1("d1", 0.1f, 1);
	Derived d2("d2", 0.1f, 1);
	Derived D1("d1", 0.1f, 1);
	Derived D2("b2", 0.2f, 1);

	cout << (b1 == b2) << endl;
	cout << (b1 == B1) << endl;
	cout << (b1 == d1) << endl;

	cout << (d1 == d2) << endl;
	cout << (d1 == D1) << endl;
	cout << (D2 == b2) << endl;
}

ostream & operator<<(ostream& os, vector<string> vec_s)
{
	for (auto vec : vec_s) {
		os << vec << " ";
	}
	return os;
}

ostream & operator<<(ostream& os, vector<string*> vec_s)
{
	for (auto vec : vec_s) {
		os << *vec << " ";
	}
	return os;
}
