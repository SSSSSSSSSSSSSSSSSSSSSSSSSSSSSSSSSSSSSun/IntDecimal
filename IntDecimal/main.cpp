#include <iostream>
#include "IntDecimal.h"

void inputIntDecimal(short input, IntDecimal& data) {
	std::cout << "°ª ÀÔ·Â : ";
	switch (input) {
	case 1:
		int a;
		std::cin >> a;
		data = a;
		break;
	case 2:
		float b;
		std::cin >> b;
		data = b;
		break;
	case 3:
		double c;
		std::cin >> c;
		data = c;
		break;
	}

	return;
}

int main() {

	std::cout << "======================================" << '\n';
	std::cout << "1. int" << '\n';
	std::cout << "2. float" << '\n';
	std::cout << "3. double" << '\n';
	std::cout << "4. Quit" << '\n';
	std::cout << "======================================" << '\n';
	
	short input;
	IntDecimal a;
	while (1) {
		std::cin >> input;

		if (1 <= input && input <= 3) {
			inputIntDecimal(input, a);
			break;
		}
		if (input == 4)
			exit(0);
	}


	std::cout << a.printSign() << a.getIntegerPart() << '.' << a.getDecimalPart() << '\n';

	std::cout << "a.toInt() : " << a.toInt() << '\n';
	std::cout << "a.toDouble() : " << a.toDouble() << '\n';
	std::cout << "a.toFloat() : " << a.toFloat() << '\n';


}
