#include "IntDecimal.h"
#include <cmath>
#include <iostream>

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


// float로 생성	(사용을 권장하지 않음)
// (유효숫자 6자리까지 유효 / 소수점 7자리 이하 절삭)
// (단, -2147480000 이하시 -214748000로 표기 (INT_MIN == -2147483648)
// (단, +2147480000 이상시 +214748000로 표기 (INT_MAX == +2147483647)
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


	short numDigits = static_cast<short>(log10(floatNumber));

	// 절대값 10 이상 인 수

	if (numDigits > 0) {
		numDigits++;		// 자리수 표현을 위해 1 더함

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
	

	// 절대값 1 이상 10 미만인 수

	if (floatNumber >= 1) {
		floatNumber *= 100000;
		integerPart = static_cast<unsigned int>(floatNumber);
		decimalPart = integerPart % 100000;
		integerPart /= 100000;
		decimalPart *= 10;

		return;
	}

	// 절대값 1 미만인 수

	integerPart = 0;
	decimalPart = static_cast<unsigned int>((floatNumber - integerPart) * 1000000.0f);

	if (decimalPart == 0)	// 0일때 부호를 +로 바꿔줌
		isPositive = true;

}



// double로 생성 (사용을 권장하지 않음.)
// (유효숫자 6자리까지 유효 / 소수점 7자리 이하 절삭)
// (단, -2147483647 이하시 -2147483647로 표기 (INT_MIN == -2147483648)
// (단, +2147483647 이상시 +2147483647로 표기 (INT_MAX == +2147483647)
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
	
	// 0
	if (doubleNumber == 0) {
		integerPart = 0;
		decimalPart = 0;
		isPositive = true;
	}

	// 양수/음수 판별해서 계산
	if (doubleNumber >= 0) {
		isPositive = true;
	}
	else {
		isPositive = false;
		doubleNumber *= -1;
	}

	
	short numDigits = static_cast<short>(log10(doubleNumber));

	// 절대값 10 이상 인 수

	if (numDigits > 0) {
		numDigits++;		// 자리수 표현을 위해 1 더함

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


	// 절대값 1 이상 10 미만인 수

	if (doubleNumber >= 1) {
		doubleNumber *= 100000;
		integerPart = static_cast<unsigned int>(doubleNumber);
		decimalPart = integerPart % 100000;
		integerPart /= 100000;
		decimalPart *= 10;
		return;
	}

	// 절대값 1 미만인 수

	integerPart = 0;
	decimalPart = static_cast<unsigned int>((doubleNumber - integerPart) * 1000000.0f);

	if (decimalPart == 0)	// 0일때 부호를 +로 바꿔줌
		isPositive = true;
	
}

// 정수부, 소수부로 생성 (소수부 999999 초과시 0으로 계산)
IntDecimal::IntDecimal(int& inputIntegerPart, const unsigned int& inputDecimalPart){
	if (inputIntegerPart >= 0) {
		isPositive = true;
		integerPart = static_cast<unsigned int>(inputIntegerPart);
	}
	else {
		isPositive = false;
		integerPart = static_cast<unsigned int>(-inputIntegerPart);
	}
	
	decimalPart = inputDecimalPart;
	if (inputDecimalPart > 999999)
		decimalPart = 0;

}

// 정수부, 소수부, 부호로 생성 (소수부 999999 초과시 0으로 계산)
IntDecimal::IntDecimal(const unsigned int& inputIntegerPart, const unsigned int& inputDecimalPart, const bool& inputIsPositive)
	: integerPart(inputIntegerPart), decimalPart(inputDecimalPart), isPositive(inputIsPositive)
{}

// 복사생성자
IntDecimal::IntDecimal(const IntDecimal& original)
	: integerPart(original.integerPart), decimalPart(original.decimalPart), isPositive(original.isPositive) {}




//=====================================
//연산자
//=====================================

//============
//단항 연산자 -
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

	// 합쳐서 0
	if (-(*this) == data) {
		return IntDecimal();
	}
	
	// + -
	if (isPositive) {
		// this의 절대값이 더 클때
		if (*this > -data) {
			newIntegerPart = integerPart - static_cast<unsigned int>(-data);
			return IntDecimal(newIntegerPart, decimalPart, isPositive);
		}
		else {
			newIntegerPart = static_cast<unsigned int>(-data) - integerPart;

			// 소수부 계산, // 0은 data의 소수부를 의미 (.000000)
			if (decimalPart > 0) {
				newIntegerPart--;
				newDecimalPart = 0 + 1000000 - decimalPart;
			}
			return IntDecimal(newIntegerPart, newDecimalPart, dataIsPositive);
		}
	}
	// - +
	else {
		// data의 절대값이 더 클때
		if (-(*this) > data) {
			newIntegerPart = integerPart - static_cast<unsigned int>(data);
			return IntDecimal(newIntegerPart, decimalPart, isPositive);
		}
		else {
			newIntegerPart = static_cast<unsigned int>(data) - integerPart;

			// 소수부 계산, // 0은 data의 소수부를 의미 (.000000)
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

	// 합쳐서 0
	if (-(*this) == data) {
		return IntDecimal();
	}
	// - +
	else {
		// data의 절대값이 더 클때
		if (-(*this) > data) {
			newIntegerPart = integerPart - data;
			return IntDecimal(newIntegerPart, decimalPart, isPositive);
		}
		else {
			newIntegerPart = data - integerPart;

			// 소수부 계산, // 0은 data의 소수부를 의미 (.000000)
			if (decimalPart > 0) {
				newIntegerPart--;
				newDecimalPart = 0 + 1000000 - decimalPart;
			}
			return IntDecimal(newIntegerPart, newDecimalPart, dataIsPositive);
		}
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

	// 합쳐서 0
	if (-(*this) == data) {
		return IntDecimal();
	}

	// + -
	if (isPositive) {
		// this의 절대값이 더 클때
		if (*this > -data) {
			newIntegerPart = integerPart - static_cast<unsigned int>(-data);
			return IntDecimal(newIntegerPart, decimalPart, isPositive);
		}
		else {
			newIntegerPart = static_cast<unsigned int>(-data) - integerPart;

			// 소수부 계산, // 0은 data의 소수부를 의미 (.000000)
			if (decimalPart > 0) {
				newIntegerPart--;
				newDecimalPart = 0 + 1000000 - decimalPart;
			}
			return IntDecimal(newIntegerPart, newDecimalPart, dataIsPositive);
		}
	}
	// - +
	else {
		// data의 절대값이 더 클때
		if (-(*this) > data) {
			newIntegerPart = integerPart - static_cast<unsigned int>(data);
			return IntDecimal(newIntegerPart, decimalPart, isPositive);
		}
		else {
			newIntegerPart = static_cast<unsigned int>(data) - integerPart;

			// 소수부 계산, // 0은 data의 소수부를 의미 (.000000)
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

	// 합쳐서 0
	if (-(*this) == data) {
		return IntDecimal();
	}
	// - +
	else {
		// data의 절대값이 더 클때
		if (-(*this) > data) {
			newIntegerPart = integerPart - data;
			return IntDecimal(newIntegerPart, decimalPart, isPositive);
		}
		else {
			newIntegerPart = data - integerPart;

			// 소수부 계산, // 0은 data의 소수부를 의미 (.000000)
			if (decimalPart > 0) {
				newIntegerPart--;
				newDecimalPart = 0 + 1000000 - decimalPart;
			}
			return IntDecimal(newIntegerPart, newDecimalPart, dataIsPositive);
		}
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

	// 합쳐서 0
	if (-(*this) == data) {
		return IntDecimal();
	}

	// 부호가 다를때
	
	if (this->abc() > data.abc()) {		// this의 절대값이 더 클때
		newIntegerPart = integerPart - data.integerPart;

		// 소수부 계산
		if (decimalPart >= data.decimalPart) {
			newDecimalPart = decimalPart - data.decimalPart;
		}
		else {
			newIntegerPart--;
			newDecimalPart = (decimalPart + 1000000) - data.decimalPart;
		}
		std::cout << 9;
		return IntDecimal(newIntegerPart, newDecimalPart, isPositive);
	}
	else {
		newIntegerPart = data.integerPart - integerPart;

		// 소수부 계산
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
//==
//============

bool IntDecimal::operator==(const short& data) const {
	if (not decimalPart)
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
	if (not decimalPart)
		return false;

	if (not isPositive && data > 0)
		return false;

	if (data == integerPart)
		return true;
	return false;
}
bool IntDecimal::operator==(const int& data) const {
	if (not decimalPart)
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
	if (not decimalPart)
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
	
	// 같을때
	if (*this == data)
		return true;

	// 부호 비교 (+>-)
	if (isPositive && data < 0)
		return true;

	// 부호 비교 (->+)
	if (not isPositive && data > 0)
		return false;

	// 서로 +일때
	if (isPositive) {
		if (integerPart >= static_cast<unsigned int>(data))
			return true;			// 정수부가 같아도 5.0와 5의 비교 같은 행위는 일어나지 않음
		return false;
	}

	// 서로 -일때
	if (integerPart >= static_cast<unsigned int>(data) * -1)
		return false;				// 정수부가 같아도 -5.0와 -5의 비교 같은 행위는 일어나지 않음
	return true;

}
bool IntDecimal::operator>=(const unsigned short& data) const {
	// 같을때
	if (*this == data)
		return true;

	// *this가 -일때
	if (not isPositive)
		return false;

	// 서로 +일때
	if (integerPart >= data)
		return true;				// 정수부가 같아도 -5.0와 -5의 비교 같은 행위는 일어나지 않음
	return false;
}

bool IntDecimal::operator>=(const int& data) const {
	// 같을때
	if (*this == data)
		return true;

	// 부호 비교 (+>-)
	if (isPositive && data < 0)
		return true;

	// 부호 비교 (->+)
	if (not isPositive && data > 0)
		return false;

	// 서로 +일때
	if (isPositive) {
		if (integerPart >= static_cast<unsigned int>(data))
			return true;			// 정수부가 같아도 -5.0와 -5의 비교 같은 행위는 일어나지 않음
		return false;
	}

	// 서로 -일때
	if (integerPart >= static_cast<unsigned int>(data) * -1)
		return false;				// 정수부가 같아도 -5.0와 -5의 비교 같은 행위는 일어나지 않음
	return true;
}

bool IntDecimal::operator>=(const unsigned int& data) const {
	// 같을때
	if (*this == data)
		return true;

	// *this가 -일때
	if (not isPositive)
		return false;

	// 서로 +일때
	if (integerPart >= data)
		return true;				// 정수부가 같아도 -5.0와 -5의 비교 같은 행위는 일어나지 않음
	return false;
}

bool IntDecimal::operator>=(const IntDecimal& data) const {
	// 같을때
	if (*this == data)
		return true;

	// 부호 비교 (+>-)
	if (isPositive && not data.isPositive)
		return true;

	// 부호 비교 (->+)
	if (not isPositive && data.isPositive)
		return false;

	// 서로 +일때 (절대값이 큰게 더 큼)
	if (isPositive) {
		if (integerPart > data.integerPart)
			return true;
		if (integerPart < data.integerPart)
			return false;

		if (decimalPart > data.decimalPart)
			return true;
		return false;
	}

	// 서로 -일때 (절대값이 작은게 더 큼)
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

	// 같을때
	if (*this == data)
		return true;

	// 부호 비교 (+<-)
	if (isPositive && data < 0)
		return false;

	// 부호 비교 (-<+)
	if (not isPositive && data > 0)
		return true;

	// 서로 +일때
	if (isPositive) {
		if (integerPart >= static_cast<unsigned int>(data))
			return false;			// 정수부가 같아도 5.0와 5의 비교 같은 행위는 일어나지 않음
		return true;
	}

	// 서로 -일때
	if (integerPart >= static_cast<unsigned int>(data) * -1)
		return true;				// 정수부가 같아도 -5.0와 -5의 비교 같은 행위는 일어나지 않음
	return false;

}
bool IntDecimal::operator<= (const unsigned short& data) const {
	// 같을때
	if (*this == data)
		return true;

	// *this가 -일때
	if (not isPositive)
		return true;

	// 서로 +일때
	if (integerPart >= data)
		return false;				// 정수부가 같아도 -5.0와 -5의 비교 같은 행위는 일어나지 않음
	return true;
}

bool IntDecimal::operator<= (const int& data) const {
	// 같을때
	if (*this == data)
		return true;

	// 부호 비교 (+<-)
	if (isPositive && data < 0)
		return false;

	// 부호 비교 (-<+)
	if (not isPositive && data > 0)
		return true;

	// 서로 +일때
	if (isPositive) {
		if (integerPart >= static_cast<unsigned int>(data))
			return false;			// 정수부가 같아도 -5.0와 -5의 비교 같은 행위는 일어나지 않음
		return true;
	}

	// 서로 -일때
	if (integerPart >= static_cast<unsigned int>(data) * -1)
		return true;				// 정수부가 같아도 -5.0와 -5의 비교 같은 행위는 일어나지 않음
	return false;
}

bool IntDecimal::operator<= (const unsigned int& data) const {
	// 같을때
	if (*this == data)
		return true;

	// *this가 -일때
	if (not isPositive)
		return true;

	// 서로 +일때
	if (integerPart >= data)
		return false;				// 정수부가 같아도 -5.0와 -5의 비교 같은 행위는 일어나지 않음
	return true;
}

bool IntDecimal::operator<=(const IntDecimal& data) const {
	// 같을때
	if (*this == data)
		return true;

	// 부호 비교 (+<-)
	if (isPositive && not data.isPositive)
		return false;

	// 부호 비교 (-<+)
	if (not isPositive && data.isPositive)
		return true;

	// 서로 +일때 (절대값이 큰게 더 큼)
	if (isPositive) {
		if (integerPart > data.integerPart)
			return false;
		if (integerPart < data.integerPart)
			return true;

		if (decimalPart > data.decimalPart)
			return false;
		return true;
	}

	// 서로 -일때 (절대값이 작은게 더 큼)
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

	// 같을때
	if (*this == data)
		return false;

	// 부호 비교 (+>=-)
	if (isPositive && data < 0)
		return true;

	// 부호 비교 (->=+)
	if (not isPositive && data > 0)
		return false;

	// 서로 +일때
	if (isPositive) {
		if (integerPart >= static_cast<unsigned int>(data))
			return true;			// 정수부가 같아도 5.0와 5의 비교 같은 행위는 일어나지 않음
		return false;
	}

	// 서로 -일때
	if (integerPart >= static_cast<unsigned int>(data) * -1)
		return false;				// 정수부가 같아도 -5.0와 -5의 비교 같은 행위는 일어나지 않음
	return true;

}
bool IntDecimal::operator>(const unsigned short& data) const {
	// 같을때
	if (*this == data)
		return false;

	// *this가 -일때
	if (not isPositive)
		return false;

	// 서로 +일때
	if (integerPart >= data)
		return true;				// 정수부가 같아도 -5.0와 -5의 비교 같은 행위는 일어나지 않음
	return false;
}

bool IntDecimal::operator>(const int& data) const {
	// 같을때
	if (*this == data)
		return false;

	// 부호 비교 (+>=-)
	if (isPositive && data < 0)
		return true;

	// 부호 비교 (->=+)
	if (not isPositive && data > 0)
		return false;

	// 서로 +일때
	if (isPositive) {
		if (integerPart >= static_cast<unsigned int>(data))
			return true;			// 정수부가 같아도 -5.0와 -5의 비교 같은 행위는 일어나지 않음
		return false;
	}

	// 서로 -일때
	if (integerPart >= static_cast<unsigned int>(data) * -1)
		return false;				// 정수부가 같아도 -5.0와 -5의 비교 같은 행위는 일어나지 않음
	return true;
}

bool IntDecimal::operator>(const unsigned int& data) const {
	// 같을때
	if (*this == data)
		return false;

	// *this가 -일때
	if (not isPositive)
		return false;

	// 서로 +일때
	if (integerPart >= data)
		return true;				// 정수부가 같아도 -5.0와 -5의 비교 같은 행위는 일어나지 않음
	return false;
}

bool IntDecimal::operator>(const IntDecimal& data) const {
	// 같을때
	if (*this == data)
		return false;

	// 부호 비교 (+>=-)
	if (isPositive && not data.isPositive)
		return true;

	// 부호 비교 (->=+)
	if (not isPositive && data.isPositive)
		return false;

	// 서로 +일때 (절대값이 큰게 더 큼)
	if (isPositive) {
		if (integerPart > data.integerPart)
			return true;
		if (integerPart < data.integerPart)
			return false;

		if (decimalPart > data.decimalPart)
			return true;
		return false;
	}

	// 서로 -일때 (절대값이 작은게 더 큼)
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

	// 같을때
	if (*this == data)
		return false;

	// 부호 비교 (+<-)
	if (isPositive && data < 0)
		return false;

	// 부호 비교 (-<+)
	if (not isPositive && data > 0)
		return true;

	// 서로 +일때
	if (isPositive) {
		if (integerPart >= static_cast<unsigned int>(data))
			return false;			// 정수부가 같아도 5.0와 5의 비교 같은 행위는 일어나지 않음
		return true;
	}

	// 서로 -일때
	if (integerPart >= static_cast<unsigned int>(data) * -1)
		return true;				// 정수부가 같아도 -5.0와 -5의 비교 같은 행위는 일어나지 않음
	return false;

}
bool IntDecimal::operator< (const unsigned short& data) const {
	// 같을때
	if (*this == data)
		return false;

	// *this가 -일때
	if (not isPositive)
		return true;

	// 서로 +일때
	if (integerPart >= data)
		return false;				// 정수부가 같아도 -5.0와 -5의 비교 같은 행위는 일어나지 않음
	return true;
}

bool IntDecimal::operator< (const int& data) const {
	// 같을때
	if (*this == data)
		return false;

	// 부호 비교 (+<-)
	if (isPositive && data < 0)
		return false;

	// 부호 비교 (-<+)
	if (not isPositive && data > 0)
		return true;

	// 서로 +일때
	if (isPositive) {
		if (integerPart >= static_cast<unsigned int>(data))
			return false;			// 정수부가 같아도 -5.0와 -5의 비교 같은 행위는 일어나지 않음
		return true;
	}

	// 서로 -일때
	if (integerPart >= static_cast<unsigned int>(data) * -1)
		return true;				// 정수부가 같아도 -5.0와 -5의 비교 같은 행위는 일어나지 않음
	return false;
}

bool IntDecimal::operator< (const unsigned int& data) const {
	// 같을때
	if (*this == data)
		return false;

	// *this가 -일때
	if (not isPositive)
		return true;

	// 서로 +일때
	if (integerPart >= data)
		return false;				// 정수부가 같아도 -5.0와 -5의 비교 같은 행위는 일어나지 않음
	return true;
}

bool IntDecimal::operator<(const IntDecimal& data) const {
	// 같을때
	if (*this == data)
		return false;

	// 부호 비교 (+<-)
	if (isPositive && not data.isPositive)
		return false;

	// 부호 비교 (-<+)
	if (not isPositive && data.isPositive)
		return true;

	// 서로 +일때 (절대값이 큰게 더 큼)
	if (isPositive) {
		if (integerPart > data.integerPart)
			return false;
		if (integerPart < data.integerPart)
			return true;

		if (decimalPart > data.decimalPart)
			return false;
		return true;
	}

	// 서로 -일때 (절대값이 작은게 더 큼)
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

//(유효숫자 6자리까지 유효 / 소수점 7자리 이하 절삭)
//(사용을 권장하지 않음.)
//(단, -2147480000 이하시 -214748000로 표기 (INT_MIN == -2147483648)
//(단, +2147480000 이상시 +214748000로 표기 (INT_MAX == +2147483647)

IntDecimal& IntDecimal::operator=(float data) {
	// +2147480000 이상시 +214748000로 표기
	if (data >= 2147480000) {
		integerPart = 2147480000;
		decimalPart = 0;
		isPositive = true;
		return *this;
	}

	// -2147480000 이하시 -214748000로 표기
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

	// 양수/음수 판별해서 계산
	if (data >= 0) {
		isPositive = true;
	}
	else {
		isPositive = false;
		data *= -1.0f;
	}


	short numDigits = static_cast<short>(log10(data));

	// 절대값 10 이상 인 수

	if (numDigits > 0) {
		numDigits++;		// 자리수 표현을 위해 1 더함

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


	// 절대값 1 이상 10 미만인 수

	if (data >= 1) {
		data *= 100000;
		integerPart = static_cast<unsigned int>(data);
		decimalPart = integerPart % 100000;
		integerPart /= 100000;
		decimalPart *= 10;

		return *this;
	}

	// 절대값 1 미만인 수

	integerPart = 0;
	decimalPart = static_cast<unsigned int>((data - integerPart) * 1000000.0f);

	if (decimalPart == 0)	// 0일때 부호를 +로 바꿔줌
		isPositive = true;

	return *this;
}

//(유효숫자 6자리까지 유효 / 소수점 7자리 이하 절삭)
//(사용을 권장하지 않음.)
//(단, -2147483647 이하시 -2147483647로 표기 (INT_MIN == -2147483648)
//(단, +2147483647 이상시 +2147483647로 표기 (INT_MAX == +2147483647)
IntDecimal& IntDecimal::operator=(double data) {
	// +2147483647 이상시 +2147483647로 표기
	if (data >= 2147483647) {
		integerPart = 2147483647;
		decimalPart = 0;
		isPositive = true;
		return *this;
	}

	// -2147483647 이하시 -2147483647로 표기
	if (data <= -2147483647) {
		integerPart = -2147483647;
		decimalPart = 0;
		isPositive = false;
		return *this;
	}


	// 양수/음수 판별해서 계산
	if (data >= 0) {
		isPositive = true;
	}
	else {
		isPositive = false;
		data *= -1;
	}

	short numDigits = static_cast<short>(log10(data));

	// 절대값 10 이상 인 수

	if (numDigits > 0) {
		numDigits++;		// 자리수 표현을 위해 1 더함

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


	// 절대값 1 이상 10 미만인 수

	if (data >= 1) {
		data *= 100000;
		integerPart = static_cast<unsigned int>(data);
		decimalPart = integerPart % 100000;
		integerPart /= 100000;
		decimalPart *= 10;

		return *this;
	}

	// 절대값 1 미만인 수

	integerPart = 0;
	decimalPart = static_cast<unsigned int>((data - integerPart) * 1000000.0f);

	if (decimalPart == 0)	// 0일때 부호를 +로 바꿔줌
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
//그 외
//=====================================


// Int로 변환				(소수점 이하 절삭)
int IntDecimal::toInt() const {
	int toIntResult = integerPart;
	if (not isPositive)
		toIntResult *= -1;

	return toIntResult;
}

// UnsignedInt로 변환		(소수점 이하/부호(-) 절삭)
unsigned int IntDecimal::toUnsignedInt() const {
	unsigned int toIntResult = integerPart;
	return toIntResult;
}

// float로 변환
float IntDecimal::toFloat() const {
	float toFloatResult = integerPart + (static_cast<float>(decimalPart) * 0.000001f);
	if (not isPositive)
		toFloatResult *= -1;
	
	return toFloatResult;
}

// Double로 변환
double IntDecimal::toDouble() const {
	double toDoubleResult = integerPart + (static_cast<double>(decimalPart) * 0.000001);
	if (not isPositive)
		toDoubleResult *= -1;

	return toDoubleResult;
}

// 절대값 전달
IntDecimal IntDecimal::abc() const {
	return IntDecimal(integerPart, decimalPart, true);
}

// 정수부 전달
unsigned int IntDecimal::getIntegerPart() const {
	return integerPart;
}


// 소수부 전달
unsigned int IntDecimal::getDecimalPart() const {
	return decimalPart;
}

// 부호 전달
bool IntDecimal::getSign() const {
	return isPositive;
}

// 부호 출력
char IntDecimal::printSign() const {
	if (isPositive)
		return '+';
	else
		return '-';
}