#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include "Perishable.h"

using namespace std;
namespace AMA {

	Perishable::Perishable() : Product ('P'){
		m_Error.clear();
	}
	std::fstream& Perishable::store(std::fstream& file, bool newLine) const {

		Product::store(file, false);
		if (newLine == true)
		{
			file << ',' << m_expire << endl;
		}
		else
		{
			file << ',' << m_expire;
		}
		
		return file;
	}
	std::fstream& Perishable::load(std::fstream& file)
	{
		Product::load(file);
		m_expire.read(file);
		file.ignore();
		return file;
		
	}
	std::ostream& Perishable::write(std::ostream& os, bool linear) const {
		Product::write(os, linear);
		if ( isClear() && !isEmpty()) 
		{

		}
		else
		{
			if (linear)
			{
				m_expire.write(os);
			}
			else
			{
				os << "n\Expiry date: ";
				m_expire.write(os);
			}
		}
		return os;
	}
	std::istream& Perishable::read(std::istream& is)
	{
		bool x = true;
		is.clear();
		Product::read(is);
		if (m_Error.isClear())
		{
			cout << " Expiry date (YYYY/MM/DD): ";
			m_expire.read(is);
			x = false;
		}

		if (m_expire.errCode() == CIN_FAILED)
		{
			m_Error.clear();
			m_Error.message("Invalid Date Entry");
			x = false;
		}
		
		if (m_expire.errCode() == YEAR_ERROR)
		{
			m_Error.clear();
			m_Error.message("Invalid Year in Date Entry");
			x = false;
		}

		if (m_expire.errCode() == MON_ERROR)
		{
			m_Error.clear();
			m_Error.message("Invalid Month in Date Entry");
			x = false;
		}

		if (m_expire.errCode() == DAY_ERROR)
		{
			m_Error.clear();
			m_Error.message("Invalid Day in Date Entry");
			x = false;
		}
			
		if (m_expire.errCode())
		{
			is.setstate(std::ios::failbit);
		}
		
		if (x)
		{
			m_Error.clear();
		}
	
		return is;
	}
	const Date& Perishable::expiry() const
	{
		return m_expire;
	}
}