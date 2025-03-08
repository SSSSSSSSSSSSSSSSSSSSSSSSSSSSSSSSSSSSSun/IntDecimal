#include "IntDecimal.h"
#include <cmath>


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


// float�� ����				(��ȿ���� 6�ڸ����� ��ȿ / �Ҽ��� 7�ڸ� ���� ����)
//							(��, -2147480000 ���Ͻ� -214748000�� ǥ�� (INT_MIN == -2147483648)
//							(��, +2147480000 �̻�� +214748000�� ǥ�� (INT_MAX == +2147483647)
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


	short numDigits = log10(floatNumber);

	// ���밪 10 �̻� �� ��

	if (numDigits > 0) {
		numDigits++;		// �ڸ��� ǥ���� ���� 1 ����

		floatNumber *= powf(10.0f, static_cast<float>(6 - numDigits));
		integerPart = static_cast<int>(floatNumber);
		if (numDigits < 6) {
			decimalPart = integerPart % static_cast<int>(pow(10, 6 - numDigits));
			integerPart /= static_cast<int>(pow(10, 6 - numDigits));
			decimalPart *= static_cast<int>(pow(10, numDigits));
		}
		else {
			integerPart *= static_cast<int>(pow(10, numDigits - 1));
			decimalPart = 0;
		}

		return;
	}
	

	// ���밪 1 �̻� 10 �̸��� ��

	if (floatNumber >= 1) {
		floatNumber *= 100000;
		integerPart = static_cast<int>(floatNumber);
		decimalPart = integerPart % 100000;
		integerPart /= 100000;
		decimalPart *= 10;

		return;
	}

	// ���밪 1 �̸��� ��

	integerPart = 0;
	decimalPart = static_cast<int>((floatNumber - integerPart) * 1000000.0f);

	if (decimalPart == 0)	// 0�϶� ��ȣ�� +�� �ٲ���
		isPositive = true;

}



// double�� ����			(�Ҽ��� 7�ڸ� ���� ����)
//							(��, -2147483647 ���Ͻ� -2147483647�� ǥ�� (INT_MIN == -2147483648)
//							(��, +2147483647 �̻�� +2147483647�� ǥ�� (INT_MAX == +2147483647)
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
	

	// ���/���� �Ǻ��ؼ� ���
	if (doubleNumber >= 0) {
		isPositive = true;
	}
	else {
		isPositive = false;
		doubleNumber *= -1;
	}

	integerPart = static_cast<int>(doubleNumber);
	decimalPart = static_cast<int>((doubleNumber - integerPart) * 1000000.0);

	if (integerPart == 0 && decimalPart == 0)	// 0�϶� ��ȣ�� +�� �ٲ���
		isPositive = true;
}



// ���������
IntDecimal::IntDecimal(const IntDecimal& original)
	: integerPart(original.integerPart), decimalPart(original.decimalPart), isPositive(original.isPositive) {}




//=====================================
//������
//=====================================















//=====================================
//�� ��
//=====================================


// Int�� ��ȯ				(�Ҽ��� ���� ����)
int IntDecimal::toInt() {
	int toIntResult = integerPart;
	if (not isPositive)
		toIntResult *= -1;

	return toIntResult;
}

// UnsignedInt�� ��ȯ		(�Ҽ��� ����/��ȣ(-) ����)
unsigned int IntDecimal::toUnsignedInt() {
	unsigned int toIntResult = integerPart;
	return toIntResult;
}

// float�� ��ȯ
float IntDecimal::toFloat() {
	float toFloatResult = integerPart + (static_cast<float>(decimalPart) * 0.000001f);
	if (not isPositive)
		toFloatResult *= -1;
	
	return toFloatResult;
}

// Double�� ��ȯ
double IntDecimal::toDouble() {
	double toDoubleResult = integerPart + (static_cast<double>(decimalPart) * 0.000001);
	if (not isPositive)
		toDoubleResult *= -1;

	return toDoubleResult;
}



// ������ ����
int IntDecimal::getIntegerPart() {
	return integerPart;
}


// �Ҽ��� ����
int IntDecimal::getDecimalPart() {
	return decimalPart;
}

// ��ȣ ����
bool IntDecimal::getSign() {
	return isPositive;
}

// ��ȣ ���
char IntDecimal::printSign() {
	if (isPositive)
		return '+';
	else
		return '-';
}