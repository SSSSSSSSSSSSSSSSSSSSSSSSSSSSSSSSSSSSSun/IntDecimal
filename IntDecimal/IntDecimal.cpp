#include "IntDecimal.h"
#include <cmath>
#include <iostream>

//=====================================
//������
//=====================================

// 0.0
IntDecimal::IntDecimal()
	: integerPart(0), decimalPart(0), isPositive(true) {}



// short�� ����				(~32768~32767)
IntDecimal::IntDecimal(const short& integer)
	: decimalPart(0)
{
	if (integer < 0) {
		integerPart = integer * -1;
		isPositive = false;
	}
	else {
		integerPart = integer;
		isPositive = true;
	}
}



// unsigned short�� ����	(0~65535)
IntDecimal::IntDecimal(const unsigned short& integer)
	: integerPart(integer), decimalPart(0), isPositive(true){}



// int�� ����				(~2147483648~2147483647)
IntDecimal::IntDecimal(const int& integer)
	: decimalPart(0)
{
	if (integer < 0) {
		integerPart = integer * -1;
		isPositive = false;
	}
	else {
		integerPart = integer;
		isPositive = true;
	}
}


// unsigned int�� ����		(0~4294967295)
IntDecimal::IntDecimal(const unsigned int& integer)
	: integerPart(integer), decimalPart(0), isPositive(true) {
}


// float�� ����	(����� �������� ����)
// (��ȿ���� 6�ڸ����� ��ȿ / �Ҽ��� 7�ڸ� ���� ����)
// (��, -2147480000 ���Ͻ� -214748000�� ǥ�� (INT_MIN == -2147483648)
// (��, +2147480000 �̻�� +214748000�� ǥ�� (INT_MAX == +2147483647)
IntDecimal::IntDecimal(float floatNumber) {

	// +2147480000 �̻�� +214748000�� ǥ��
	if (floatNumber >= 2147480000) {
		integerPart = 2147480000;
		decimalPart = 0;
		isPositive = true;
		return;
	}

	// -2147480000 ���Ͻ� -214748000�� ǥ��
	if (floatNumber <= -2147480000) {
		integerPart = 2147480000;
		decimalPart = 0;
		isPositive = false;
		return;
	}

	// 0
	if (floatNumber == 0) {
		integerPart = 0;
		decimalPart = 0;
		isPositive = true;
	}

	// ���/���� �Ǻ��ؼ� ���
	if (floatNumber >= 0) {
		isPositive = true;
	}
	else {
		isPositive = false;
		floatNumber *= -1.0f;
	}


	short numDigits = static_cast<short>(log10(floatNumber));

	// ���밪 10 �̻� �� ��

	if (numDigits > 0) {
		numDigits++;		// �ڸ��� ǥ���� ���� 1 ����

		floatNumber *= powf(10.0f, static_cast<float>(6 - numDigits));
		integerPart = static_cast<unsigned int>(floatNumber);
		if (numDigits < 6) {
			decimalPart = integerPart % static_cast<unsigned int>(pow(10, 6 - numDigits));
			integerPart /= static_cast<unsigned int>(pow(10, 6 - numDigits));
			decimalPart *= static_cast<unsigned int>(pow(10, numDigits));
		}
		else {
			integerPart *= static_cast<unsigned int>(pow(10, numDigits - 1));
			decimalPart = 0;
		}

		return;
	}
	

	// ���밪 1 �̻� 10 �̸��� ��

	if (floatNumber >= 1) {
		floatNumber *= 100000;
		integerPart = static_cast<unsigned int>(floatNumber);
		decimalPart = integerPart % 100000;
		integerPart /= 100000;
		decimalPart *= 10;

		return;
	}

	// ���밪 1 �̸��� ��

	integerPart = 0;
	decimalPart = static_cast<unsigned int>((floatNumber - integerPart) * 1000000.0f);

	if (decimalPart == 0)	// 0�϶� ��ȣ�� +�� �ٲ���
		isPositive = true;

}



// double�� ���� (����� �������� ����)
// (��ȿ���� 6�ڸ����� ��ȿ / �Ҽ��� 7�ڸ� ���� ����)
// (��, -2147483647 ���Ͻ� -2147483647�� ǥ�� (INT_MIN == -2147483648)
// (��, +2147483647 �̻�� +2147483647�� ǥ�� (INT_MAX == +2147483647)
IntDecimal::IntDecimal(double doubleNumber) {

	// +2147483647 �̻�� +2147483647�� ǥ��
	if (doubleNumber >= 2147483647) {
		integerPart = 2147483647;
		decimalPart = 0;
		isPositive = true;
		return;
	}

	// -2147483647 ���Ͻ� -2147483647�� ǥ��
	if (doubleNumber <= -2147483647) {
		integerPart = -2147483647;
		decimalPart = 0;
		isPositive = false;
		return;
	}
	
	// 0
	if (doubleNumber == 0) {
		integerPart = 0;
		decimalPart = 0;
		isPositive = true;
	}

	// ���/���� �Ǻ��ؼ� ���
	if (doubleNumber >= 0) {
		isPositive = true;
	}
	else {
		isPositive = false;
		doubleNumber *= -1;
	}

	
	short numDigits = static_cast<short>(log10(doubleNumber));

	// ���밪 10 �̻� �� ��

	if (numDigits > 0) {
		numDigits++;		// �ڸ��� ǥ���� ���� 1 ����

		doubleNumber *= pow(10.0, static_cast<double>(6 - numDigits));
		integerPart = static_cast<unsigned int>(doubleNumber);
		if (numDigits < 6) {
			decimalPart = integerPart % static_cast<unsigned int>(pow(10, 6 - numDigits));
			integerPart /= static_cast<unsigned int>(pow(10, 6 - numDigits));
			decimalPart *= static_cast<unsigned int>(pow(10, numDigits));
		}
		else {
			integerPart *= static_cast<unsigned int>(pow(10, numDigits - 1));
			decimalPart = 0;
		}

		return;
	}


	// ���밪 1 �̻� 10 �̸��� ��

	if (doubleNumber >= 1) {
		doubleNumber *= 100000;
		integerPart = static_cast<unsigned int>(doubleNumber);
		decimalPart = integerPart % 100000;
		integerPart /= 100000;
		decimalPart *= 10;
		return;
	}

	// ���밪 1 �̸��� ��

	integerPart = 0;
	decimalPart = static_cast<unsigned int>((doubleNumber - integerPart) * 1000000.0f);

	if (decimalPart == 0)	// 0�϶� ��ȣ�� +�� �ٲ���
		isPositive = true;
	
}

// ������, �Ҽ��η� ���� (�Ҽ��� 999999 �ʰ��� 0���� ���)
// �Ҽ��δ� ������ �Ҽ��� ù��° �ڸ� ���� ��
// (ex : (3,25) -> 3.250000
IntDecimal::IntDecimal(const int& inputIntegerPart, const unsigned int& inputDecimalPart){
	if (inputIntegerPart >= 0) {
		isPositive = true;
		integerPart = static_cast<unsigned int>(inputIntegerPart);
	}
	else {
		isPositive = false;
		integerPart = static_cast<unsigned int>(-inputIntegerPart);
	}
	
	if (inputDecimalPart > 999999) {
		decimalPart = 0;
		return;
	}
	int numDigits = static_cast<int>(log10(inputDecimalPart) + 1);
	decimalPart = inputDecimalPart * static_cast<unsigned int>(pow(10, 6 - numDigits));
	

}

// ������, �Ҽ���, ��ȣ�� ���� (�Ҽ��� 999999 �ʰ��� 0���� ���)
// �Ҽ��δ� ������ �Ҽ��� ù��° �ڸ� ���� ��
// (ex : (3,25) -> 3.250000
IntDecimal::IntDecimal(const unsigned int& inputIntegerPart, const unsigned int& inputDecimalPart, const bool& inputIsPositive)
	: integerPart(inputIntegerPart), isPositive(inputIsPositive)
{

	if (inputDecimalPart > 999999) {
		decimalPart = 0;
		return;
	}
	int numDigits = static_cast<int>(log10(inputDecimalPart) + 1);
	decimalPart = inputDecimalPart * static_cast<unsigned int>(pow(10, 6 - numDigits));
}

// ���������
IntDecimal::IntDecimal(const IntDecimal& original)
	: integerPart(original.integerPart), decimalPart(original.decimalPart), isPositive(original.isPositive) {}




//=====================================
//������
//=====================================

//============
//���� ������ -
//============
IntDecimal IntDecimal::operator-() const {
	return IntDecimal(this->integerPart, this->decimalPart, not (this->isPositive));
}


//============
//+
//============
 
IntDecimal IntDecimal::operator+(const short& data) const {
	unsigned int newIntegerPart;
	unsigned int newDecimalPart;
	bool dataIsPositive;

	if (data >= 0)
		dataIsPositive = true;
	else
		dataIsPositive = false;

	// + + or - -
	if (isPositive == dataIsPositive) {
		if (isPositive) {
			newIntegerPart = integerPart + static_cast<unsigned int>(data);
			return IntDecimal(newIntegerPart, decimalPart, dataIsPositive);
		}
		else {
			newIntegerPart = integerPart + static_cast<unsigned int>(-data);
			return IntDecimal(newIntegerPart, decimalPart, dataIsPositive);
		}
	}

	// ���ļ� 0
	if (this->abs() == data) {
		return IntDecimal();
	}
	
	// + -
	if (isPositive) {
		// this�� ���밪�� �� Ŭ��
		if (this->abs() > std::abs(data)) {
			newIntegerPart = integerPart - static_cast<unsigned int>(-data);
			return IntDecimal(newIntegerPart, decimalPart, isPositive);
		}
		else {
			newIntegerPart = static_cast<unsigned int>(-data) - integerPart;

			// �Ҽ��� ���, // 0�� data�� �Ҽ��θ� �ǹ� (.000000)
			if (decimalPart > 0) {
				newIntegerPart--;
				newDecimalPart = 0 + 1000000 - decimalPart;
			}
			return IntDecimal(newIntegerPart, newDecimalPart, dataIsPositive);
		}
	}
	// - +
	else {
		// this�� ���밪�� �� Ŭ��
		if (this->abs() > std::abs(data)) {
			newIntegerPart = integerPart - static_cast<unsigned int>(data);
			return IntDecimal(newIntegerPart, decimalPart, isPositive);
		}
		else {
			newIntegerPart = static_cast<unsigned int>(data) - integerPart;

			// �Ҽ��� ���, // 0�� data�� �Ҽ��θ� �ǹ� (.000000)
			if (decimalPart > 0) {
				newIntegerPart--;
				newDecimalPart = 0 + 1000000 - decimalPart;
			}
			return IntDecimal(newIntegerPart, newDecimalPart, dataIsPositive);
		}
	}

}

IntDecimal IntDecimal::operator+(const unsigned short& data) const {
	unsigned int newIntegerPart;
	unsigned int newDecimalPart;
	bool dataIsPositive = true;

	// + +
	if (isPositive == dataIsPositive) {
		newIntegerPart = integerPart + data;
		return IntDecimal(newIntegerPart, decimalPart, dataIsPositive);
	}

	// ���ļ� 0
	if (this->abs() == data) {
		return IntDecimal();
	}
	// - +

	// this�� ���밪�� �� Ŭ��
	if (this->abs() > data) {
		newIntegerPart = integerPart - data;
		return IntDecimal(newIntegerPart, decimalPart, isPositive);
	}
	else {
		newIntegerPart = data - integerPart;

		// �Ҽ��� ���, // 0�� data�� �Ҽ��θ� �ǹ� (.000000)
		if (decimalPart > 0) {
			newIntegerPart--;
			newDecimalPart = 0 + 1000000 - decimalPart;
		}
		return IntDecimal(newIntegerPart, newDecimalPart, dataIsPositive);
	}

}


IntDecimal IntDecimal::operator+(const int& data) const {
	unsigned int newIntegerPart;
	unsigned int newDecimalPart;
	bool dataIsPositive;

	if (data >= 0)
		dataIsPositive = true;
	else
		dataIsPositive = false;

	// + + or - -
	if (isPositive == dataIsPositive) {
		if (isPositive) {
			newIntegerPart = integerPart + static_cast<unsigned int>(data);
			return IntDecimal(newIntegerPart, decimalPart, dataIsPositive);
		}
		else {
			newIntegerPart = integerPart + static_cast<unsigned int>(-data);
			return IntDecimal(newIntegerPart, decimalPart, dataIsPositive);
		}
	}

	// ���ļ� 0
	if (this->abs() == data) {
		return IntDecimal();
	}

	// + -
	if (isPositive) {
		// this�� ���밪�� �� Ŭ��
		if (this->abs() > std::abs(data)) {
			newIntegerPart = integerPart - static_cast<unsigned int>(-data);
			return IntDecimal(newIntegerPart, decimalPart, isPositive);
		}
		else {
			newIntegerPart = static_cast<unsigned int>(-data) - integerPart;

			// �Ҽ��� ���, // 0�� data�� �Ҽ��θ� �ǹ� (.000000)
			if (decimalPart > 0) {
				newIntegerPart--;
				newDecimalPart = 0 + 1000000 - decimalPart;
			}
			return IntDecimal(newIntegerPart, newDecimalPart, dataIsPositive);
		}
	}
	// - +
	else {
		// this�� ���밪�� �� Ŭ��
		if (this->abs() > std::abs(data)) {
			newIntegerPart = integerPart - static_cast<unsigned int>(data);
			return IntDecimal(newIntegerPart, decimalPart, isPositive);
		}
		else {
			newIntegerPart = static_cast<unsigned int>(data) - integerPart;

			// �Ҽ��� ���, // 0�� data�� �Ҽ��θ� �ǹ� (.000000)
			if (decimalPart > 0) {
				newIntegerPart--;
				newDecimalPart = 0 + 1000000 - decimalPart;
			}
			return IntDecimal(newIntegerPart, newDecimalPart, dataIsPositive);
		}
	}
}
IntDecimal IntDecimal::operator+(const unsigned int& data) const {
	unsigned int newIntegerPart;
	unsigned int newDecimalPart;
	bool dataIsPositive = true;

	// + +
	if (isPositive == dataIsPositive) {
		newIntegerPart = integerPart + data;
		return IntDecimal(newIntegerPart, decimalPart, dataIsPositive);
	}

	// ���ļ� 0
	if (this->abs() == data) {
		return IntDecimal();
	}
	// - +

	// this�� ���밪�� �� Ŭ��
	if (this->abs() > data) {
		newIntegerPart = integerPart - data;
		return IntDecimal(newIntegerPart, decimalPart, isPositive);
	}
	else {
		newIntegerPart = data - integerPart;

		// �Ҽ��� ���, // 0�� data�� �Ҽ��θ� �ǹ� (.000000)
		if (decimalPart > 0) {
			newIntegerPart--;
			newDecimalPart = 0 + 1000000 - decimalPart;
		}
		return IntDecimal(newIntegerPart, newDecimalPart, dataIsPositive);
	}

}

IntDecimal IntDecimal::operator+(const IntDecimal& data) const {
	unsigned int newIntegerPart;
	unsigned int newDecimalPart;

	// + + or - -
	if (isPositive == data.isPositive) {
		newIntegerPart = integerPart + data.integerPart;
		newDecimalPart = decimalPart + data.decimalPart;

		if (newDecimalPart >= 1000000) {
			newIntegerPart++;
			newDecimalPart -= 1000000;
		}

		return IntDecimal(newIntegerPart, newDecimalPart, isPositive);
	}

	// ���ļ� 0
	if (this->abs() == data) {
		return IntDecimal();
	}

	// ��ȣ�� �ٸ���
	
	if (this->abs() > data.abs()) {		// this�� ���밪�� �� Ŭ��
		newIntegerPart = integerPart - data.integerPart;

		// �Ҽ��� ���
		if (decimalPart >= data.decimalPart) {
			newDecimalPart = decimalPart - data.decimalPart;
		}
		else {
			newIntegerPart--;
			newDecimalPart = (decimalPart + 1000000) - data.decimalPart;
		}
		return IntDecimal(newIntegerPart, newDecimalPart, isPositive);
	}
	else {
		newIntegerPart = data.integerPart - integerPart;

		// �Ҽ��� ���
		if (data.decimalPart >= decimalPart) {
			newDecimalPart = data.decimalPart - decimalPart;
		}
		else {
			newIntegerPart--;
			newDecimalPart = (data.decimalPart + 1000000) - decimalPart;
		}

		return IntDecimal(newIntegerPart, newDecimalPart, data.isPositive);

	}



}

//============
//-
//============

IntDecimal IntDecimal::operator-(const short& data) const {
	return IntDecimal(*this + (-data));
}
IntDecimal IntDecimal::operator-(const unsigned short& data) const {
	short signedDate = static_cast<short>(data);

	return IntDecimal(*this + (-signedDate));
}
IntDecimal IntDecimal::operator-(const int& data) const {
	return IntDecimal(*this + (-data));
}
IntDecimal IntDecimal::operator-(const unsigned int& data) const {
	int signedDate = static_cast<int>(data);

	return IntDecimal(*this + (-signedDate));
}
IntDecimal IntDecimal::operator-(const IntDecimal& data) const {
	return IntDecimal(*this + (-data));
}


//============
//*
//============

// ������ �����÷ο��(>INT_MAX*2+1) INT_MIN-0.999999 ����
IntDecimal IntDecimal::operator*(const short& data) const {
	// 0
	if (*this == 0 || data == 0)
		return IntDecimal();

	bool dataIsPositive;

	if (data >= 0)
		dataIsPositive = true;
	else
		dataIsPositive = false;

	unsigned int carry = 0;
	unsigned int newDecimalPart = 0;

	// �Ҽ��ΰ� 0�� �ƴҶ��� �۵���
	if (decimalPart) {
		unsigned int decimalDigits[6];
		for (int i = 0;i < 6;i++) {
			decimalDigits[i] = decimalPart % static_cast<int>(pow(10, 6 - i)) / static_cast<int>(pow(10, 6 - i - 1));

			// �ڸ����� 0�� �ƴҶ��� �۵���
			if (decimalDigits[i]) {
				decimalDigits[i] *= std::abs(data);
			
				carry += decimalDigits[i] / static_cast<int>(pow(10, 1 + i));
				newDecimalPart += decimalDigits[i] % static_cast<int>(pow(10, 1 + i)) * static_cast<int>(pow(10, 6 - i - 1));
			}
		}

		if (newDecimalPart >= 1000000u) {
			carry += newDecimalPart / 1000000;
			newDecimalPart %= 1000000;
		}
	}

	unsigned int newIntegerPart = 0;

	// �����ΰ� 0�� �ƴҶ��� �۵���
	if (integerPart) {
		// �����÷ο� �˻�
		if (integerPart > (INT_MAX * 2u + 1u - carry) / std::abs(data) ){
			return IntDecimal(INT_MAX * 2u + 1u, 999999, false);
		}
		newIntegerPart = integerPart * std::abs(data);

		
	}

	newIntegerPart += carry;

	return IntDecimal(newIntegerPart, newDecimalPart, not (isPositive ^ dataIsPositive));

}

// ������ �����÷ο��(>INT_MAX*2+1) INT_MIN-0.999999 ����
IntDecimal IntDecimal::operator*(const unsigned short& data) const {
	// 0
	if (*this == 0 || data == 0)
		return IntDecimal();

	unsigned int carry = 0;
	unsigned int newDecimalPart = 0;

	// �Ҽ��ΰ� 0�� �ƴҶ��� �۵���
	if (decimalPart) {
		unsigned int decimalDigits[6];
		for (int i = 0;i < 6;i++) {
			decimalDigits[i] = decimalPart % static_cast<int>(pow(10, 6 - i)) / static_cast<int>(pow(10, 6 - i - 1));

			// �ڸ����� 0�� �ƴҶ��� �۵���
			if (decimalDigits[i]) {
				decimalDigits[i] *= data;

				carry += decimalDigits[i] / static_cast<int>(pow(10, 1 + i));
				newDecimalPart += decimalDigits[i] % static_cast<int>(pow(10, 1 + i)) * static_cast<int>(pow(10, 6 - i - 1));
			}
		}

		if (newDecimalPart >= 1000000u) {
			carry += newDecimalPart / 1000000;
			newDecimalPart %= 1000000;
		}
	}

	unsigned int newIntegerPart = 0;

	// �����ΰ� 0�� �ƴҶ��� �۵���
	if (integerPart) {
		// �����÷ο� �˻�
		if (integerPart > (INT_MAX * 2u + 1u - carry) / data) {
			return IntDecimal(INT_MAX * 2u + 1u, 999999, false);
		}
		newIntegerPart = integerPart * data;


	}

	newIntegerPart += carry;

	return IntDecimal(newIntegerPart, newDecimalPart, isPositive);

}

// ������ �����÷ο��(>INT_MAX*2+1) INT_MIN-0.999999 ����
IntDecimal IntDecimal::operator*(const int& data) const {
	// 0
	if (*this == 0 || data == 0)
		return IntDecimal();

	bool dataIsPositive;

	if (data >= 0)
		dataIsPositive = true;
	else
		dataIsPositive = false;

	unsigned int carry = 0;
	unsigned int newDecimalPart = 0;

	// �Ҽ��ΰ� 0�� �ƴҶ��� �۵���
	if (decimalPart) {

		unsigned int decimalDigits[6];
		for (int i = 0;i < 6;i++) {
			decimalDigits[i] = decimalPart % static_cast<int>(pow(10, 6 - i)) / static_cast<int>(pow(10, 6 - i - 1));

			// �����÷ο� �˻�
			if (decimalDigits[i] > (INT_MAX * 2u + 1u) / data) {
				return IntDecimal(INT_MAX * 2u + 1u, 999999, false);
			}

			// �ڸ����� 0�� �ƴҶ��� �۵���
			if (decimalDigits[i]) {
				decimalDigits[i] *= std::abs(data);

				carry += decimalDigits[i] / static_cast<int>(pow(10, 1 + i));
				newDecimalPart += decimalDigits[i] % static_cast<int>(pow(10, 1 + i)) * static_cast<int>(pow(10, 6 - i - 1));
			}
		}

		if (newDecimalPart >= 1000000u) {
			carry += newDecimalPart / 1000000;
			newDecimalPart %= 1000000;
		}
	}

	unsigned int newIntegerPart = 0;

	// �����ΰ� 0�� �ƴҶ��� �۵���
	if (integerPart) {
		// �����÷ο� �˻�
		if (integerPart > (INT_MAX * 2u + 1u - carry) / std::abs(data)) {
			return IntDecimal(INT_MAX * 2u + 1u, 999999, false);
		}
		newIntegerPart = integerPart * std::abs(data);


	}

	newIntegerPart += carry;

	return IntDecimal(newIntegerPart, newDecimalPart, not (isPositive ^ dataIsPositive));
}

// ������ �����÷ο��(>INT_MAX*2+1) INT_MIN-0.999999 ����
IntDecimal IntDecimal::operator*(const unsigned int& data) const {
	// 0
	if (*this == 0 || data == 0)
		return IntDecimal();

	unsigned int carry = 0;
	unsigned int newDecimalPart = 0;

	// �Ҽ��ΰ� 0�� �ƴҶ��� �۵���
	if (decimalPart) {
		unsigned int decimalDigits[6];
		for (int i = 0;i < 6;i++) {
			decimalDigits[i] = decimalPart % static_cast<int>(pow(10, 6 - i)) / static_cast<int>(pow(10, 6 - i - 1));

			// �����÷ο� �˻�
			if (decimalDigits[i] > (INT_MAX * 2u + 1u) / data) {
				return IntDecimal(INT_MAX * 2u + 1u, 999999, false);
			}

			// �ڸ����� 0�� �ƴҶ��� �۵���
			if (decimalDigits[i]) {
				decimalDigits[i] *= data;

				carry += decimalDigits[i] / static_cast<int>(pow(10, 1 + i));
				newDecimalPart += decimalDigits[i] % static_cast<int>(pow(10, 1 + i)) * static_cast<int>(pow(10, 6 - i - 1));
			}
		}

		if (newDecimalPart >= 1000000u) {
			carry += newDecimalPart / 1000000;
			newDecimalPart %= 1000000;
		}
	}

	unsigned int newIntegerPart = 0;

	// �����ΰ� 0�� �ƴҶ��� �۵���
	if (integerPart) {
		// �����÷ο� �˻�
		if (integerPart > (INT_MAX * 2u + 1u - carry) / data) {
			return IntDecimal(INT_MAX * 2u + 1u, 999999, false);
		}
		newIntegerPart = integerPart * data;


	}

	newIntegerPart += carry;

	return IntDecimal(newIntegerPart, newDecimalPart, isPositive);

}

// ������ �����÷ο��(>INT_MAX*2+1) INT_MIN-0.999999 ����
// �Ҽ��� 7�ڸ����� �ݿø�
IntDecimal IntDecimal::operator*(const IntDecimal& data) const {

	// 0
	if (*this == 0 || data == 0)
		return IntDecimal();

//A.B * C.D = A*C + A*0.D + 0.B*C + 0.B*0.D
	IntDecimal result = IntDecimal();

	// 0.B*0.D
	unsigned long int productOfDecimalPart = decimalPart * data.decimalPart;
	result.setDecimalPart(productOfDecimalPart / 1000000);
	

	// �ݿø�
	productOfDecimalPart %= 1000000;
	productOfDecimalPart /= 100000;

	if (productOfDecimalPart >= 5)
		result.setDecimalPart(result.getDecimalPart() + 1);

	// A*0.D
	IntDecimal D(0, data.decimalPart, true);
	result += D * integerPart;
	

	// 0.B*C
	IntDecimal B(0, decimalPart, true);
	IntDecimal C(data.integerPart, 0, true);




}



//============
//+=
//============
IntDecimal& IntDecimal::operator+=(const short& data) {
	bool dataIsPositive;

	if (data >= 0)
		dataIsPositive = true;
	else
		dataIsPositive = false;

	// + + or - -
	if (isPositive == dataIsPositive) {
		if (isPositive) {
			integerPart += static_cast<unsigned int>(data);
			return *this;
		}
		else {
			integerPart += static_cast<unsigned int>(-data);
			return *this;
		}
	}

	// ���ļ� 0
	if (this->abs() == data) {
		*this = 0;
		return *this;
	}

	// + -
	if (isPositive) {
		// this�� ���밪�� �� Ŭ��
		if (this->abs() > std::abs(data)) {
			integerPart -= static_cast<unsigned int>(-data);
			return *this;
		}
		else {
			integerPart = static_cast<unsigned int>(-data) - integerPart;

			// �Ҽ��� ���, // 0�� data�� �Ҽ��θ� �ǹ� (.000000)
			if (decimalPart > 0) {
				integerPart--;
				decimalPart = 0 + 1000000 - decimalPart;
			}
			*this = -(*this);
			return *this;
		}
	}
	// - +
	else {
		// this�� ���밪�� �� Ŭ��
		if (this->abs() > std::abs(data)) {
			integerPart -= static_cast<unsigned int>(data);
			return *this;
		}
		else {
			integerPart = static_cast<unsigned int>(data) - integerPart;

			// �Ҽ��� ���, // 0�� data�� �Ҽ��θ� �ǹ� (.000000)
			if (decimalPart > 0) {
				integerPart--;
				decimalPart = 0 + 1000000 - decimalPart;
			}
			*this = -(*this);
			return *this;
		}
	}
}

IntDecimal& IntDecimal::operator+=(const unsigned short& data) {
	bool dataIsPositive = true;

	// + +
	if (isPositive == dataIsPositive) {
		integerPart += data;
		return *this;
	}

	// ���ļ� 0
	if (this->abs() == data) {
		*this = 0;
		return *this;
	}
	// - +

	// this�� ���밪�� �� Ŭ��
	if (this->abs() > data) {
		integerPart -= data;
		return *this;
	}
	else {
		integerPart = data - integerPart;

		// �Ҽ��� ���, // 0�� data�� �Ҽ��θ� �ǹ� (.000000)
		if (decimalPart > 0) {
			integerPart--;
			decimalPart = 0 + 1000000 - decimalPart;
		}
		*this = -(*this);
		return *this;
	}

}

IntDecimal& IntDecimal::operator+=(const int& data) {
	bool dataIsPositive;

	if (data >= 0)
		dataIsPositive = true;
	else
		dataIsPositive = false;

	// + + or - -
	if (isPositive == dataIsPositive) {
		if (isPositive) {
			integerPart += static_cast<unsigned int>(data);
			return *this;
		}
		else {
			integerPart += static_cast<unsigned int>(-data);
			return *this;
		}
	}

	// ���ļ� 0
	if (this->abs() == data) {
		*this = 0;
		return *this;
	}

	// + -
	if (isPositive) {
		// this�� ���밪�� �� Ŭ��
		if (this->abs() > std::abs(data)) {
			integerPart -= static_cast<unsigned int>(-data);
			return *this;
		}
		else {
			integerPart = static_cast<unsigned int>(-data) - integerPart;

			// �Ҽ��� ���, // 0�� data�� �Ҽ��θ� �ǹ� (.000000)
			if (decimalPart > 0) {
				integerPart--;
				decimalPart = 0 + 1000000 - decimalPart;
			}
			*this = -(*this);
			return *this;
		}
	}
	// - +
	else {
		// this�� ���밪�� �� Ŭ��
		if (this->abs() > std::abs(data)) {
			integerPart -= static_cast<unsigned int>(data);
			return *this;
		}
		else {
			integerPart = static_cast<unsigned int>(data) - integerPart;

			// �Ҽ��� ���, // 0�� data�� �Ҽ��θ� �ǹ� (.000000)
			if (decimalPart > 0) {
				integerPart--;
				decimalPart = 0 + 1000000 - decimalPart;
			}
			*this = -(*this);
			return *this;
		}
	}
}

IntDecimal& IntDecimal::operator+=(const unsigned int& data) {
	bool dataIsPositive = true;

	// + +
	if (isPositive == dataIsPositive) {
		integerPart += data;
		return *this;
	}

	// ���ļ� 0
	if (this->abs() == data) {
		*this = 0;
		return *this;
	}
	// - +

	// this�� ���밪�� �� Ŭ��
	if (this->abs() > data) {
		integerPart -= data;
		return *this;
	}
	else {
		integerPart = data - integerPart;

		// �Ҽ��� ���, // 0�� data�� �Ҽ��θ� �ǹ� (.000000)
		if (decimalPart > 0) {
			integerPart--;
			decimalPart = 0 + 1000000 - decimalPart;
		}
		*this = -(*this);
		return *this;
	}

}

IntDecimal& IntDecimal::operator+=(const IntDecimal& data) {

	// + + or - -
	if (isPositive == data.isPositive) {
		integerPart += data.integerPart;
		decimalPart += data.decimalPart;

		if (decimalPart >= 1000000) {
			integerPart++;
			decimalPart -= 1000000;
		}

		return *this;
	}

	// ���ļ� 0
	if (this->abs() == data) {
		*this = 0;
		return *this;
	}

	// ��ȣ�� �ٸ���

	if (this->abs() > data.abs()) {		// this�� ���밪�� �� Ŭ��
		integerPart -= data.integerPart;

		// �Ҽ��� ���
		if (decimalPart >= data.decimalPart) {
			decimalPart -= data.decimalPart;
		}
		else {
			integerPart--;
			decimalPart = (decimalPart + 1000000) - data.decimalPart;
		}
		return *this;
	}
	else {
		integerPart = data.integerPart - integerPart;

		// �Ҽ��� ���
		if (data.decimalPart >= decimalPart) {
			decimalPart = data.decimalPart - decimalPart;
		}
		else {
			integerPart--;
			decimalPart = (data.decimalPart + 1000000) - decimalPart;
		}

		*this = -(*this);
		return *this;

	}



}


//============
//==
//============

bool IntDecimal::operator==(const short& data) const {
	if (decimalPart)
		return false;

	if (isPositive && data < 0)
		return false;

	if (not isPositive && data > 0)
		return false;

	if (data == integerPart)
		return true;
	return false;
}
bool IntDecimal::operator==(const unsigned short& data) const {
	if (decimalPart)
		return false;

	if (not isPositive && data > 0)
		return false;

	if (data == integerPart)
		return true;
	return false;
}
bool IntDecimal::operator==(const int& data) const {
	if (decimalPart)
		return false;

	if (isPositive && data < 0)
		return false;

	if (not isPositive && data > 0)
		return false;

	if (data == integerPart)
		return true;
	return false;
}

bool IntDecimal::operator==(const unsigned int& data) const {
	if (decimalPart)
		return false;

	if (not isPositive && data > 0)
		return false;

	if (data == integerPart)
		return true;
	return false;
}
bool IntDecimal::operator==(const IntDecimal& data) const {
	if (not (integerPart == data.integerPart))
		return false;

	if (not (decimalPart == data.decimalPart))
		return false;

	if (not (isPositive == data.isPositive)) {
		if (integerPart == 0 && decimalPart == 0) {
			return true;
		}
		return false;
	}

	return true;
}

//============
//>=
//============

bool IntDecimal::operator>=(const short& data) const {
	
	// ������
	if (*this == data)
		return true;

	// ��ȣ �� (+>-)
	if (isPositive && data < 0)
		return true;

	// ��ȣ �� (->+)
	if (not isPositive && data > 0)
		return false;

	// ���� +�϶�
	if (isPositive) {
		if (integerPart >= static_cast<unsigned int>(data))
			return true;			// �����ΰ� ���Ƶ� 5.0�� 5�� �� ���� ������ �Ͼ�� ����
		return false;
	}

	// ���� -�϶�
	if (integerPart >= static_cast<unsigned int>(data) * -1)
		return false;				// �����ΰ� ���Ƶ� -5.0�� -5�� �� ���� ������ �Ͼ�� ����
	return true;

}
bool IntDecimal::operator>=(const unsigned short& data) const {
	// ������
	if (*this == data)
		return true;

	// *this�� -�϶�
	if (not isPositive)
		return false;

	// ���� +�϶�
	if (integerPart >= data)
		return true;				// �����ΰ� ���Ƶ� -5.0�� -5�� �� ���� ������ �Ͼ�� ����
	return false;
}

bool IntDecimal::operator>=(const int& data) const {
	// ������
	if (*this == data)
		return true;

	// ��ȣ �� (+>-)
	if (isPositive && data < 0)
		return true;

	// ��ȣ �� (->+)
	if (not isPositive && data > 0)
		return false;

	// ���� +�϶�
	if (isPositive) {
		if (integerPart >= static_cast<unsigned int>(data))
			return true;			// �����ΰ� ���Ƶ� -5.0�� -5�� �� ���� ������ �Ͼ�� ����
		return false;
	}

	// ���� -�϶�
	if (integerPart >= static_cast<unsigned int>(data) * -1)
		return false;				// �����ΰ� ���Ƶ� -5.0�� -5�� �� ���� ������ �Ͼ�� ����
	return true;
}

bool IntDecimal::operator>=(const unsigned int& data) const {
	// ������
	if (*this == data)
		return true;

	// *this�� -�϶�
	if (not isPositive)
		return false;

	// ���� +�϶�
	if (integerPart >= data)
		return true;				// �����ΰ� ���Ƶ� -5.0�� -5�� �� ���� ������ �Ͼ�� ����
	return false;
}

bool IntDecimal::operator>=(const IntDecimal& data) const {
	// ������
	if (*this == data)
		return true;

	// ��ȣ �� (+>-)
	if (isPositive && not data.isPositive)
		return true;

	// ��ȣ �� (->+)
	if (not isPositive && data.isPositive)
		return false;

	// ���� +�϶� (���밪�� ū�� �� ŭ)
	if (isPositive) {
		if (integerPart > data.integerPart)
			return true;
		if (integerPart < data.integerPart)
			return false;

		if (decimalPart > data.decimalPart)
			return true;
		return false;
	}

	// ���� -�϶� (���밪�� ������ �� ŭ)
	if (integerPart > data.integerPart)
		return false;
	if (integerPart < data.integerPart)
		return true;

	if (decimalPart > data.decimalPart)
		return false;
	return true;
}

//============
//<=
//============

bool IntDecimal::operator<=(const short& data) const {

	// ������
	if (*this == data)
		return true;

	// ��ȣ �� (+<-)
	if (isPositive && data < 0)
		return false;

	// ��ȣ �� (-<+)
	if (not isPositive && data > 0)
		return true;

	// ���� +�϶�
	if (isPositive) {
		if (integerPart >= static_cast<unsigned int>(data))
			return false;			// �����ΰ� ���Ƶ� 5.0�� 5�� �� ���� ������ �Ͼ�� ����
		return true;
	}

	// ���� -�϶�
	if (integerPart >= static_cast<unsigned int>(data) * -1)
		return true;				// �����ΰ� ���Ƶ� -5.0�� -5�� �� ���� ������ �Ͼ�� ����
	return false;

}
bool IntDecimal::operator<= (const unsigned short& data) const {
	// ������
	if (*this == data)
		return true;

	// *this�� -�϶�
	if (not isPositive)
		return true;

	// ���� +�϶�
	if (integerPart >= data)
		return false;				// �����ΰ� ���Ƶ� -5.0�� -5�� �� ���� ������ �Ͼ�� ����
	return true;
}

bool IntDecimal::operator<= (const int& data) const {
	// ������
	if (*this == data)
		return true;

	// ��ȣ �� (+<-)
	if (isPositive && data < 0)
		return false;

	// ��ȣ �� (-<+)
	if (not isPositive && data > 0)
		return true;

	// ���� +�϶�
	if (isPositive) {
		if (integerPart >= static_cast<unsigned int>(data))
			return false;			// �����ΰ� ���Ƶ� -5.0�� -5�� �� ���� ������ �Ͼ�� ����
		return true;
	}

	// ���� -�϶�
	if (integerPart >= static_cast<unsigned int>(data) * -1)
		return true;				// �����ΰ� ���Ƶ� -5.0�� -5�� �� ���� ������ �Ͼ�� ����
	return false;
}

bool IntDecimal::operator<= (const unsigned int& data) const {
	// ������
	if (*this == data)
		return true;

	// *this�� -�϶�
	if (not isPositive)
		return true;

	// ���� +�϶�
	if (integerPart >= data)
		return false;				// �����ΰ� ���Ƶ� -5.0�� -5�� �� ���� ������ �Ͼ�� ����
	return true;
}

bool IntDecimal::operator<=(const IntDecimal& data) const {
	// ������
	if (*this == data)
		return true;

	// ��ȣ �� (+<-)
	if (isPositive && not data.isPositive)
		return false;

	// ��ȣ �� (-<+)
	if (not isPositive && data.isPositive)
		return true;

	// ���� +�϶� (���밪�� ū�� �� ŭ)
	if (isPositive) {
		if (integerPart > data.integerPart)
			return false;
		if (integerPart < data.integerPart)
			return true;

		if (decimalPart > data.decimalPart)
			return false;
		return true;
	}

	// ���� -�϶� (���밪�� ������ �� ŭ)
	if (integerPart > data.integerPart)
		return true;
	if (integerPart < data.integerPart)
		return false;

	if (decimalPart > data.decimalPart)
		return true;
	return false;
}

//============
//>
//============

bool IntDecimal::operator>(const short& data) const {

	// ������
	if (*this == data)
		return false;

	// ��ȣ �� (+>=-)
	if (isPositive && data < 0)
		return true;

	// ��ȣ �� (->=+)
	if (not isPositive && data > 0)
		return false;

	// ���� +�϶�
	if (isPositive) {
		if (integerPart >= static_cast<unsigned int>(data))
			return true;			// �����ΰ� ���Ƶ� 5.0�� 5�� �� ���� ������ �Ͼ�� ����
		return false;
	}

	// ���� -�϶�
	if (integerPart >= static_cast<unsigned int>(data) * -1)
		return false;				// �����ΰ� ���Ƶ� -5.0�� -5�� �� ���� ������ �Ͼ�� ����
	return true;

}
bool IntDecimal::operator>(const unsigned short& data) const {
	// ������
	if (*this == data)
		return false;

	// *this�� -�϶�
	if (not isPositive)
		return false;

	// ���� +�϶�
	if (integerPart >= data)
		return true;				// �����ΰ� ���Ƶ� -5.0�� -5�� �� ���� ������ �Ͼ�� ����
	return false;
}

bool IntDecimal::operator>(const int& data) const {
	// ������
	if (*this == data)
		return false;

	// ��ȣ �� (+>=-)
	if (isPositive && data < 0)
		return true;

	// ��ȣ �� (->=+)
	if (not isPositive && data > 0)
		return false;

	// ���� +�϶�
	if (isPositive) {
		if (integerPart >= static_cast<unsigned int>(data))
			return true;			// �����ΰ� ���Ƶ� -5.0�� -5�� �� ���� ������ �Ͼ�� ����
		return false;
	}

	// ���� -�϶�
	if (integerPart >= static_cast<unsigned int>(data) * -1)
		return false;				// �����ΰ� ���Ƶ� -5.0�� -5�� �� ���� ������ �Ͼ�� ����
	return true;
}

bool IntDecimal::operator>(const unsigned int& data) const {
	// ������
	if (*this == data)
		return false;

	// *this�� -�϶�
	if (not isPositive)
		return false;

	// ���� +�϶�
	if (integerPart >= data)
		return true;				// �����ΰ� ���Ƶ� -5.0�� -5�� �� ���� ������ �Ͼ�� ����
	return false;
}

bool IntDecimal::operator>(const IntDecimal& data) const {
	// ������
	if (*this == data)
		return false;

	// ��ȣ �� (+>=-)
	if (isPositive && not data.isPositive)
		return true;

	// ��ȣ �� (->=+)
	if (not isPositive && data.isPositive)
		return false;

	// ���� +�϶� (���밪�� ū�� �� ŭ)
	if (isPositive) {
		if (integerPart > data.integerPart)
			return true;
		if (integerPart < data.integerPart)
			return false;

		if (decimalPart > data.decimalPart)
			return true;
		return false;
	}

	// ���� -�϶� (���밪�� ������ �� ŭ)
	if (integerPart > data.integerPart)
		return false;
	if (integerPart < data.integerPart)
		return true;

	if (decimalPart > data.decimalPart)
		return false;
	return true;
}

//============
//<
//============

bool IntDecimal::operator<(const short& data) const {

	// ������
	if (*this == data)
		return false;

	// ��ȣ �� (+<-)
	if (isPositive && data < 0)
		return false;

	// ��ȣ �� (-<+)
	if (not isPositive && data > 0)
		return true;

	// ���� +�϶�
	if (isPositive) {
		if (integerPart >= static_cast<unsigned int>(data))
			return false;			// �����ΰ� ���Ƶ� 5.0�� 5�� �� ���� ������ �Ͼ�� ����
		return true;
	}

	// ���� -�϶�
	if (integerPart >= static_cast<unsigned int>(data) * -1)
		return true;				// �����ΰ� ���Ƶ� -5.0�� -5�� �� ���� ������ �Ͼ�� ����
	return false;

}
bool IntDecimal::operator< (const unsigned short& data) const {
	// ������
	if (*this == data)
		return false;

	// *this�� -�϶�
	if (not isPositive)
		return true;

	// ���� +�϶�
	if (integerPart >= data)
		return false;				// �����ΰ� ���Ƶ� -5.0�� -5�� �� ���� ������ �Ͼ�� ����
	return true;
}

bool IntDecimal::operator< (const int& data) const {
	// ������
	if (*this == data)
		return false;

	// ��ȣ �� (+<-)
	if (isPositive && data < 0)
		return false;

	// ��ȣ �� (-<+)
	if (not isPositive && data > 0)
		return true;

	// ���� +�϶�
	if (isPositive) {
		if (integerPart >= static_cast<unsigned int>(data))
			return false;			// �����ΰ� ���Ƶ� -5.0�� -5�� �� ���� ������ �Ͼ�� ����
		return true;
	}

	// ���� -�϶�
	if (integerPart >= static_cast<unsigned int>(data) * -1)
		return true;				// �����ΰ� ���Ƶ� -5.0�� -5�� �� ���� ������ �Ͼ�� ����
	return false;
}

bool IntDecimal::operator< (const unsigned int& data) const {
	// ������
	if (*this == data)
		return false;

	// *this�� -�϶�
	if (not isPositive)
		return true;

	// ���� +�϶�
	if (integerPart >= data)
		return false;				// �����ΰ� ���Ƶ� -5.0�� -5�� �� ���� ������ �Ͼ�� ����
	return true;
}

bool IntDecimal::operator<(const IntDecimal& data) const {
	// ������
	if (*this == data)
		return false;

	// ��ȣ �� (+<-)
	if (isPositive && not data.isPositive)
		return false;

	// ��ȣ �� (-<+)
	if (not isPositive && data.isPositive)
		return true;

	// ���� +�϶� (���밪�� ū�� �� ŭ)
	if (isPositive) {
		if (integerPart > data.integerPart)
			return false;
		if (integerPart < data.integerPart)
			return true;

		if (decimalPart > data.decimalPart)
			return false;
		return true;
	}

	// ���� -�϶� (���밪�� ������ �� ŭ)
	if (integerPart > data.integerPart)
		return true;
	if (integerPart < data.integerPart)
		return false;

	if (decimalPart > data.decimalPart)
		return true;
	return false;
}

IntDecimal& IntDecimal::operator=(const short& data) {
	decimalPart = 0;
	if (data < 0) {
		integerPart = data * -1;
		isPositive = false;
	}
	else {
		integerPart = data;
		isPositive = true;
	}
	return *this;
}

IntDecimal& IntDecimal::operator=(const unsigned short& data) {
	decimalPart = 0;
	integerPart = data;
	isPositive = true;
}

IntDecimal& IntDecimal::operator=(const int& data) {
	decimalPart = 0;
	if (data < 0) {
		integerPart = data * -1;
		isPositive = false;
	}
	else {
		integerPart = data;
		isPositive = true;
	}
	return *this;
}

IntDecimal& IntDecimal::operator=(const unsigned int& data) {
	decimalPart = 0;
	integerPart = data;
	isPositive = true;
}

//(��ȿ���� 6�ڸ����� ��ȿ / �Ҽ��� 7�ڸ� ���� ����)
//(����� �������� ����)
//(��, -2147480000 ���Ͻ� -214748000�� ǥ�� (INT_MIN == -2147483648)
//(��, +2147480000 �̻�� +214748000�� ǥ�� (INT_MAX == +2147483647)

IntDecimal& IntDecimal::operator=(float data) {
	// +2147480000 �̻�� +214748000�� ǥ��
	if (data >= 2147480000) {
		integerPart = 2147480000;
		decimalPart = 0;
		isPositive = true;
		return *this;
	}

	// -2147480000 ���Ͻ� -214748000�� ǥ��
	if (data <= -2147480000) {
		integerPart = 2147480000;
		decimalPart = 0;
		isPositive = false;
		return *this;
	}

	// 0
	if (data == 0) {
		integerPart = 0;
		decimalPart = 0;
		isPositive = true;
	}

	// ���/���� �Ǻ��ؼ� ���
	if (data >= 0) {
		isPositive = true;
	}
	else {
		isPositive = false;
		data *= -1.0f;
	}


	short numDigits = static_cast<short>(log10(data));

	// ���밪 10 �̻� �� ��

	if (numDigits > 0) {
		numDigits++;		// �ڸ��� ǥ���� ���� 1 ����

		data *= powf(10.0f, static_cast<float>(6 - numDigits));
		integerPart = static_cast<unsigned int>(data);
		if (numDigits < 6) {
			decimalPart = integerPart % static_cast<unsigned int>(pow(10, 6 - numDigits));
			integerPart /= static_cast<unsigned int>(pow(10, 6 - numDigits));
			decimalPart *= static_cast<unsigned int>(pow(10, numDigits));
		}
		else {
			integerPart *= static_cast<unsigned int>(pow(10, numDigits - 1));
			decimalPart = 0;
		}

		return *this;
	}


	// ���밪 1 �̻� 10 �̸��� ��

	if (data >= 1) {
		data *= 100000;
		integerPart = static_cast<unsigned int>(data);
		decimalPart = integerPart % 100000;
		integerPart /= 100000;
		decimalPart *= 10;

		return *this;
	}

	// ���밪 1 �̸��� ��

	integerPart = 0;
	decimalPart = static_cast<unsigned int>((data - integerPart) * 1000000.0f);

	if (decimalPart == 0)	// 0�϶� ��ȣ�� +�� �ٲ���
		isPositive = true;

	return *this;
}

//(��ȿ���� 6�ڸ����� ��ȿ / �Ҽ��� 7�ڸ� ���� ����)
//(����� �������� ����)
//(��, -2147483647 ���Ͻ� -2147483647�� ǥ�� (INT_MIN == -2147483648)
//(��, +2147483647 �̻�� +2147483647�� ǥ�� (INT_MAX == +2147483647)
IntDecimal& IntDecimal::operator=(double data) {
	// +2147483647 �̻�� +2147483647�� ǥ��
	if (data >= 2147483647) {
		integerPart = 2147483647;
		decimalPart = 0;
		isPositive = true;
		return *this;
	}

	// -2147483647 ���Ͻ� -2147483647�� ǥ��
	if (data <= -2147483647) {
		integerPart = -2147483647;
		decimalPart = 0;
		isPositive = false;
		return *this;
	}


	// ���/���� �Ǻ��ؼ� ���
	if (data >= 0) {
		isPositive = true;
	}
	else {
		isPositive = false;
		data *= -1;
	}

	short numDigits = static_cast<short>(log10(data));

	// ���밪 10 �̻� �� ��

	if (numDigits > 0) {
		numDigits++;		// �ڸ��� ǥ���� ���� 1 ����

		data *= pow(10.0, static_cast<double>(6 - numDigits));
		integerPart = static_cast<unsigned int>(data);
		if (numDigits < 6) {
			decimalPart = integerPart % static_cast<unsigned int>(pow(10, 6 - numDigits));
			integerPart /= static_cast<unsigned int>(pow(10, 6 - numDigits));
			decimalPart *= static_cast<unsigned int>(pow(10, numDigits));
		}
		else {
			integerPart *= static_cast<unsigned int>(pow(10, numDigits - 1));
			decimalPart = 0;
		}

		return *this;
	}


	// ���밪 1 �̻� 10 �̸��� ��

	if (data >= 1) {
		data *= 100000;
		integerPart = static_cast<unsigned int>(data);
		decimalPart = integerPart % 100000;
		integerPart /= 100000;
		decimalPart *= 10;

		return *this;
	}

	// ���밪 1 �̸��� ��

	integerPart = 0;
	decimalPart = static_cast<unsigned int>((data - integerPart) * 1000000.0f);

	if (decimalPart == 0)	// 0�϶� ��ȣ�� +�� �ٲ���
		isPositive = true;

	return *this;
}

IntDecimal& IntDecimal::operator=(const IntDecimal& data) {
	integerPart = data.integerPart;
	decimalPart = data.decimalPart;
	isPositive = data.isPositive;

	return *this;
}



bool IntDecimal::operator!() const {
	if (integerPart)
		return true;
	if (decimalPart)
		return true;
}

//=====================================
//�� ��
//=====================================


// Int�� ��ȯ				(�Ҽ��� ���� ����)
int IntDecimal::toInt() const {
	int toIntResult = integerPart;
	if (not isPositive)
		toIntResult *= -1;

	return toIntResult;
}

// UnsignedInt�� ��ȯ		(�Ҽ��� ����/��ȣ(-) ����)
unsigned int IntDecimal::toUnsignedInt() const {
	unsigned int toIntResult = integerPart;
	return toIntResult;
}

// float�� ��ȯ
float IntDecimal::toFloat() const {
	float toFloatResult = integerPart + (static_cast<float>(decimalPart) * 0.000001f);
	if (not isPositive)
		toFloatResult *= -1;
	
	return toFloatResult;
}

// Double�� ��ȯ
double IntDecimal::toDouble() const {
	double toDoubleResult = integerPart + (static_cast<double>(decimalPart) * 0.000001);
	if (not isPositive)
		toDoubleResult *= -1;

	return toDoubleResult;
}

// ���밪 ����
IntDecimal IntDecimal::abs() const {
	return IntDecimal(integerPart, decimalPart, true);
}

// ������ ����
unsigned int IntDecimal::getIntegerPart() const {
	return integerPart;
}


// �Ҽ��� ����
unsigned int IntDecimal::getDecimalPart() const {
	return decimalPart;
}

// ��ȣ ����
bool IntDecimal::getSign() const {
	return isPositive;
}

// ��ȣ ���
char IntDecimal::printSign() const {
	if (isPositive)
		return '+';
	else
		return '-';
}

// ������ ����
void IntDecimal::setIntegerPart(unsigned int data) {
	integerPart = data;
	return;
}

// �Ҽ��� ����
// data�� 999999 �ʰ��Ͻ� �ƹ��ϵ� �Ͼ�� ����
void IntDecimal::setDecimalPart(unsigned int data) {
	if (data > 999999)
		return;

	decimalPart = data;
	return;
}

// ��ȣ ����
void IntDecimal::setIsPositive(bool data) {
	isPositive = data;
	return;
}