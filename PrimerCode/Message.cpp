#include"Message.h"
#include"Folder.h"

using namespace std;

void Message::save(Folder &f)
{
	folders.insert(&f);	//������Folder��ӵ����ǵ�Folder�б���
	f.addMsg(this);		//����Message��ӵ�f��Message������
}

void Message::remove(Folder &f)
{
	folders.erase(&f);	//������Folder�����ǵ�Folder�б���ɾ��
	f.remMsg(this);		//����Message��f��Message������ɾ��
}

void Message::add_to_Folders(const Message &m)	//�����Message��ӵ�����Message m��ÿһ��Folder��
{
	for (auto f : m.folders)	//��ÿ������m��Folder
		f->addMsg(this);		//���Folder���һ��ָ��Message��ָ��
}

//�������캯�����������Message m����Ϣ�������½���message��
Message::Message(const Message &m) :	
	contents(m.contents), folders(m.folders)
{
	add_to_Folders(m);		//������Ϣ��ӵ�ָ��m��Folder��
}

//�ƶ����캯��
Message::Message(Message &&m) :contents(std::move(m.contents))	//move(m.contents)������һ����ֵ���ã�����ʹ���ƶ�����
{
	move_Folders(&m);	//�ƶ�folders������Folderָ��
}

//�Ӷ�Ӧ��Folder��ɾ����Message
void Message::remove_from_Folders()
{
	for (auto f : folders)	//��folders��ÿ��ָ��
		f->remMsg(this);	//�Ӹ�Folder��ɾ����Message
}

Message::~Message()
{
	remove_from_Folders();
}

Message& Message::operator=(const Message &rhs)
{
	//ͨ����ɾ��ָ���ٲ��������������Ը�ֵ���
	remove_from_Folders();		//��������Folder
	contents = rhs.contents;	//��rhs������Ϣ����
	folders = rhs.folders;		//��rhs����Folderָ��
	add_to_Folders(rhs);		//����Message��ӵ���ЩFolder��
	return *this;
}

Message& Message::operator=(Message &&rhs)
{
	if (this != &rhs) {	//ֱ�Ӽ���Ը�ֵ���
		remove_from_Folders();
		contents = std::move(rhs.contents);	//�ƶ���ֵ�����
		move_Folders(&rhs);	//����foldersָ��Message
	}
	return *this;
}

void swap(Message &lhs, Message &rhs)
{
	using std::swap;	//�ڱ������ϸ���˵������Ҫ��������һ����ϰ��
	//��ÿ����Ϣ��ָ�������ԭ��������Folder��ɾ��
	for (auto f : lhs.folders)
		f->remMsg(&lhs);
	for (auto f : rhs.folders)
		f->remMsg(&rhs);
	//����contents��Folderָ��set
	swap(lhs.folders, rhs.folders);		//ʹ��swap(set&,set&)
	swap(lhs.contents, rhs.contents);	//swap(string&,string&)
	//��ÿ��Message��ָ����ӵ����ģ��£�Folder��
	for (auto f : lhs.folders)
		f->addMsg(&lhs);
	for (auto f : rhs.folders)
		f->addMsg(&rhs);
}

void Message::move_Folders(Message *m)	//��Message m����folders��ɾ��������this�������
{
	folders = std::move(m->folders);	//ʹ��set���ƶ���ֵ�����
	for (auto f : folders) {	//��ÿ��Folder
		f->remMsg(m);	//��Folder��ɾ����Message
		f->addMsg(this);	//����Message��ӵ�Folder��
	}
	m->folders.clear(); //ȷ������m���޺���
}
