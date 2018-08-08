/* Student ID : 105903173
* Seneca email : agarcia - caicedo@myseneca.ca
* Date of Completion : 13 / 07 / 2018
* *********************************************************/


#include "Date.h"


namespace AMA {

	// number of days in month mon_ and year year_
	//
	int Date::mdays(int mon, int year)const {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}

	void Date::errCode(int errorCode) {
		if ( errorCode == CIN_FAILED || errorCode == YEAR_ERROR
			|| errorCode == MON_ERROR || errorCode == DAY_ERROR)
		m_error = errorCode;
	}

	Date::Date() {
		set();
	}

	Date::Date(int year, int month, int day) {
		set();
		if (year >= min_year && year <= max_year) 
		{
			if (month >= 1 && month <= 12)
			{
				if (day >= 1 && day <= mdays(month, year)) {
					m_year = year;
					m_month = month;
					m_day = day;
					m_comp = comp();
					errCode(NO_ERROR);
				}
				else
				{
					errCode(DAY_ERROR);
				}
			}
			else 
			{
				errCode(MON_ERROR);
			}
		} 
		else
		{
			errCode(YEAR_ERROR);
		}

	}

	void Date::set() {
		m_year = 0;
		m_month = 0;
		m_day = 0;
		m_error = 0; 
	}

	bool Date::isEmpty() const{
		bool x;
		if (m_year == 0)
		{
			x = true;
		} 
		else
		{
			x = false; 
		}

		return x; 
	}
	int Date::comp() const{
		int comp = m_year * 372 + m_month * 13 + m_day;
		return comp ;
	}
	bool Date::operator==(const Date& rhs) const {
		bool x = isEmpty();
		if (x == false)
		{
			if (this->comp() == rhs.comp())
			{
				x = true;
			}
		}
		else 
		{
			x = false;
		}

		return x;
	}

	bool Date::operator!=(const Date& rhs) const {
		bool x = isEmpty();
		if (x == false)
		{
			if (this->comp() != rhs.comp())
			{
				x = true;
			}
			else
			{
				x = false;
			}
		}
		else
		{
			x = false;
		}

		return x;
	}

	bool Date::operator<(const Date& rhs) const {
		bool x = isEmpty();

		if (x == false)
		{
			if (this->comp() < rhs.comp())
			{
				x = true;
			}
			else
			{
				x = false;
			}
		}

		return x;
	}

	bool Date::operator>(const Date& rhs) const {
		bool x = isEmpty();
		if (x == false)
		{
			if(this->comp() > rhs.comp())
			{
				x = true;
			}
			else
			{
				x = false;
			}
		}
		else
		{
			x = false;
		}

		return x;
	}

	bool Date::operator<=(const Date& rhs) const {
		bool x = isEmpty();
		if (x == false)
		{
			if (this->comp() <= rhs.comp())
			{
				x = true;
			}
			else
			{
				x = false;
			}
		}
		else
		{
			x = false;
		}

		return x;
	}

	bool Date::operator>=(const Date& rhs) const {
		bool x = isEmpty();
		if (x == false)
		{
			if (this->comp() >= rhs.comp())
			{
				x = true;
			}
			else
			{
				x = false;
			}
		}
		else
		{
			x = false;
		}

		return x;
	}

	int Date::errCode() const {
		return m_error; 
	}

	bool Date::bad() const {
		bool x;
		if (m_error == CIN_FAILED || m_error == YEAR_ERROR
			|| m_error == MON_ERROR || m_error == DAY_ERROR)
		{
			x = true;
		}
		else 
		{
			x = false;
		}

		return x; 
	}

	std::istream& Date::read(std::istream& istr) {
		int day;
		int month;
		int year;
		
		istr >> year;
		istr.ignore(4, '/'); 
	
		istr >> month;
		istr.ignore(2, '/');
		
		istr >> day;
		Date dat(year, month, day);
		
		if (istr.fail())
		{
			errCode(CIN_FAILED);
			istr.clear();
		}
		else if ( year > max_year || year < min_year)
		{
			errCode(YEAR_ERROR);
			istr.clear();
		}
		else if (month < 1 || month > 12)
		{
			errCode(MON_ERROR);
			istr.clear();
		}
		else if (day < 1 || day > mdays(month, year))
		{
			errCode(DAY_ERROR);
			istr.clear();
		} 
		else
		{
			*this = dat;
		}
		istr.clear();
		return istr; 
	}
	std::ostream& Date::write(std::ostream& ostr) const {

		ostr << m_year << '/';
		ostr.fill('0');
		ostr.width(2);
		ostr << m_month << '/';
		ostr.fill('0');
		ostr.width(2); 
		ostr << m_day; 
		return ostr;
	}
	std::istream& operator>>(std::istream& is, Date& date) {
		date.read(is);
		return is;
	}
	std::ostream& operator<<(std::ostream& os, const Date& date) {
		date.write(os);
		return os;
	}

}