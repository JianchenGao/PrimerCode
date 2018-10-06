#pragma once
#ifndef MESSAGE_H
#define MESSAGE_H

#include<string>
#include<set>


class Message {
	friend class Folder;
	friend void swap(Message &lhs, Message &rhs);
public:
	//folders����ʽ��ʼ��Ϊ�ռ���
	explicit Message(const std::string &str = ""):
		contents(str) { }
	//�������Ƴ�Ա����������ָ��Message��ָ��
	Message(const Message&);	//�������캯��
	Message(Message &&);
	Message& operator=(const Message&);	//������ֵ�����
	Message& operator=(Message &&);	//�ƶ���ֵ�����
	~Message();	//��������
	//�Ӹ���Folder���������/ɾ����Message
	void save(Folder&);
	void remove(Folder&);
	void addFldr(Folder *f) { folders.insert(f); }//��Ӹ���Folder
	void add_to_Folders(const Message &m);
	void remove_from_Folders();
	void move_Folders(Message *m);	//�ӱ�Message�ƶ�Folderָ��
private:
	std::string contents;	//ʵ����Ϣ�ı�
	std::set<Folder*> folders;	//
};

#endif // !MESSAGE
