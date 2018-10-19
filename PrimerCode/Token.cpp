#include"Token.h"

using namespace std;

Token &Token::operator=(int i)
{
	if (tok == STR) sval.~string();
	ival = i;
	tok = INT;
	return *this;
}

Token &Token::operator=(char c)
{
	if (tok == STR) sval.~string();
	cval = c;
	tok = INT;
	return *this;
}

Token &Token::operator=(double d)
{
	if (tok == STR) sval.~string();
	dval = d;
	tok = INT;
	return *this;
}

Token &Token::operator=(const std::string &s)
{
	if (tok == STR)
		sval = s;
	else
		new(&sval) string(s);
	tok = INT;
	return *this;
}

void Token::copyUnion(const Token &t)
{
	switch (t.tok) {
	case Token::INT: ival = t.ival; break;
	case Token::CHAR: cval = t.cval; break;
	case Token::DBL: dval = t.dval; break;
		// to copy a string, construct it using placement new; see (XREF(placenew)) 
	case Token::STR: new(&sval) std::string(t.sval); break;
	}
}

Token &Token::operator=(const Token &t)
{
	// if this object holds a string and t doesn't, we have to free the old string
	if (tok == STR && t.tok != STR) sval.~string();
	if (tok == STR && t.tok == STR)
		sval = t.sval;  // no need to construct a new string
	else
		copyUnion(t);   // will construct a string if t.tok is STR
	tok = t.tok;
	return *this;
}