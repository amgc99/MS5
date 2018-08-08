/*
Student ID : 105903173
* Seneca email : agarcia - caicedo@myseneca.ca
* Date of Completion : 03 / 08 / 2018
* *********************************************************/

#define _CRT_SECURE_NO_WARNINGS 
#include <cstring>
#include <iomanip>
#include <string>
#include <iostream>
#include "Product.h"



using namespace std;
namespace AMA {

	Product::Product(char type)
	{
		m_type = type;
		m_pname = nullptr;
	}

	Product::Product(const char* sku, const char* pname, const char* unit, int qty_have, bool tax, double price, int qty_need)
	{
		strcpy(m_sku, sku);
		m_pname = nullptr;
		name(pname);
		strcpy(m_descrp, unit);
		m_qtyCurrent = qty_have;
		m_taxable = tax;
		m_price = price;
		m_qtyNeed = qty_need;
		

	}

	Product::Product(const Product& scr) {
		if (scr.m_Error.message() != nullptr)
		{
			m_Error.message(scr.m_Error.message());
		}

		*this = scr;
	}

	Product& Product::operator=(const Product& src)
	{
		if (this != &src) {
			
			m_pname = nullptr;
			name(src.name());
			strcpy(m_sku, src.sku());
			strcpy(m_descrp, src.unit());
			
			m_qtyCurrent = src.quantity();
			m_qtyNeed = src.qtyNeeded();
			m_price = src.price();
			m_taxable = src.taxed();
			if (src.m_Error.message() != nullptr)
			{
				m_Error.message(src.m_Error.message());
			}
		
		}

		return *this;
	}

	Product::~Product()
	{
		delete[] m_pname;
		m_pname = nullptr;
	}

	void Product::name(const char* name)
	{
		
		delete[] m_pname;
		
		if (name != nullptr) {
			m_pname = new char[strlen(name) + 1];
			strcpy(m_pname, name);
		}
	}
	
	const char* Product::name() const
	{
		return m_pname; 
	}
	
	const char* Product::sku() const
	{
		return m_sku;
	}
	
	const char* Product::unit() const
	{
		return m_descrp;
	}
	
	bool Product::taxed() const
	{
		return m_taxable;
	}
	
	double Product::price() const
	{
		return m_price;
	}
	
	double Product::cost() const
	{
		double cost = (taxed()) ? (price() * tax_rate) + price() : price ();
		return cost;
	}
	
	void Product::message(const char* mssg)
	{
		m_Error.message(mssg);
	}
	
	bool Product::isClear() const
	{
		return m_Error.isClear();
	}

	
	std::fstream& Product::store(std::fstream& file, bool line) const
	{
		if (file.is_open()) 
		{
			file << m_type << "," << sku() << ","
				<< unit() << ", " << *m_pname << ","
				<< m_Error.message() << "," << qtyNeeded() << ","
				<< quantity() << "," << price() << ",";
			if (taxed())
			{
				file << "True";
			}
			else
			{
				file << "False";
			}
		}

		if (line == true) 
		{
			file << endl;
		}

		return file;
	}
	
	std::fstream& Product::load(std::fstream& file)
	{
		string str[] = { "Name", "Type", "SKU", "Unit", "InvHave", "InvNeed", "Price", "Taxable", "errMssg" };
		
		if (file.is_open()) 
		{
			for (int i = 0; i < 9; i++) 
			{
				std::getline(file, str[i], ',');
			}
			
			name(str[0].c_str());
			m_type = str[1][0];
			strcpy(m_sku, str[2].c_str());
			strcpy(m_descrp, str[3].c_str());
			m_qtyCurrent = stoi(str[4]);
			m_qtyNeed = stoi(str[5]);
			m_price = stof(str[6]);
			m_taxable = (str[7] == "True" ? true : false);
			m_Error.message(str[8].c_str());

		}

		return file;
	}
	
	std::ostream& Product::write(std::ostream& os , bool loob) const
	{
		if (!(m_Error.isClear()))
		{
			os << m_Error.message();
			return os;
		}
		else if (loob)
		{
			os.width(max_sku_length); 
			os << std::left << m_sku << '|';
			os.width(20);
			os << std::left << m_pname << '|';
			os.width(7);
			os << std::right << std::fixed << std::setprecision(2) << cost() << '|';
			os.width(4);
			os << std::right << quantity() << '|';
			os.width(10);
			os << std::left << unit() << '|';
			os.width(4);
			os << std::right << qtyNeeded() << '|';
		}
		else
		{
			os << "SKU: " << m_sku << '|' << endl;
			os << "Name: " << *m_pname << '|' << endl;
			os << "Price: " << price();
			os << '|' << endl;
			if (taxed())
			{
				os << " Price after tax: " << cost() << endl;
			}
			else
			{
				os << " Price after tax: N/A" << endl;
			}
			os << "Quantity on hand: " << quantity() << '|' << endl;
			os << "Quantity on hand: " << qtyNeeded() << '|' << endl;
		}

		return os;
	}
	
	std::istream& Product::read(std::istream& is)
	{
		
		char txbl;
		string Name;
		Product tmp;

		cout << " Sku: ";
		is >> tmp.m_sku;
		cout << " Name (no spaces): ";
		is >> Name;
		tmp.name(Name.c_str());
		cout << " Unit: ";
		is >> tmp.m_descrp;
		cout << " Taxed? (y/n): ";
		is >> txbl;
		if (!is.fail())
		{
			m_Error.clear();

			if (txbl == 'Y' || txbl == 'y')
			{
				tmp.m_taxable = true;
			}
			else if (txbl == 'N' || txbl == 'n')
			{
				tmp.m_taxable = false;
			}
			else 
			{
				is.setstate(std::ios::failbit);
				
				m_Error.message("Only (Y)es or (N)o are acceptable");
				return is;
			}
		}
		else
		{
			is.setstate(std::ios::failbit);
		
			m_Error.message("Only (Y)es or (N)o are acceptable");
			return is;
		}
		cout << " Price: ";
		is >> tmp.m_price;
		if (is.fail())
		{
			m_Error.clear();
			is.setstate(std::ios::failbit);
			
			m_Error.message("Invalid Price Entry");
			return is;
		}
		cout << " Quantity on hand: ";
		is >> tmp.m_qtyCurrent;
		if (is.fail())
		{
			m_Error.clear();
			is.setstate(std::ios::failbit);
		
			m_Error.message("Invalid Quantity Entry");
			return is;
		}
		cout << " Quantity needed: ";
		is >> tmp.m_qtyNeed;
		if (is.fail())
		{
			m_Error.clear();
			is.setstate(std::ios::failbit);
			
			m_Error.message("Invalid Quantity Needed Entry");
			return is; 
		}
		
		return is;
	}


	bool Product::operator==(const char* _sku) const
	{
		return (strcmp(sku(), _sku) == 0);
	}
	
	double Product::total_cost() const
	{
		return taxed() ? cost() * quantity() : price() * quantity();
	}
	
	void Product::quantity(int qty)
	{
		m_qtyCurrent = qty;
	}
	
	bool Product::isEmpty() const
	{
		return (m_price < 0);
	}
	
	int Product::qtyNeeded() const
	{
		return m_qtyNeed;
	}
	
	int Product::quantity() const
	{
		return m_qtyCurrent;
	}

	
	bool Product::operator>(const iProduct& src) const
	{
		return (strcmp(sku(), src.name()) > 0);
	}
	
	bool Product::operator>(const Product& product) const
	{
		return (strcmp(name(), product.name()) > 0);
	}
	
	int Product::operator+=(int add)
	{
		if (add > 0)
		{
			m_qtyCurrent += add;
		}
		return quantity();
	}
	std::ostream& operator<<(std::ostream& os, const iProduct& product) {
		product.write(os, true);
		return os;
	}

	std::istream& operator>>(std::istream& is,  iProduct& product)
	{
		product.read(is);
		return is;
	}
	
	double operator+=(double& price, const iProduct& product)
	{
		price += product.total_cost();
		return price;
	}

}