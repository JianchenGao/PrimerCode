#pragma once
#ifndef SALES_DATA_H
#define SALES_DATA_H

#include <string>
#include<ostream>

namespace cplusplus_primer{
	class Sales_data {

		friend Sales_data add(const Sales_data&, const Sales_data&);
		friend std::ostream &print(std::ostream&, const Sales_data&);
		friend std::istream &read(std::istream&, Sales_data&);
		friend std::ostream &operator<<(std::ostream &os, const Sales_data &item);
		friend std::istream &operator>>(std::istream &is, Sales_data &item);
		friend bool operator==(const Sales_data &lhs, const Sales_data &rhs);
		friend bool operator!=(const Sales_data &lhs, const Sales_data &rhs);
		friend Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs);//不能写在类内，类内会将第一参数默认成this

		
	public:
		Sales_data() = default;
		Sales_data(const std::string &s) :bookNo(s) { }
		Sales_data(const std::string &s,unsigned n,double p) :bookNo(s),units_sold(n),revenue(p*n) { }
		Sales_data(std::istream &);
		Sales_data(const Sales_data&);
		Sales_data& operator+=(const Sales_data &rhs);


		std::string isbn() const { return bookNo; }
		Sales_data& combine(const Sales_data&);

	private:
		double avg_price() const;

		std::string bookNo;
		unsigned units_sold = 0;
		double revenue = 0.0;
	};


	Sales_data add(const Sales_data&, const Sales_data&);
	std::ostream &print(std::ostream&, const Sales_data&);
	std::istream &read(std::istream&, Sales_data&);

	std::ostream &operator<<(std::ostream &os, const Sales_data &item);
	std::istream &operator>>(std::istream &is, Sales_data &item);
	bool operator==(const Sales_data &lhs, const Sales_data &rhs);
	bool operator!=(const Sales_data &lhs, const Sales_data &rhs);
	Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs);//不能写在类内，类内会将第一参数默认成this
}

#endif // !SALES_DATA_H
