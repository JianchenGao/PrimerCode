#ifndef TOKEN_H
#define TOKEN_H

#include<string>

class Token {
public:
	//��Ϊunion����һ��string��Ա������token���붨�忽�����Ƴ�Ա

	Token():tok(INT),ival{0}{ }
	Token(const Token &t) :tok(t.tok) { copyUnion(t); }
	Token &operator=(const Token&);
	//���union����һ��string��Ա�������Ǳ���������
	~Token() {
		if (tok == STR) 
			sval.~basic_string();  //c++��string����ֱ�ӵ�������������
	}

	//����ĸ�ֵ�������ֵ����union�Ĳ�ͬ��Ա
	Token &operator=(const std::string&);
	Token &operator=(char);
	Token &operator=(int);
	Token &operator=(double);

private:
	enum { INT, CHAR, DBL, STR } tok;	//�б�ʽ
	union {
		char cval;
		int ival;
		double dval;
		std::string sval;
	};

	void copyUnion(const Token&);
};

#endif // !TOKEN_H
