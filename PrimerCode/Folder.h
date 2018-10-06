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
	void add_to_Messages(const Folder &f);	//�����Folder��ӵ�����Message��
	void remove_from_Msgs();	//�����Folder��������Message��ɾ��
	Folder() = default;
	Folder(const Folder &f) :Msgs(f.Msgs)	//�������캯��
	{
		add_to_Messages(f);	//��Folder��ӵ�������Message��folders��
	}
	~Folder()	//��������
	{
		remove_from_Msgs();
	}
	Folder& operator=(const Folder &rhs);	//��ֵ��������


private:
	std::set<Message *> Msgs;	//��Folder���洢����Ϣ
};



#endif // !FOLDER