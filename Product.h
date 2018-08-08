/*
Student ID : 105903173
* Seneca email : agarcia - caicedo@myseneca.ca
* Date of Completion : 03 / 08 / 2018
* *********************************************************/

#ifndef AMA_PRODUCT_H__
#define AMA_PRODUCT_H__
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include "ErrorState.h"
#include "iProduct.h"

namespace AMA {
#define max_sku_length 7
#define max_unit_length 10
#define max_name_length 75
#define tax_rate 0.13

	class Product : public iProduct {
		char m_type;
		char m_sku[max_sku_length + 1];
		char m_descrp[max_name_length + 1];
		char * m_pname = nullptr;
		int m_qtyCurrent;
		int m_qtyNeed;
		double m_price;
		bool m_taxable;

	protected:
		ErrorState m_Error;
		void name(const char*);
		const char* name() const;
		const char* sku() const;
		const char* unit() const;
		bool taxed() const;
		double price() const;
		double cost() const;
		void message(const char*);
		bool isClear() const;

	public:
		Product(char type = 'N');
		Product(const char* sku, const char* pname, const char* unit, int qty_have = 0, bool tax = true, double price = 0, int qty_need = 0);
		Product(const Product&);
		Product& operator=(const Product&);
		~Product();

		std::fstream& store(std::fstream&, bool line = true) const;
		std::fstream& load(std::fstream&);
		std::ostream& write(std::ostream&, bool) const;
		std::istream& read(std::istream&);

		bool operator==(const char*) const;
		double total_cost() const;
		void quantity(int);
		bool isEmpty() const;
		int qtyNeeded() const;
		int quantity() const;

		bool operator>(const iProduct&) const;
		bool operator>(const Product&) const;
		int operator+=(int);
	};

	std::ostream& operator<<(std::ostream&, const iProduct&);
	std::istream& operator>>(std::istream&, iProduct&);
	double operator+=(double&, const iProduct&);
}

#endif