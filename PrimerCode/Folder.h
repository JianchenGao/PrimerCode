#pragma once
#ifndef FOLDER_H
#define FOLDER_H
#include<set>
#include<iostream>
#include"Message.h"

class Folder {
	friend class Message;
public:
	void addMsg(Message *);
	void remMsg(Message *);
	void print_msg()
	{
		for (auto m : Msgs)
			std::cout << m->contents << std::endl;
	}
	void add_to_Messages(const Folder &f);	//将这个Folder添加到所有Message中
	void remove_from_Msgs();	//将这个Folder从它所有Message中删除
	Folder() = default;
	Folder(const Folder &f) :Msgs(f.Msgs)	//拷贝构造函数
	{
		add_to_Messages(f);	//将Folder添加到它所有Message的folders中
	}
	~Folder()	//析构函数
	{
		remove_from_Msgs();
	}
	Folder& operator=(const Folder &rhs);	//赋值拷贝函数


private:
	std::set<Message *> Msgs;	//此Folder所存储的信息
};



#endif // !FOLDER