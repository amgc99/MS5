/*
Student ID : 105903173
* Seneca email : agarcia - caicedo@myseneca.ca
* Date of Completion : 03 / 08 / 2018
* *********************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include "ErrorState.h"
#include <cstring>
#include <string>

using namespace std;

namespace AMA {

	ErrorState::ErrorState(const char* errorMessage) {
		if (errorMessage == nullptr) 
		{
			m_message = nullptr;
		} 
		else
		{
			message(errorMessage);
		}

	}
	
	void ErrorState::clear() {
		delete[] m_message;
		m_message = nullptr;
	}

	bool ErrorState::isClear() const {
		return (m_message == nullptr);
	}
	void ErrorState::message(const char* str) {
		
		if (isClear())
		{
			m_message = new char[strlen(str) + 1];
			strcpy(m_message, str);
		}

	
	}
	const char* ErrorState::message() const {
		return m_message; 
	}

	std::ostream& operator<<(std::ostream& os, const ErrorState& state) {
		if (!state.isClear())
		{
			os << state.message();
		}
		
		return os; 
	}

}