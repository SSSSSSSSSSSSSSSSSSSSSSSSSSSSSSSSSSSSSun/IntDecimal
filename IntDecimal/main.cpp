#include <iostream>
#include "FixedPoint.h"

void inputIntDecimal(short input, FixedPoint& data) {
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
	case 4:
		int d1;
		unsigned d2;
		std::cin >> d1 >> d2;
		data = FixedPoint(d1, d2);
		break;
	}

	return;
}

int main() {

	std::cout << "======================================" << '\n';
	std::cout << "1. int" << '\n';
	std::cout << "2. float" << '\n';
	std::cout << "3. double" << '\n';
	std::cout << "4. int, unsigned int" << '\n';
	std::cout << "5. Quit" << '\n';
	std::cout << "======================================" << '\n';
	
	short input;
	FixedPoint a;
	while (1) {
		std::cin >> input;

		if (1 <= input && input <= 4) {
			inputIntDecimal(input, a);
			break;
		}
		if (input == 5)
			exit(0);
	}

	FixedPoint d = -1.3;
	FixedPoint b = 5.1;
	FixedPoint c = b + d;

	//float q = -123.123;
	//float w;
	//float e = modf(q,&w);

	//std::cout << w << ' ' << e << '\n';

	std::cout << d.printSign() << d.getIntegerPart() << '.' << d.getDecimalPart() << '\n';
	std::cout << b.printSign() << b.getIntegerPart() << '.' << b.getDecimalPart() << '\n';
	std::cout << c.printSign() << c.getIntegerPart() << '.' << c.getDecimalPart() << '\n';

	std::cout << a.printSign() << a.getIntegerPart() << '.' << a.getDecimalPart() << '\n';
	std::cout << "a.toInt() : " << a.toInt() << '\n';
	std::cout << "a.toDouble() : " << a.toDouble() << '\n';
	std::cout << "a.toFloat() : " << a.toFloat() << '\n';


}
