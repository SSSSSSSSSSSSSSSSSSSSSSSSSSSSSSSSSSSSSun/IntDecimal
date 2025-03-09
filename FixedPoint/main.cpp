#include <iostream>
#include "FixedPoint.h"
#include "mainLoop.h"

// FixedPoint가 잘 작동하는지 확인하기 위해 만든 코드

void inputfirst(short*,const short&, int&, unsigned int&,FixedPoint&);
void inputInt(int&);
void inputUnsignedInt(unsigned int&);
void inputFixedPoint(short, FixedPoint&);


int main() {
	short input[2] = { -1, -1 };
	int intA, intB;
	unsigned int unsignedA, unsignedB;
	FixedPoint fixedpointA, fixedpointB;
	inputfirst(input, 0, intA, unsignedA, fixedpointA);
	inputfirst(input, 1, intB, unsignedB, fixedpointB);

	if (input[0] == 1) {
		if (input[1] == 1)
			mainLoop(input, intA, intB);
		if (input[1] == 2)
			mainLoop(input, intA, unsignedB);
		if (input[1] >= 3)
			mainLoop(input, intA, fixedpointB);
	}
	if (input[0] == 2) {
		if (input[1] == 1)
			mainLoop(input, unsignedA, intB);
		if (input[1] == 2)
			mainLoop(input, unsignedA, unsignedB);
		if (input[1] >= 3)
			mainLoop(input, unsignedA, fixedpointB);
	}
	if (input[0] >= 3) {
		if (input[1] == 1)
			mainLoop(input, fixedpointA, intB);
		if (input[1] == 2)
			mainLoop(input, fixedpointA, unsignedB);
		if (input[1] >= 3)
			mainLoop(input, fixedpointA, fixedpointB);
	}

}

void inputfirst(short* input,const short& index, int& intA, unsigned int& unsignedA, FixedPoint& fixedpointA) {
	char indexUpper = 'A' + index;
	char indexLower = 'a' + index;

	std::cout << "=" << indexUpper << "====================================" << '\n';
	std::cout << "1. int" << '\n';
	std::cout << "2. unsigned int" << '\n';
	std::cout << "3. int => FixedPoint" << '\n';
	std::cout << "4. unsigned int => FixedPoint" << '\n';
	std::cout << "5. float => FixedPoint" << '\n';
	std::cout << "6. double => FixedPoint" << '\n';
	std::cout << "7. int, unsigned int => FixedPoint" << '\n';
	std::cout << "8. unsigned int, unsigned int => FixedPoint" << '\n';
	std::cout << "0. Quit" << '\n';
	std::cout << "text. Quit" << '\n';
	std::cout << "======================================" << '\n';

	while (1) {
		std::cout << "명령어 입력 : ";
		std::cin >> input[index];
		bool escape = true;
		switch (input[index]) {
		case 1:
			inputInt(intA);
			break;
		case 2:
			inputUnsignedInt(unsignedA);
			break;
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
			inputFixedPoint(input[index], fixedpointA);
			break;
		case 0:
			exit(0);
		default:
			escape = false;

		}

		if (escape)
			break;
	}

	switch (input[index]) {
	case 1:
		std::cout << indexUpper << " (int) : " << intA << '\n';
		break;
	case 2:
		std::cout << indexUpper << " (unsigned int) : " << unsignedA << '\n';
		break;
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
		std::cout << indexUpper << " (FixedPoint) : " << fixedpointA << '\n';
		std::cout << indexLower << ".toInt() : " << fixedpointA.toInt() << '\n';
		std::cout << indexLower << ".tounsignedInt() : " << fixedpointA.toUnsignedInt() << '\n';
		std::cout << indexLower << ".toDouble() : " << fixedpointA.toDouble() << '\n';
		std::cout << indexLower << ".toFloat() : " << fixedpointA.toFloat() << '\n';
		break;
	}
	std::cout << '\n';
	return;
}

void inputInt(int& data) {
	std::cout << "값 입력 : ";
	std::cin >> data;
	return;
}

void inputUnsignedInt(unsigned int& data) {
	std::cout << "값 입력 : ";
	std::cin >> data;
	return;
}

void inputFixedPoint(short input, FixedPoint& data) {
	std::cout << "값 입력 : ";
	switch (input) {
	case 3:
		int a;
		std::cin >> a;
		data = a;
		break;
	case 4:
		unsigned int b;
		std::cin >> b;
		data = b;
		break;
	case 5:
		float c;
		std::cin >> c;
		data = c;
		break;
	case 6:
		double d;
		std::cin >> d;
		data = d;
		break;
	case 7:
		int e1;
		unsigned e2;
		std::cin >> e1 >> e2;
		data = FixedPoint(e1, e2);
		break;
	case 8:
		unsigned f1;
		unsigned f2;
		bool f3;
		std::cin >> f1 >> f2 >> f3;
		data = FixedPoint(f1, f2, f3);
		break;
	}

	return;
}

