#ifndef AMA_PERISHABLE_H__
#define AMA_PERISHABLE_H__
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "Date.h"
#include "Product.h"


namespace AMA {
	
	class Perishable : public Product 
	{
		Date m_expire;

	public:
		Perishable();
		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);
		const Date& expiry() const;

	};
	
	iProduct* CreatePerishable();
}

#endif