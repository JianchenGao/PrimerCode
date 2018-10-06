#pragma once
#ifndef MESSAGE_H
#define MESSAGE_H

#include<string>
#include<set>


class Message {
	friend class Folder;
	friend void swap(Message &lhs, Message &rhs);
public:
	//folders被隐式初始化为空集合
	explicit Message(const std::string &str = ""):
		contents(str) { }
	//拷贝控制成员，用来管理指向本Message的指针
	Message(const Message&);	//拷贝构造函数
	Message(Message &&);
	Message& operator=(const Message&);	//拷贝赋值运算符
	Message& operator=(Message &&);	//移动赋值运算符
	~Message();	//析构函数
	//从给定Folder集合中添加/删除本Message
	void save(Folder&);
	void remove(Folder&);
	void addFldr(Folder *f) { folders.insert(f); }//添加给定Folder
	void add_to_Folders(const Message &m);
	void remove_from_Folders();
	void move_Folders(Message *m);	//从本Message移动Folder指针
private:
	std::string contents;	//实际消息文本
	std::set<Folder*> folders;	//
};

#endif // !MESSAGE
