#include"Folder.h"
#include"Message.h"

//将指向Message m的指针存入Msg中 
void Folder::addMsg(Message *m)
{
	Msgs.insert(m);
}

//将指向Message m的指针从Msg中删除 
void Folder::remMsg(Message *m)
{
	Msgs.erase(m);
}

void Folder::add_to_Messages(const Folder &f)	//将这个Folder添加到所有Message中
{
	for (auto m : f.Msgs)	//m代表传入的Folder &f中所存储的每个Message的地址
		m->folders.insert(this);	//this表示本Folder的地址（有类创建的新对象）
}

void Folder::remove_from_Msgs()	//将这个Folder从它所有Message中删除
{
	for (auto m : Msgs)	//m代表调用此函数对象的所有信息的地址
		m->remove(*this);	//将Folder对象从Message中删除
}

Folder& Folder::operator=(const Folder &rhs)	//赋值拷贝函数
{
	remove_from_Msgs();	//从每个Message中删除此Folder
	Msgs = rhs.Msgs;	//从右侧运算对象拷贝Message集合
	add_to_Messages(rhs);	//将此Folder添加到每个新Message中
	return *this;
}

