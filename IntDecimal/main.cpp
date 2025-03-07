#include <iostream>



int main() {

	int a = INT_MAX;
	int b = INT_MIN;
	float c = 100000;

	std::cout << c << std::endl;

	c = INT_MAX;
	c += 10000;

	if (c > a) {
		std::cout << c << std::endl;
	}
	std::cout << a << std::endl;
	std::cout << b << std::endl;

	int d = static_cast<int>(c);
	std::cout << d << std::endl;
}
