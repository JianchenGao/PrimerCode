#include "Screen.h"

void Screen::some_member() const
{
	++access_ctr;
}

Screen& Screen::move(Directions cm)
{
	//运行this对象中索引值为cm的元素
	return (this->*Menu[cm])();	//Menu[cm]指向一个成员函数
}

Screen::Action Screen::Menu[] = {
	&Screen::home,
	&Screen::forward,
	&Screen::back,
	&Screen::up,
	&Screen::down,
};