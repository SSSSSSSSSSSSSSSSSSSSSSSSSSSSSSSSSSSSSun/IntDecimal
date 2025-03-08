#include "IntDecimal.h"
#include <cmath>


//=====================================
//생성자
//=====================================

// 0.0
IntDecimal::IntDecimal()
	: integerPart(0), decimalPart(0), isPositive(true) {}



// short로 생성				(~32768~32767)
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



// unsigned short로 생성	(0~65535)
IntDecimal::IntDecimal(const unsigned short& integer)
	: integerPart(integer), decimalPart(0), isPositive(true){}



// int로 생성				(~2147483648~2147483647)
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


// unsigned int로 생성		(0~4294967295)
IntDecimal::IntDecimal(const unsigned int& integer)
	: integerPart(integer), decimalPart(0), isPositive(true) {
}


// float로 생성				(유효숫자 6자리까지 유효 / 소수점 7자리 이하 절삭)
//							(단, -2147480000 이하시 -214748000로 표기 (INT_MIN == -2147483648)
//							(단, +2147480000 이상시 +214748000로 표기 (INT_MAX == +2147483647)
IntDecimal::IntDecimal(float floatNumber) {

	// +2147480000 이상시 +214748000로 표기
	if (floatNumber >= 2147480000) {
		integerPart = 2147480000;
		decimalPart = 0;
		isPositive = true;
		return;
	}

	// -2147480000 이하시 -214748000로 표기
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

	// 양수/음수 판별해서 계산
	if (floatNumber >= 0) {
		isPositive = true;
	}
	else {
		isPositive = false;
		floatNumber *= -1.0f;
	}


	short numDigits = log10(floatNumber);

	// 절대값 10 이상 인 수

	if (numDigits > 0) {
		numDigits++;		// 자리수 표현을 위해 1 더함

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
	

	// 절대값 1 이상 10 미만인 수

	if (floatNumber >= 1) {
		floatNumber *= 100000;
		integerPart = static_cast<int>(floatNumber);
		decimalPart = integerPart % 100000;
		integerPart /= 100000;
		decimalPart *= 10;

		return;
	}

	// 절대값 1 미만인 수

	integerPart = 0;
	decimalPart = static_cast<int>((floatNumber - integerPart) * 1000000.0f);

	if (decimalPart == 0)	// 0일때 부호를 +로 바꿔줌
		isPositive = true;

}



// double로 생성			(소수점 7자리 이하 절삭)
//							(단, -2147483647 이하시 -2147483647로 표기 (INT_MIN == -2147483648)
//							(단, +2147483647 이상시 +2147483647로 표기 (INT_MAX == +2147483647)
IntDecimal::IntDecimal(double doubleNumber) {

	// +2147483647 이상시 +2147483647로 표기
	if (doubleNumber >= 2147483647) {
		integerPart = 2147483647;
		decimalPart = 0;
		isPositive = true;
		return;
	}

	// -2147483647 이하시 -2147483647로 표기
	if (doubleNumber <= -2147483647) {
		integerPart = -2147483647;
		decimalPart = 0;
		isPositive = false;
		return;
	}
	

	// 양수/음수 판별해서 계산
	if (doubleNumber >= 0) {
		isPositive = true;
	}
	else {
		isPositive = false;
		doubleNumber *= -1;
	}

	integerPart = static_cast<int>(doubleNumber);
	decimalPart = static_cast<int>((doubleNumber - integerPart) * 1000000.0);

	if (integerPart == 0 && decimalPart == 0)	// 0일때 부호를 +로 바꿔줌
		isPositive = true;
}



// 복사생성자
IntDecimal::IntDecimal(const IntDecimal& original)
	: integerPart(original.integerPart), decimalPart(original.decimalPart), isPositive(original.isPositive) {}




//=====================================
//연산자
//=====================================















//=====================================
//그 외
//=====================================


// Int로 변환				(소수점 이하 절삭)
int IntDecimal::toInt() {
	int toIntResult = integerPart;
	if (not isPositive)
		toIntResult *= -1;

	return toIntResult;
}

// UnsignedInt로 변환		(소수점 이하/부호(-) 절삭)
unsigned int IntDecimal::toUnsignedInt() {
	unsigned int toIntResult = integerPart;
	return toIntResult;
}

// float로 변환
float IntDecimal::toFloat() {
	float toFloatResult = integerPart + (static_cast<float>(decimalPart) * 0.000001f);
	if (not isPositive)
		toFloatResult *= -1;
	
	return toFloatResult;
}

// Double로 변환
double IntDecimal::toDouble() {
	double toDoubleResult = integerPart + (static_cast<double>(decimalPart) * 0.000001);
	if (not isPositive)
		toDoubleResult *= -1;

	return toDoubleResult;
}



// 정수부 전달
int IntDecimal::getIntegerPart() {
	return integerPart;
}


// 소수부 전달
int IntDecimal::getDecimalPart() {
	return decimalPart;
}

// 부호 전달
bool IntDecimal::getSign() {
	return isPositive;
}

// 부호 출력
char IntDecimal::printSign() {
	if (isPositive)
		return '+';
	else
		return '-';
}