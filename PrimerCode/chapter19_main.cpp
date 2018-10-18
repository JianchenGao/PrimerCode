#include<iostream>

#include"RTTI_test.h"
#include"Screen.h"

using namespace std;

void rtti_test();

int main()
{
	cout << "hello word!" << endl;
	//rtti_test();

	char (Screen::*pmf)() const;
	pmf = &Screen::get;

	char (Screen::*pmf2)(Screen::pos, Screen::pos) const;
	pmf2 = &Screen::get;

	Screen myScreen, *pScreen = &myScreen;

	char c1 = (pScreen->*pmf)();

	char c2 = (myScreen.*pmf2)(0, 0);

	Screen s;
	
	s = s.move(Screen::Directions::HOME);	//Screen::Directions::HOME访问类中的数据成员?????
	
	return 0;
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
