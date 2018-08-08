/*
Student ID : 105903173
* Seneca email : agarcia - caicedo@myseneca.ca
* Date of Completion : 03 / 08 / 2018
* *********************************************************/

#ifndef AMA_ERRORSTATE_H__
#define AMA_ERRORSTATE_H__
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

namespace AMA {

	class ErrorState {
		char* m_message;

	public: 
		explicit ErrorState(const char* errorMessage = nullptr);
		ErrorState(const ErrorState& em) = delete;
		ErrorState& operator=(const ErrorState& em) = delete;
		virtual ~ErrorState() {};
		void clear();
		bool isClear() const;
		void message(const char* str);
		const char* message() const;
		
	};
	std::ostream& operator<<(std::ostream& os, const ErrorState&);
	}
#endif