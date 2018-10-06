#pragma once
#ifndef STRBLOB_H
#define STRBLOB_H

#include "Version_test.h"
#include "StrBlobPtr.h"

#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include <initializer_list>


// forward declaration needed for friend declaration in StrBlob
class StrBlobPtr;

class StrBlob {
	friend class StrBlobPtr;
public:
    typedef std::vector<std::string>::size_type size_type;

	// constructors
    StrBlob() : data(std::make_shared<std::vector<std::string>>()) { }
    StrBlob(std::initializer_list<std::string> il):
		data(std::make_shared<std::vector<std::string>>(il)) { }
	StrBlob(std::string *, std::string*);  

	// size operations
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }

    // add and remove elements
    void push_back(const std::string &t) { data->push_back(t); }
    void pop_back();

    // element access
    std::string& front();
    std::string& back();

	// interface to StrBlobPtr
	StrBlobPtr begin();  // can't be defined until StrBlobPtr is

	StrBlobPtr end();

private:
    std::shared_ptr<std::vector<std::string>> data; 
    // throws msg if data[i] isn't valid
    void check(size_type i, const std::string &msg) const;
};


inline
StrBlob::StrBlob(std::string *b, std::string *e):
              data(std::make_shared<std::vector<std::string>>(b,e)) { }


#endif
