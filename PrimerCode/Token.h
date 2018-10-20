#ifndef TOKEN_H
#define TOKEN_H

#include<string>

class Token {
public:
	//因为union含有一个string成员，所以token必须定义拷贝控制成员

	Token():tok(INT),ival{0}{ }
	Token(const Token &t) :tok(t.tok) { copyUnion(t); }
	Token &operator=(const Token&);
	//如果union含有一个string成员，则我们必须销毁它
	~Token() {
		if (tok == STR) 
			sval.~basic_string();  //c++中string不能直接调用其析构函数
	}

	//下面的赋值运算符赋值设置union的不同成员
	Token &operator=(const std::string&);
	Token &operator=(char);
	Token &operator=(int);
	Token &operator=(double);

private:
	enum { INT, CHAR, DBL, STR } tok;	//判别式
	union {
		char cval;
		int ival;
		double dval;
		std::string sval;
	};

	void copyUnion(const Token&);
};

#endif // !TOKEN_H
