#pragma once
#ifndef WINDOW_MGR_H
#define WINDOW_MGR_H

#include <vector>
#include <string>
#include <iostream>
#include "Screen.h"

class Window_mgr {
public:
	using ScreenIndex = std::vector<Screen>::size_type;

	ScreenIndex addScreen(const Screen&);
	void clear(ScreenIndex);

private:
	// Screens this Window_mgr is tracking
	// by default, a Window_mgr has one standard sized blank Screen 
	std::vector<Screen> screens{ Screen(24, 80, ' ') };//P246
};

inline
void Window_mgr::clear(ScreenIndex i)
{
	// s is a reference to the Screen we want to clear
	Screen &s = screens[i];
	// reset the contents of that Screen to all blanks
	s.contents = std::string(s.height * s.width, ' ');
}

// return type is seen before we're in the scope of Window_mgr
inline
Window_mgr::ScreenIndex
Window_mgr::addScreen(const Screen &s)
{
	screens.push_back(s);
	return screens.size() - 1;
}


#endif // !WINDOW_MGR_H
