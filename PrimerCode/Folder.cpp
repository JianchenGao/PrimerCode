#include"Folder.h"
#include"Message.h"

//��ָ��Message m��ָ�����Msg�� 
void Folder::addMsg(Message *m)
{
	Msgs.insert(m);
}

//��ָ��Message m��ָ���Msg��ɾ�� 
void Folder::remMsg(Message *m)
{
	Msgs.erase(m);
}

void Folder::add_to_Messages(const Folder &f)	//�����Folder��ӵ�����Message��
{
	for (auto m : f.Msgs)	//m�������Folder &f�����洢��ÿ��Message�ĵ�ַ
		m->folders.insert(this);	//this��ʾ��Folder�ĵ�ַ�����ഴ�����¶���
}

void Folder::remove_from_Msgs()	//�����Folder��������Message��ɾ��
{
	for (auto m : Msgs)	//m������ô˺��������������Ϣ�ĵ�ַ
		m->remove(*this);	//��Folder�����Message��ɾ��
}

Folder& Folder::operator=(const Folder &rhs)	//��ֵ��������
{
	remove_from_Msgs();	//��ÿ��Message��ɾ����Folder
	Msgs = rhs.Msgs;	//���Ҳ�������󿽱�Message����
	add_to_Messages(rhs);	//����Folder��ӵ�ÿ����Message��
	return *this;
}

