#pragma once
#ifndef QUOTE_H
#define QUOTE_H
#include<string>
#include<set>
#include<ostream>


class Quote {
public:
	//���麯�����ص�ǰ�����һ�ݶ�̬����Ŀ���
	//��Щ��Աʹ�õ������޶����μ�13.6.3
	virtual Quote* clone() const & { return new Quote(*this); }	//ֻ�ܷ�����ֵ
	virtual Quote* clone() && { return new Quote(std::move(*this)); } //������ֵ

	Quote() = default;
	Quote(const std::string &book,double sales_price):
		bookNo(book),price(sales_price){ }
	std::string isbn() const { return bookNo; }
	virtual double net_price(std::size_t n) const { return 0; };
	//�������ɾ������һ��ָ�����������Ļ���ָ�룬����Ҫ����������
	virtual ~Quote() = default;	//��̬����������
private:
	std::string bookNo;
protected:
	double price = 0.0;
};

//���ڱ����ۿ�ֵ�͹��������࣬������ʹ����Щ���ݿ���ʵ�ֲ�ͬ�ļ۸����
class Disc_quote :public Quote {
public:
	Disc_quote() = default;
	Disc_quote(const std::string& book, double price,
		std::size_t qty, double disc) :
		Quote(book, price){ }
	double net_price(std::size_t) const = 0;	//���麯��
};

//��ͬһ�鼮������������ĳ��ֵ�����ۿ�
//�ۿ۵�ֵ��һ��С��1������С��ֵ���Դ��������������ۼ۸�
class Bulk_quote :public Disc_quote {	//Bulk_quote�̳���Quote
public:
	Bulk_quote* clone() const & { return new Bulk_quote(*this); }	//ֻ�ܷ�����ֵ
	Bulk_quote* clone() && { return new Bulk_quote(std::move(*this)); } //������ֵ
	using Disc_quote::Disc_quote;	//�̳�Disc_quote�Ĺ��캯��
	Bulk_quote() = default;
	Bulk_quote(const std::string&, double, std::size_t, double);
	//���ǻ���ĺ����汾��ʵ�ֻ��ڴ���������ۿ�����
	double net_price(std::size_t) const override;	//��ʾע��ʹ�ô˺�����д������麯��
private:
	std::size_t min_qty = 0;	//�����ۿ����ߵ���͹�����
	double discount = 0.0;	//��С����ʾ���ۿ۶�
};

extern double print_total(std::ostream &os, const Quote &item, size_t n);

#endif