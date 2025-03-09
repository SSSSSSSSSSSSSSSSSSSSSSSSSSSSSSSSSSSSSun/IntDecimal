#include "mainLoop.h"

void displayInputMessage() {
	std::cout << "======================================" << '\n';
	std::cout << '\n';
	std::cout << "a >> A+B" << '\t';
	std::cout << "b >> A-B" << '\t';
	std::cout << "c >> A*B" << '\t';
	std::cout << "d >> A/B" << '\n';
	std::cout << "e >> A+=B" << '\t';
	std::cout << "f >> A-=B" << '\t';
	std::cout << "g >> A*=B" << '\t';
	std::cout << "h >> A/=B" << '\n';
	std::cout << "i >> A==B" << '\t';
	std::cout << "j >> A!=B" << '\n';
	std::cout << "k >> A>B" << '\t';
	std::cout << "l >> A>=B" << '\t';
	std::cout << "m >> A<B" << '\t';
	std::cout << "n >> A<=B" << '\n';
	std::cout << "o >> -A " << '\t';
	std::cout << "p >> !A " << '\t';
	std::cout << "q >> A=B" << '\n';
	std::cout << "z >> Quit" << '\n';
	std::cout << "e,f,g,h,q (+=,-=,*=,/=,=)는 A가 FixedPoint일때만 작동" << '\n';
	std::cout << "i,j,k,l,m,n (==,!=,>,>=,<,<=)은 [A:int/B:unsigned], [A:unsigned/B:int]일때 미작동" << '\n';
	std::cout << "o (-A)는 A가 int 혹은 FixedPoint일때만 작동" << '\n';
	std::cout << "======================================" << '\n';


	std::cout << "값 입력 : ";
}

void mainLoop(short* input, int& a, const int& b) {
	char operatorChoiceInput;
	while (1) {
		std::cout << "======================================" << '\n';
		std::cout << "A : " << a << '\n';
		std::cout << "B : " << b << '\n';
		displayInputMessage();
		std::cin >> operatorChoiceInput;

		switch (operatorChoiceInput) {
		case 'A':
		case 'a':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << a+b << '\n';
			break;
		case 'B':
		case 'b':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << a - b << '\n';
			break;
		case 'C':
		case 'c':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << a * b << '\n';
			break;
		case 'D':
		case 'd':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << a / b << '\n';
			break;
		case 'I':
		case 'i':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << (a==b) << '\n';
			break;
		case 'J':
		case 'j':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << (a != b) << '\n';
			break;
		case 'K':
		case 'k':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << (a > b) << '\n';
			break;
		case 'L':
		case 'l':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << (a >= b) << '\n';
			break;
		case 'M':
		case 'm':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << (a < b) << '\n';
			break;
		case 'N':
		case 'n':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << (a <= b) << '\n';
			break;
		case 'O':
		case 'o':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << -a << '\n';
			break;
		case 'P':
		case 'p':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << !a << '\n';
			break;
		case 'Z':
		case 'z':
			exit(0);
		}

	}
}

void mainLoop(short* input, int& a, const unsigned int& b) {
	char operatorChoiceInput;
	while (1) {
		std::cout << "======================================" << '\n';
		std::cout << "A : " << a << '\n';
		std::cout << "B : " << b << '\n';
		displayInputMessage();
		std::cin >> operatorChoiceInput;

		switch (operatorChoiceInput) {
		case 'A':
		case 'a':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << a + b << '\n';
			break;
		case 'B':
		case 'b':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << a - b << '\n';
			break;
		case 'C':
		case 'c':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << a * b << '\n';
			break;
		case 'D':
		case 'd':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << a / b << '\n';
			break;
		case 'O':
		case 'o':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << -a << '\n';
			break;
		case 'P':
		case 'p':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << !a << '\n';
			break;
		case 'Z':
		case 'z':
			exit(0);
		}

	}
}
void mainLoop(short* input, int& a, const FixedPoint& b) {
	char operatorChoiceInput;
	while (1) {
		std::cout << "======================================" << '\n';
		std::cout << "A : " << a << '\n';
		std::cout << "B : " << b << '\n';
		displayInputMessage();
		std::cin >> operatorChoiceInput;

		switch (operatorChoiceInput) {
		case 'A':
		case 'a':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << a + b << '\n';
			break;
		case 'B':
		case 'b':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << a - b << '\n';
			break;
		case 'C':
		case 'c':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << a * b << '\n';
			break;
		case 'D':
		case 'd':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << a / b << '\n';
			break;
		case 'I':
		case 'i':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << (a == b) << '\n';
			break;
		case 'J':
		case 'j':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << (a != b) << '\n';
			break;
		case 'K':
		case 'k':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << (a > b) << '\n';
			break;
		case 'L':
		case 'l':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << (a >= b) << '\n';
			break;
		case 'M':
		case 'm':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << (a < b) << '\n';
			break;
		case 'N':
		case 'n':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << (a <= b) << '\n';
			break;
		case 'O':
		case 'o':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << -a << '\n';
			break;
		case 'P':
		case 'p':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << !a << '\n';
			break;
		case 'Z':
		case 'z':
			exit(0);
		}

	}
}
void mainLoop(short* input, unsigned int& a, const int& b) {
	char operatorChoiceInput;
	while (1) {
		std::cout << "======================================" << '\n';
		std::cout << "A : " << a << '\n';
		std::cout << "B : " << b << '\n';
		displayInputMessage();
		std::cin >> operatorChoiceInput;

		switch (operatorChoiceInput) {
		case 'A':
		case 'a':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << a + b << '\n';
			break;
		case 'B':
		case 'b':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << a - b << '\n';
			break;
		case 'C':
		case 'c':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << a * b << '\n';
			break;
		case 'D':
		case 'd':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << a / b << '\n';
			break;
		case 'P':
		case 'p':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << !a << '\n';
			break;
		case 'Z':
		case 'z':
			exit(0);
		}

	}
}
void mainLoop(short* input, unsigned int& a, const unsigned int& b) {
	char operatorChoiceInput;
	while (1) {
		std::cout << "======================================" << '\n';
		std::cout << "A : " << a << '\n';
		std::cout << "B : " << b << '\n';
		displayInputMessage();
		std::cin >> operatorChoiceInput;

		switch (operatorChoiceInput) {
		case 'A':
		case 'a':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << a + b << '\n';
			break;
		case 'B':
		case 'b':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << a - b << '\n';
			break;
		case 'C':
		case 'c':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << a * b << '\n';
			break;
		case 'D':
		case 'd':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << a / b << '\n';
			break;
		case 'I':
		case 'i':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << (a == b) << '\n';
			break;
		case 'J':
		case 'j':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << (a != b) << '\n';
			break;
		case 'K':
		case 'k':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << (a > b) << '\n';
			break;
		case 'L':
		case 'l':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << (a >= b) << '\n';
			break;
		case 'M':
		case 'm':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << (a < b) << '\n';
			break;
		case 'N':
		case 'n':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << (a <= b) << '\n';
			break;
		case 'P':
		case 'p':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << !a << '\n';
			break;
		case 'Z':
		case 'z':
			exit(0);
		}

	}
}
void mainLoop(short* input, unsigned int& a, const FixedPoint& b) {
	char operatorChoiceInput;
	while (1) {
		std::cout << "======================================" << '\n';
		std::cout << "A : " << a << '\n';
		std::cout << "B : " << b << '\n';
		displayInputMessage();
		std::cin >> operatorChoiceInput;

		switch (operatorChoiceInput) {
		case 'A':
		case 'a':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << a + b << '\n';
			break;
		case 'B':
		case 'b':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << a - b << '\n';
			break;
		case 'C':
		case 'c':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << a * b << '\n';
			break;
		case 'D':
		case 'd':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << a / b << '\n';
			break;
		case 'I':
		case 'i':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << (a == b) << '\n';
			break;
		case 'J':
		case 'j':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << (a != b) << '\n';
			break;
		case 'K':
		case 'k':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << (a > b) << '\n';
			break;
		case 'L':
		case 'l':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << (a >= b) << '\n';
			break;
		case 'M':
		case 'm':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << (a < b) << '\n';
			break;
		case 'N':
		case 'n':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << (a <= b) << '\n';
			break;
		case 'P':
		case 'p':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << !a << '\n';
			break;
		case 'Z':
		case 'z':
			exit(0);
		}

	}
}
void mainLoop(short* input, FixedPoint& a, const int& b) {
	char operatorChoiceInput;
	while (1) {
		std::cout << "======================================" << '\n';
		std::cout << "A : " << a << '\n';
		std::cout << "B : " << b << '\n';
		displayInputMessage();
		std::cin >> operatorChoiceInput;

		switch (operatorChoiceInput) {
		case 'A':
		case 'a':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << a + b << '\n';
			break;
		case 'B':
		case 'b':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << a - b << '\n';
			break;
		case 'C':
		case 'c':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << a * b << '\n';
			break;
		case 'D':
		case 'd':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << a / b << '\n';
			break;
		case 'E':
		case 'e':
			std::cout << '\n' << "======================================" << '\n';
			a += b;
			std::cout << "result : " << a << '\n';
			break;
		case 'F':
		case 'f':
			std::cout << '\n' << "======================================" << '\n';
			a -= b;
			std::cout << "result : " << a << '\n';
			break;
		case 'G':
		case 'g':
			std::cout << '\n' << "======================================" << '\n';
			a *= b;
			std::cout << "result : " << a << '\n';
			break;
		case 'H':
		case 'h':
			std::cout << '\n' << "======================================" << '\n';
			a /= b;
			std::cout << "result : " << a << '\n';
			break;
		case 'I':
		case 'i':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << (a == b) << '\n';
			break;
		case 'J':
		case 'j':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << (a != b) << '\n';
			break;
		case 'K':
		case 'k':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << (a > b) << '\n';
			break;
		case 'L':
		case 'l':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << (a >= b) << '\n';
			break;
		case 'M':
		case 'm':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << (a < b) << '\n';
			break;
		case 'N':
		case 'n':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << (a <= b) << '\n';
			break;
		case 'P':
		case 'p':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << !a << '\n';
			break;
		case 'Q':
		case 'q':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << (a = b) << '\n';
			break;
		case 'Z':
		case 'z':
			exit(0);
		}

	}
}
void mainLoop(short* input, FixedPoint& a, const unsigned int& b) {
	char operatorChoiceInput;
	while (1) {
		std::cout << "======================================" << '\n';
		std::cout << "A : " << a << '\n';
		std::cout << "B : " << b << '\n';
		displayInputMessage();
		std::cin >> operatorChoiceInput;

		switch (operatorChoiceInput) {
		case 'A':
		case 'a':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << a + b << '\n';
			break;
		case 'B':
		case 'b':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << a - b << '\n';
			break;
		case 'C':
		case 'c':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << a * b << '\n';
			break;
		case 'D':
		case 'd':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << a / b << '\n';
			break;
		case 'E':
		case 'e':
			std::cout << '\n' << "======================================" << '\n';
			a += b;
			std::cout << "result : " << a << '\n';
			break;
		case 'F':
		case 'f':
			std::cout << '\n' << "======================================" << '\n';
			a -= b;
			std::cout << "result : " << a << '\n';
			break;
		case 'G':
		case 'g':
			std::cout << '\n' << "======================================" << '\n';
			a *= b;
			std::cout << "result : " << a << '\n';
			break;
		case 'H':
		case 'h':
			std::cout << '\n' << "======================================" << '\n';
			a /= b;
			std::cout << "result : " << a << '\n';
			break;
		case 'I':
		case 'i':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << (a == b) << '\n';
			break;
		case 'J':
		case 'j':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << (a != b) << '\n';
			break;
		case 'K':
		case 'k':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << (a > b) << '\n';
			break;
		case 'L':
		case 'l':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << (a >= b) << '\n';
			break;
		case 'M':
		case 'm':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << (a < b) << '\n';
			break;
		case 'N':
		case 'n':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << (a <= b) << '\n';
			break;
		case 'O':
		case 'o':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << -a << '\n';
			break;
		case 'P':
		case 'p':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << !a << '\n';
			break;
		case 'Q':
		case 'q':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << (a = b) << '\n';
			break;
		case 'Z':
		case 'z':
			exit(0);
		}

	}
}
void mainLoop(short* input, FixedPoint& a, const FixedPoint& b) {
	char operatorChoiceInput;
	while (1) {
		std::cout << "======================================" << '\n';
		std::cout << "A : " << a << '\n';
		std::cout << "B : " << b << '\n';
		displayInputMessage();
		std::cin >> operatorChoiceInput;

		switch (operatorChoiceInput) {
		case 'A':
		case 'a':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << a + b << '\n';
			break;
		case 'B':
		case 'b':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << a - b << '\n';
			break;
		case 'C':
		case 'c':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << a * b << '\n';
			break;
		case 'D':
		case 'd':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << a / b << '\n';
			break;
		case 'E':
		case 'e':
			std::cout << '\n' << "======================================" << '\n';
			a += b;
			std::cout << "result : " << a << '\n';
			break;
		case 'F':
		case 'f':
			std::cout << '\n' << "======================================" << '\n';
			a -= b;
			std::cout << "result : " << a << '\n';
			break;
		case 'G':
		case 'g':
			std::cout << '\n' << "======================================" << '\n';
			a *= b;
			std::cout << "result : " << a << '\n';
			break;
		case 'H':
		case 'h':
			std::cout << '\n' << "======================================" << '\n';
			a /= b;
			std::cout << "result : " << a << '\n';
			break;
		case 'I':
		case 'i':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << (a == b) << '\n';
			break;
		case 'J':
		case 'j':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << (a != b) << '\n';
			break;
		case 'K':
		case 'k':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << (a > b) << '\n';
			break;
		case 'L':
		case 'l':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << (a >= b) << '\n';
			break;
		case 'M':
		case 'm':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << (a < b) << '\n';
			break;
		case 'N':
		case 'n':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << (a <= b) << '\n';
			break;
		case 'O':
		case 'o':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << -a << '\n';
			break;
		case 'P':
		case 'p':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << !a << '\n';
			break;
		case 'Q':
		case 'q':
			std::cout << '\n' << "======================================" << '\n';
			std::cout << "result : " << (a = b) << '\n';
			break;
		case 'Z':
		case 'z':
			exit(0);
		}

	}
}