/*
Student ID : 105903173
* Seneca email : agarcia - caicedo@myseneca.ca
* Date of Completion : 04 / 08 / 2018
* *********************************************************/

#include "MyProduct.h"

namespace AMA {

	iProduct* CreateProduct() {
		return new MyProduct("Product");
	}
	iProduct* CreatePerishable() {
		return new MyProduct("Perishable");
	}
}