#pragma once
#ifndef SCREEN_H
#define SCREEN_H

#include<string>
#include<iostream>


class Screen {
public:

	friend class Window_mgr;

	//Action是一个指针，可以用任意一个光标移动函数对其赋值
	using Action = Screen & (Screen::*)();
	//指定具体要移动的方向
	enum Directions {HOME,FORWARD,BACK,UP,DOWN};
	Screen& move(Directions);

	Screen& home() { std::cout << "home" << std::endl; return *this; }
	Screen& forward() { std::cout << "forward" << std::endl; return *this;}
	Screen& back() { std::cout << "back" << std::endl; return *this;}
	Screen& up() { std::cout << "up" << std::endl; return *this;}
	Screen& down() { std::cout << "down" << std::endl; return *this;}


	typedef std::string::size_type pos;
	//Screen() = default;
	
	Screen(pos ht, pos wd, char c) :height(ht), width(wd),
		contents(ht*wd, c) { }
	Screen(pos ht = 0, pos wd = 0) :
		cursor(0), height(ht), width(wd), contents(ht * wd, ' ') { }
	char get() const
	{
		return contents[cursor];
	}
	inline char get(pos ht, pos wd) const;
	Screen &move(pos r, pos c);
	Screen &set(char);
	Screen &set(pos, pos, char);

	void some_member() const;
	
	Screen &display(std::ostream &os)
	{
		do_display(os); return *this;
	}
	const Screen &display(std::ostream &os) const//此处的const有何用？？
	{
		do_display(os); return *this;
	}

private:
	// function to do the work of displaying a Screen
	void do_display(std::ostream &os) const { os << contents; }
	// other members as before

	pos cursor = 0;
	pos height = 0, width = 0;
	std::string contents;

	mutable size_t access_ctr;

	static Action Menu[];
};

inline                   // we can specify inline on the definition
Screen &Screen::move(pos r, pos c)
{
	pos row = r * width; // compute the row location
	cursor = row + c;    // move cursor to the column within that row
	return *this;        // return this object as an lvalue
}

char Screen::get(pos r, pos c) const // declared as inline in the class
{
	pos row = r * width;      // compute row location
	return contents[row + c]; // return character at the given column
}

inline Screen &Screen::set(char c)
{
	contents[cursor] = c; // set the new value at the current cursor location
	return *this;         // return this object as an lvalue
}
inline Screen &Screen::set(pos r, pos col, char ch)
{
	contents[r*width + col] = ch;  // set specified location to given value
	return *this;                  // return this object as an lvalue
}


#endif // !SALES_DATA_H
