#include "Screen.h"

void Screen::some_member() const
{
	++access_ctr;
}

Screen& Screen::move(Directions cm)
{
	//����this����������ֵΪcm��Ԫ��
	return (this->*Menu[cm])();	//Menu[cm]ָ��һ����Ա����
}

Screen::Action Screen::Menu[] = {
	&Screen::home,
	&Screen::forward,
	&Screen::back,
	&Screen::up,
	&Screen::down,
};