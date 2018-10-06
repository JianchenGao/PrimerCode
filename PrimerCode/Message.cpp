#include"Message.h"
#include"Folder.h"

using namespace std;

void Message::save(Folder &f)
{
	folders.insert(&f);	//将给定Folder添加到我们的Folder列表中
	f.addMsg(this);		//将本Message添加到f的Message集合中
}

void Message::remove(Folder &f)
{
	folders.erase(&f);	//将给定Folder从我们的Folder列表中删除
	f.remMsg(this);		//将本Message从f的Message集合中删除
}

void Message::add_to_Folders(const Message &m)	//将类的Message添加到包含Message m的每一个Folder中
{
	for (auto f : m.folders)	//对每个包含m的Folder
		f->addMsg(this);		//向该Folder添加一个指向本Message的指针
}

//拷贝构造函数：将传入的Message m的信息拷贝到新建类message中
Message::Message(const Message &m) :	
	contents(m.contents), folders(m.folders)
{
	add_to_Folders(m);		//将本消息添加到指向m的Folder中
}

//移动构造函数
Message::Message(Message &&m) :contents(std::move(m.contents))	//move(m.contents)，返回一个右值引用，表明使用移动拷贝
{
	move_Folders(&m);	//移动folders并更新Folder指针
}

//从对应的Folder中删除本Message
void Message::remove_from_Folders()
{
	for (auto f : folders)	//对folders中每个指针
		f->remMsg(this);	//从该Folder中删除本Message
}

Message::~Message()
{
	remove_from_Folders();
}

Message& Message::operator=(const Message &rhs)
{
	//通过先删除指针再插入它们来处理自赋值情况
	remove_from_Folders();		//更新已有Folder
	contents = rhs.contents;	//从rhs拷贝消息内容
	folders = rhs.folders;		//从rhs拷贝Folder指针
	add_to_Folders(rhs);		//将本Message添加到那些Folder中
	return *this;
}

Message& Message::operator=(Message &&rhs)
{
	if (this != &rhs) {	//直接检查自赋值情况
		remove_from_Folders();
		contents = std::move(rhs.contents);	//移动赋值运算符
		move_Folders(&rhs);	//重置folders指向Message
	}
	return *this;
}

void swap(Message &lhs, Message &rhs)
{
	using std::swap;	//在本例中严格来说并不需要，但这是一个好习惯
	//将每个消息的指针从它（原来）所在Folder中删除
	for (auto f : lhs.folders)
		f->remMsg(&lhs);
	for (auto f : rhs.folders)
		f->remMsg(&rhs);
	//交换contents和Folder指针set
	swap(lhs.folders, rhs.folders);		//使用swap(set&,set&)
	swap(lhs.contents, rhs.contents);	//swap(string&,string&)
	//将每个Message的指针添加到它的（新）Folder中
	for (auto f : lhs.folders)
		f->addMsg(&lhs);
	for (auto f : rhs.folders)
		f->addMsg(&rhs);
}

void Message::move_Folders(Message *m)	//将Message m从其folders中删除，并用this将其代替
{
	folders = std::move(m->folders);	//使用set的移动赋值运算符
	for (auto f : folders) {	//对每个Folder
		f->remMsg(m);	//对Folder中删除旧Message
		f->addMsg(this);	//将本Message添加到Folder中
	}
	m->folders.clear(); //确保销毁m是无害的
}
