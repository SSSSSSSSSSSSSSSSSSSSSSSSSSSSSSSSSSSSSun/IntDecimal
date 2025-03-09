#include "FixedPoint.h"

//=====================================
//생성자
//=====================================

// 0.0
FixedPoint::FixedPoint()
	: integerPart(0), decimalPart(0), isPositive(true) {}

// int로 생성				(~2147483648~2147483647)
FixedPoint::FixedPoint(const int& integer)
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
FixedPoint::FixedPoint(const unsigned int& integer)
	: integerPart(integer), decimalPart(0), isPositive(true) {
}


// float로 생성	(사용을 권장하지 않음)
// (유효숫자 6자리까지 유효 / 소수점 7자리 이하 절삭)
// (단, -2147480000 이하시 -214748000로 표기 (INT_MIN == -2147483648)
// (단, +2147480000 이상시 +214748000로 표기 (INT_MAX == +2147483647)
FixedPoint::FixedPoint(float floatNumber) {

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



// double로 생성 (사용을 권장하지 않음)
// (유효숫자 6자리까지 유효 / 소수점 7자리 이하 절삭)
// (단, -2147483647 이하시 -2147483647로 표기 (INT_MIN == -2147483648)
// (단, +2147483647 이상시 +2147483647로 표기 (INT_MAX == +2147483647)
FixedPoint::FixedPoint(double doubleNumber) {

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
// 소수부는 무조건 소수점 첫번째 자리 부터 들어감
// (ex : (3,25) -> 3.250000
FixedPoint::FixedPoint(const int& inputIntegerPart, const unsigned int& inputDecimalPart){
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

// 정수부, 소수부, 부호로 생성 (소수부 999999 초과시 0으로 계산)
// 소수부는 무조건 소수점 첫번째 자리 부터 들어감
// (ex : (3,25) -> 3.250000
FixedPoint::FixedPoint(const unsigned int& inputIntegerPart, const unsigned int& inputDecimalPart, const bool& inputIsPositive)
	: integerPart(inputIntegerPart), isPositive(inputIsPositive)
{

	if (inputDecimalPart > 999999) {
		decimalPart = 0;
		return;
	}
	int numDigits = static_cast<int>(log10(inputDecimalPart) + 1);
	decimalPart = inputDecimalPart * static_cast<unsigned int>(pow(10, 6 - numDigits));
}

// 복사생성자
FixedPoint::FixedPoint(const FixedPoint& original)
	: integerPart(original.integerPart), decimalPart(original.decimalPart), isPositive(original.isPositive) {}




//=====================================
//연산자
//=====================================

//=======================
//단항 연산자
//=======================

//============
//- (단항)
//============
FixedPoint operator-(const FixedPoint& obj) {

	return FixedPoint(obj.integerPart, obj.decimalPart, not (obj.isPositive));
}

//============
//!
//============


bool operator!(const FixedPoint& obj) {
	if (obj.integerPart)
		return true;
	if (obj.decimalPart)
		return true;
}


//============
//<<
//============

std::ostream& operator<<(std::ostream& lhs, const FixedPoint& rhs) {

	//정수일때
	if (rhs.decimalPart == 0) {
		// 양수면 부호 표시 안함
		if (rhs.isPositive) {
			lhs << rhs.integerPart << '.' << 0 << 0 << 0 << 0 << 0 << 0;
			return lhs;
		}

		lhs << rhs.printSign() << rhs.integerPart << '.' << 0 << 0 << 0 << 0 << 0 << 0;
		return lhs;
	}

	//소수일때
	// 양수면 부호 표시 안함
	if (rhs.isPositive) {
		lhs << rhs.integerPart << '.';
	}
	else {
		lhs << rhs.printSign() << rhs.integerPart << '.';
	}
	for (int i = 0;i < 6-(log10(rhs.decimalPart) + 1);i++) {
		lhs << 0;
	}
	lhs << rhs.decimalPart;
	return lhs;
}


//============
//+=
//============
FixedPoint& FixedPoint::operator+=(const int& data) {
	FixedPoint result = *this + data;
	*this = result;
	return *this;
}

FixedPoint& FixedPoint::operator+=(const unsigned int& data) {
	FixedPoint result = *this + data;
	*this = result;
	return *this;
}

FixedPoint& FixedPoint::operator+=(const FixedPoint& data) {
	FixedPoint result = *this + data;
	*this = result;
	return *this;
}

//============
//-=
//============
FixedPoint& FixedPoint::operator-=(const int& data) {
	FixedPoint result = *this - data;
	*this = result;
	return *this;
}

FixedPoint& FixedPoint::operator-=(const unsigned int& data) {
	FixedPoint result = *this - data;
	*this = result;
	return *this;
}

FixedPoint& FixedPoint::operator-=(const FixedPoint& data) {
	FixedPoint result = *this - data;
	*this = result;
	return *this;
}

//============
//*=
//============
FixedPoint& FixedPoint::operator*=(const int& data) {
	FixedPoint result = *this * data;
	*this = result;
	return *this;
}

FixedPoint& FixedPoint::operator*=(const unsigned int& data) {
	FixedPoint result = *this * data;
	*this = result;
	return *this;
}

FixedPoint& FixedPoint::operator*=(const FixedPoint& data) {
	FixedPoint result = *this * data;
	*this = result;
	return *this;
}

//============
///=
//============
FixedPoint& FixedPoint::operator/=(const int& data) {
	FixedPoint result = *this / data;
	*this = result;
	return *this;
}

FixedPoint& FixedPoint::operator/=(const unsigned int& data) {
	FixedPoint result = *this / data;
	*this = result;
	return *this;
}

FixedPoint& FixedPoint::operator/=(const FixedPoint& data) {
	FixedPoint result = *this / data;
	*this = result;
	return *this;
}

//============
//=
//============

FixedPoint& FixedPoint::operator=(const int& data) {
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

FixedPoint& FixedPoint::operator=(const unsigned int& data) {
	decimalPart = 0;
	integerPart = data;
	isPositive = true;

	return *this;
}

//(유효숫자 6자리까지 유효 / 소수점 7자리 이하 절삭)
//(사용을 권장하지 않음)
//(단, -2147480000 이하시 -214748000로 표기 (INT_MIN == -2147483648)
//(단, +2147480000 이상시 +214748000로 표기 (INT_MAX == +2147483647)

FixedPoint& FixedPoint::operator=(float data) {
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
//(사용을 권장하지 않음)
//(단, -2147483647 이하시 -2147483647로 표기 (INT_MIN == -2147483648)
//(단, +2147483647 이상시 +2147483647로 표기 (INT_MAX == +2147483647)
FixedPoint& FixedPoint::operator=(double data) {
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

FixedPoint& FixedPoint::operator=(const FixedPoint& data) {
	integerPart = data.integerPart;
	decimalPart = data.decimalPart;
	isPositive = data.isPositive;

	return *this;
}



//=======================
//이항 연산자
//=======================

//============
//+
//============


FixedPoint operator+(const FixedPoint& lhs, const int& rhs) {
	unsigned int newIntegerPart;
	unsigned int newDecimalPart;
	bool dataIsPositive;

	if (rhs >= 0)
		dataIsPositive = true;
	else
		dataIsPositive = false;

	// + + or - -
	if (lhs.isPositive == dataIsPositive) {
		if (lhs.isPositive) {
			newIntegerPart = lhs.integerPart + static_cast<unsigned int>(rhs);
			return FixedPoint(newIntegerPart, lhs.decimalPart, dataIsPositive);
		}
		else {
			newIntegerPart = lhs.integerPart + static_cast<unsigned int>(-rhs);
			return FixedPoint(newIntegerPart, lhs.decimalPart, dataIsPositive);
		}
	}

	// 합쳐서 0
	if (lhs.abs() == rhs) {
		return FixedPoint();
	}

	// + -
	if (lhs.isPositive) {
		// lhs의 절대값이 더 클때
		if (lhs.abs() > std::abs(rhs)) {
			newIntegerPart = lhs.integerPart - static_cast<unsigned int>(-rhs);
			return FixedPoint(newIntegerPart, lhs.decimalPart, lhs.isPositive);
		}
		else {
			newIntegerPart = static_cast<unsigned int>(-rhs) - lhs.integerPart;

			// 소수부 계산, // 0은 data의 소수부를 의미 (.000000)
			if (lhs.decimalPart > 0) {
				newIntegerPart--;
				newDecimalPart = 0 + 1000000 - lhs.decimalPart;
			}
			return FixedPoint(newIntegerPart, newDecimalPart, dataIsPositive);
		}
	}
	// - +
	else {
		// lhs의 절대값이 더 클때
		if (lhs.abs() > std::abs(rhs)) {
			newIntegerPart = lhs.integerPart - static_cast<unsigned int>(rhs);
			return FixedPoint(newIntegerPart, lhs.decimalPart, lhs.isPositive);
		}
		else {
			newIntegerPart = static_cast<unsigned int>(rhs) - lhs.integerPart;

			// 소수부 계산, // 0은 data의 소수부를 의미 (.000000)
			if (lhs.decimalPart > 0) {
				newIntegerPart--;
				newDecimalPart = 0 + 1000000 - lhs.decimalPart;
			}
			return FixedPoint(newIntegerPart, newDecimalPart, dataIsPositive);
		}
	}
}
FixedPoint operator+(const FixedPoint& lhs, const unsigned int& rhs) {
	unsigned int newIntegerPart;
	unsigned int newDecimalPart;
	bool dataIsPositive = true;

	// + +
	if (lhs.isPositive == dataIsPositive) {
		newIntegerPart = lhs.integerPart + rhs;
		return FixedPoint(newIntegerPart, lhs.decimalPart, dataIsPositive);
	}

	// 합쳐서 0
	if (lhs.abs() == rhs) {
		return FixedPoint();
	}
	// - +

	// lhs의 절대값이 더 클때
	if (lhs.abs() > rhs) {
		newIntegerPart = lhs.integerPart - rhs;
		return FixedPoint(newIntegerPart, lhs.decimalPart, lhs.isPositive);
	}
	else {
		newIntegerPart = rhs - lhs.integerPart;

		// 소수부 계산, // 0은 data의 소수부를 의미 (.000000)
		if (lhs.decimalPart > 0) {
			newIntegerPart--;
			newDecimalPart = 0 + 1000000 - lhs.decimalPart;
		}
		return FixedPoint(newIntegerPart, newDecimalPart, dataIsPositive);
	}

}

FixedPoint operator+(const FixedPoint& lhs, const FixedPoint& rhs) {
	unsigned int newIntegerPart;
	unsigned int newDecimalPart;

	// + + or - -
	if (lhs.isPositive == rhs.isPositive) {
		newIntegerPart = lhs.integerPart + rhs.integerPart;
		newDecimalPart = lhs.decimalPart + rhs.decimalPart;

		if (newDecimalPart >= 1000000) {
			newIntegerPart++;
			newDecimalPart -= 1000000;
		}

		return FixedPoint(newIntegerPart, newDecimalPart, lhs.isPositive);
	}

	// 합쳐서 0
	if (lhs.abs() == rhs) {
		return FixedPoint();
	}

	// 부호가 다를때
	
	if (lhs.abs() > rhs.abs()) {		// this의 절대값이 더 클때
		newIntegerPart = lhs.integerPart - rhs.integerPart;

		// 소수부 계산
		if (lhs.decimalPart >= rhs.decimalPart) {
			newDecimalPart = lhs.decimalPart - rhs.decimalPart;
		}
		else {
			newIntegerPart--;
			newDecimalPart = (lhs.decimalPart + 1000000) - rhs.decimalPart;
		}
		return FixedPoint(newIntegerPart, newDecimalPart, lhs.isPositive);
	}
	else {
		newIntegerPart = rhs.integerPart - lhs.integerPart;

		// 소수부 계산
		if (rhs.decimalPart >= lhs.decimalPart) {
			newDecimalPart = rhs.decimalPart - lhs.decimalPart;
		}
		else {
			newIntegerPart--;
			newDecimalPart = (rhs.decimalPart + 1000000) - lhs.decimalPart;
		}

		return FixedPoint(newIntegerPart, newDecimalPart, rhs.isPositive);

	}



}

FixedPoint operator+(const int& lhs, const FixedPoint& rhs) {
	return rhs + lhs;
}

FixedPoint operator+(const unsigned int& lhs, const FixedPoint& rhs) {
	return rhs + lhs;
}

//============
//-
//============
FixedPoint operator-(const FixedPoint& lhs, const int& rhs) {
	return lhs + (-rhs);
}
FixedPoint operator-(const FixedPoint& lhs, const unsigned int& rhs) {
	int signedRhs = static_cast<int>(rhs);
	return lhs + (-signedRhs);
}
FixedPoint operator-(const FixedPoint& lhs, const FixedPoint& rhs){
	return lhs+( - rhs);
}
FixedPoint operator-( const int& lhs, const FixedPoint& rhs) {
	return (-rhs)+lhs;
}
FixedPoint operator-(const unsigned int& lhs, const FixedPoint& rhs) {
	int signedLhs = static_cast<int>(lhs);
	return (-rhs)+signedLhs;
}
//============
//*
//============

// 정수부 오버플로우시(>INT_MAX*2+1) INT_MIN-0.999999 리턴
FixedPoint operator*(const FixedPoint& lhs, const int& rhs) {
	// 0
	if (lhs == 0 || rhs == 0)
		return FixedPoint();

	bool dataIsPositive;

	if (rhs >= 0)
		dataIsPositive = true;
	else
		dataIsPositive = false;

	unsigned int carry = 0;
	unsigned int newDecimalPart = 0;

	// 소수부가 0이 아닐때만 작동함
	if (lhs.decimalPart) {

		unsigned int decimalDigits[6]{ 0,0,0,0,0,0 };
		for (int i = 0;i < 6;i++) {
			decimalDigits[i] = lhs.decimalPart % static_cast<int>(pow(10, 6 - i)) / static_cast<int>(pow(10, 6 - i - 1));

			// 오버플로우 검사
			if (decimalDigits[i] > (INT_MAX * 2u + 1u) / rhs) {
				return FixedPoint(INT_MAX * 2u + 1u, 999999, false);
			}

			// 자리수가 0이 아닐때만 작동함
			if (decimalDigits[i]) {
				decimalDigits[i] *= std::abs(rhs);

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

	// 정수부가 0이 아닐때만 작동함
	if (lhs.integerPart) {
		// 오버플로우 검사
		if (lhs.integerPart > (INT_MAX * 2u + 1u - carry) / std::abs(rhs)) {
			return FixedPoint(INT_MAX * 2u + 1u, 999999, false);
		}
		newIntegerPart = lhs.integerPart * std::abs(rhs);


	}

	newIntegerPart += carry;

	return FixedPoint(newIntegerPart, newDecimalPart, not (lhs.isPositive ^ dataIsPositive));
}

// 정수부 오버플로우시(>INT_MAX*2+1) INT_MIN-0.999999 리턴
FixedPoint operator*(const FixedPoint& lhs, const unsigned int& rhs) {
	// 0
	if (lhs == 0 || rhs == 0)
		return FixedPoint();

	unsigned int carry = 0;
	unsigned int newDecimalPart = 0;

	// 소수부가 0이 아닐때만 작동함
	if (lhs.decimalPart) {
		unsigned int decimalDigits[6]{ 0,0,0,0,0,0 };
		for (int i = 0;i < 6;i++) {
			decimalDigits[i] = lhs.decimalPart % static_cast<int>(pow(10, 6 - i)) / static_cast<int>(pow(10, 6 - i - 1));

			// 오버플로우 검사
			if (decimalDigits[i] > (INT_MAX * 2u + 1u) / rhs) {
				return FixedPoint(INT_MAX * 2u + 1u, 999999, false);
			}

			// 자리수가 0이 아닐때만 작동함
			if (decimalDigits[i]) {
				decimalDigits[i] *= rhs;

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

	// 정수부가 0이 아닐때만 작동함
	if (lhs.integerPart) {
		// 오버플로우 검사
		if (lhs.integerPart > (INT_MAX * 2u + 1u - carry) / rhs) {
			return FixedPoint(INT_MAX * 2u + 1u, 999999, false);
		}
		newIntegerPart = lhs.integerPart * rhs;


	}

	newIntegerPart += carry;

	return FixedPoint(newIntegerPart, newDecimalPart, lhs.isPositive);

}

// 정수부 오버플로우시(>INT_MAX*2+1) INT_MIN-0.999999 리턴
// 소수점 7자리에서 반올림
FixedPoint operator*(const FixedPoint& lhs, const FixedPoint& rhs) {

	// 0
	if (lhs == 0 || rhs == 0)
		return FixedPoint();

//A.B * C.D = A*C + A*0.D + 0.B*C + 0.B*0.D
	FixedPoint result = FixedPoint();

	// 0.B*0.D
	unsigned long long int productOfDecimalPart = lhs.decimalPart;
	productOfDecimalPart *= rhs.decimalPart;
	result.setDecimalPart(static_cast<int>(productOfDecimalPart / 1000000));
	
	// 반올림
	productOfDecimalPart %= 1000000;
	productOfDecimalPart /= 100000;

	if (productOfDecimalPart >= 5)
		result.setDecimalPart(result.getDecimalPart() + 1);


	// A*0.D
	FixedPoint D(0, rhs.decimalPart, true);
	result += lhs.integerPart * D;
	

	// 0.B*C
	FixedPoint B(0, lhs.decimalPart, true);
	result += B * rhs.integerPart;

	// A*C
	// 
	// 정수부가 둘다 0이 아닐때만 작동함
	if (lhs.integerPart || rhs.integerPart) {
		// 오버플로우 검사
		if (lhs.integerPart > (INT_MAX * 2u + 1u - result.integerPart) / rhs.integerPart) {
			return FixedPoint(INT_MAX * 2u + 1u, 999999, false);
		}
		result += lhs.integerPart * rhs.integerPart;
	}

	// 부호 책정
	result.isPositive = not (lhs.isPositive ^ rhs.isPositive);

	return result;
}

FixedPoint operator*(const int& lhs, const FixedPoint& rhs) {
	return rhs * lhs;
}

FixedPoint operator*(const unsigned int& lhs, const FixedPoint& rhs) {
	return rhs * lhs;
}

//============
// /
//============

// 0으로 나눌려 시도시 INT_MIN-0.999999 리턴
// 소수점 7자리에서 반올림
FixedPoint operator/(const FixedPoint &lhs, const int& rhs){

	// /0
	if (rhs == 0) {
		return FixedPoint(INT_MAX * 2u + 1u, 999999, false);
	}

	bool dataIsPositive;
	unsigned int unsignedRhs = abs(rhs);
	if (rhs > 0)
		dataIsPositive = true;
	else
		dataIsPositive = false;

	FixedPoint result = lhs;

	// 정수부
	result.integerPart = lhs.integerPart/unsignedRhs;

	// 소수부
	unsigned long long int resultDecimalPart = (lhs.integerPart % unsignedRhs);
	resultDecimalPart *= 1000000;


	resultDecimalPart += lhs.decimalPart;
	result.decimalPart = static_cast<unsigned int>(resultDecimalPart/unsignedRhs);
		// 반올림
	resultDecimalPart %= unsignedRhs;
	if (resultDecimalPart*2 > unsignedRhs)
		result.decimalPart++;

	// 부호 책정
	result.isPositive = not (lhs.isPositive ^ dataIsPositive);
	return result;
}

// 0으로 나눌려 시도시 INT_MIN-0.999999 리턴
// 소수점 7자리에서 반올림
FixedPoint operator/(const FixedPoint &lhs, const unsigned int& rhs){
	// /0
	if (rhs == 0) {
		return FixedPoint(INT_MAX * 2u + 1u, 999999, false);
	}

	FixedPoint result = lhs;

	// 정수부
	result.integerPart = lhs.integerPart / rhs;

	// 소수부
	unsigned long long int resultDecimalPart = (lhs.integerPart % rhs);
	resultDecimalPart *= 1000000;
	resultDecimalPart += lhs.decimalPart;
	result.decimalPart = static_cast<unsigned int>(resultDecimalPart / rhs);

	// 반올림
	if ((resultDecimalPart % rhs) * 2 > rhs) {
		result.decimalPart++;
	}

	// 부호 책정
	result.isPositive = lhs.isPositive;
	return result;
}

// 0으로 나눌려 시도시 INT_MIN-0.999999 리턴
// 소수점 7자리에서 반올림
FixedPoint operator/(const FixedPoint& lhs, const FixedPoint& rhs) {

	// /0
	if (rhs == 0) {
		return FixedPoint(INT_MAX * 2u + 1u, 999999, false);
	}

	// rhs가 정수인 경우
	if (rhs.decimalPart == 0)
		return lhs / rhs.integerPart;

	unsigned long long int longlongLhs = lhs.integerPart;
	unsigned long long int longlongRhs = rhs.integerPart;

	longlongLhs *= 1000000; longlongRhs *= 1000000;
	longlongLhs += lhs.getDecimalPart(); longlongRhs += rhs.getDecimalPart();

	FixedPoint result = FixedPoint();

	//정수부
	result.integerPart = static_cast<unsigned int>(longlongLhs / longlongRhs);

	//소수부
	longlongLhs %= longlongRhs;
	
	for (int i = 0; i < 6;i++) {
		longlongLhs *= 10;
		result.decimalPart *= 10;
		result.decimalPart += static_cast<unsigned int>(longlongLhs / longlongRhs);
		longlongLhs %= longlongRhs;
	}

	// 반올림
	std::cout << longlongLhs;
	if (longlongLhs >= 500000)
		result.decimalPart++;

	// 부호 책정
	result.isPositive = not (lhs.isPositive ^ rhs.isPositive);

	return result;
}


// 0으로 나눌려 시도시 INT_MIN-0.999999 리턴
// 소수점 7자리에서 반올림
FixedPoint operator/(const int &lhs, const FixedPoint& rhs){
	// /0
	if (rhs == 0) {
		return FixedPoint(INT_MAX * 2u + 1u, 999999, false);
	}

	FixedPoint fixedpointLhs = lhs;
	// rhs가 정수인 경우
	if (rhs.decimalPart == 0)
		return lhs / rhs.integerPart;


	return lhs / rhs;
}

// 0으로 나눌려 시도시 INT_MIN-0.999999 리턴
// 소수점 7자리에서 반올림
FixedPoint operator/(const unsigned int&lhs, const FixedPoint& rhs){
	// /0
	if (rhs == 0) {
		return FixedPoint(INT_MAX * 2u + 1u, 999999, false);
	}

	FixedPoint fixedpointLhs = lhs;
	// rhs가 정수인 경우
	if (rhs.decimalPart == 0)
		return lhs / rhs.integerPart;


	return lhs / rhs;
}


//============
//==
//============

bool operator==(const FixedPoint& lhs, const int& rhs) {
	if (lhs.decimalPart)
		return false;

	if (lhs.isPositive && rhs < 0)
		return false;

	if (not lhs.isPositive && rhs > 0)
		return false;

	if (rhs == lhs.integerPart)
		return true;
	return false;
}

bool operator==(const FixedPoint& lhs, const unsigned int& rhs) {
	if (lhs.decimalPart)
		return false;

	if (not lhs.isPositive && rhs > 0)
		return false;

	if (rhs == lhs.integerPart)
		return true;
	return false;
}
bool operator==(const FixedPoint& lhs, const FixedPoint& rhs) {
	if (not (lhs.integerPart == rhs.integerPart))
		return false;

	if (not (lhs.decimalPart == rhs.decimalPart))
		return false;

	if (not (lhs.isPositive == rhs.isPositive)) {
		if (lhs.integerPart == 0 && lhs.decimalPart == 0) {
			return true;
		}
		return false;
	}

	return true;
}

bool operator==(const int& lhs, const FixedPoint& rhs) {
	return rhs == lhs;
}
bool operator==(const unsigned int& lhs, const FixedPoint& rhs) {
	return rhs == lhs;
}

//============
// !=
//============

bool operator!=(const FixedPoint& lhs, const int& rhs) {
	return not (lhs == rhs);
}
bool operator!=(const FixedPoint& lhs, const unsigned int& rhs) {
	return not (lhs == rhs);
}
bool operator!=(const FixedPoint& lhs, const FixedPoint& rhs) {
	return not (lhs == rhs);
}
bool operator!=(const int& lhs, const FixedPoint& rhs) {
	return not (lhs == rhs);
}
bool operator!=(const unsigned int& lhs, const FixedPoint& rhs) {
	return not (lhs == rhs);
}

//============
//>
//============

bool operator>(const FixedPoint& lhs, const int& rhs) {
	// 같을때
	if (lhs == rhs)
		return false;

	// 부호 비교 (+>-)
	if (lhs.isPositive && rhs < 0)
		return true;

	// 부호 비교 (->+)
	if (not lhs.isPositive && rhs > 0)
		return false;

	// 서로 +일때
	if (lhs.isPositive) {
		if (lhs.integerPart >= static_cast<unsigned int>(rhs))
			return true;			// 정수부가 같아도 -5.0와 -5의 비교 같은 행위는 일어나지 않음
		return false;
	}

	// 서로 -일때
	if (lhs.integerPart >= static_cast<unsigned int>(rhs) * -1)
		return false;				// 정수부가 같아도 -5.0와 -5의 비교 같은 행위는 일어나지 않음
	return true;
}

bool operator>(const FixedPoint& lhs, const unsigned int& rhs) {
	// 같을때
	if (lhs == rhs)
		return false;

	// lhs가 -일때
	if (not lhs.isPositive)
		return false;

	// 서로 +일때
	if (lhs.integerPart >= rhs)
		return true;				// 정수부가 같아도 -5.0와 -5의 비교 같은 행위는 일어나지 않음
	return false;
}

bool operator>(const FixedPoint& lhs, const FixedPoint& rhs) {
	// 같을때
	if (lhs == rhs)
		return false;

	// 부호 비교 (+>-)
	if (lhs.isPositive && not rhs.isPositive)
		return true;

	// 부호 비교 (->+)
	if (not lhs.isPositive && rhs.isPositive)
		return false;

	// 서로 +일때 (절대값이 큰게 더 큼)
	if (lhs.isPositive) {
		if (lhs.integerPart > rhs.integerPart)
			return true;
		if (lhs.integerPart < rhs.integerPart)
			return false;

		if (lhs.decimalPart > rhs.decimalPart)
			return true;
		return false;
	}

	// 서로 -일때 (절대값이 작은게 더 큼)
	if (lhs.integerPart > rhs.integerPart)
		return false;
	if (lhs.integerPart < rhs.integerPart)
		return true;

	if (lhs.decimalPart > rhs.decimalPart)
		return false;
	return true;
}

bool operator>(const int& lhs, const FixedPoint& rhs) {
	return rhs < lhs;
}
bool operator>(const unsigned int& lhs, const FixedPoint& rhs) {
	return rhs < lhs;
}

//============
//<
//============

bool operator<(const FixedPoint& lhs, const int& rhs) {
	// 같을때
	if (lhs == rhs)
		return false;

	// 부호 비교 (+<-)
	if (lhs.isPositive && rhs < 0)
		return false;

	// 부호 비교 (-<+)
	if (not lhs.isPositive && rhs > 0)
		return true;

	// 서로 +일때
	if (lhs.isPositive) {
		if (lhs.integerPart >= static_cast<unsigned int>(rhs))
			return false;			// 정수부가 같아도 -5.0와 -5의 비교 같은 행위는 일어나지 않음
		return true;
	}

	// 서로 -일때
	if (lhs.integerPart >= static_cast<unsigned int>(rhs) * -1)
		return true;				// 정수부가 같아도 -5.0와 -5의 비교 같은 행위는 일어나지 않음
	return false;
}

bool operator<(const FixedPoint& lhs, const unsigned int& rhs) {
	// 같을때
	if (lhs == rhs)
		return false;

	// lhs가 -일때
	if (not lhs.isPositive)
		return true;

	// 서로 +일때
	if (lhs.integerPart >= rhs)
		return false;				// 정수부가 같아도 -5.0와 -5의 비교 같은 행위는 일어나지 않음
	return true;
}


bool operator<(const FixedPoint& lhs, const FixedPoint& rhs) {
	// 같을때
	if (lhs == rhs)
		return false;

	// 부호 비교 (+<-)
	if (lhs.isPositive && not rhs.isPositive)
		return false;

	// 부호 비교 (-<+)
	if (not lhs.isPositive && rhs.isPositive)
		return true;

	// 서로 +일때 (절대값이 큰게 더 큼)
	if (lhs.isPositive) {
		if (lhs.integerPart > rhs.integerPart)
			return false;
		if (lhs.integerPart < rhs.integerPart)
			return true;

		if (lhs.decimalPart > rhs.decimalPart)
			return false;
		return true;
	}

	// 서로 -일때 (절대값이 작은게 더 큼)
	if (lhs.integerPart > rhs.integerPart)
		return true;
	if (lhs.integerPart < rhs.integerPart)
		return false;

	if (lhs.decimalPart > rhs.decimalPart)
		return true;
	return false;
}

bool operator<(const int& lhs, const FixedPoint& rhs) {
	return rhs > lhs;
}
bool operator<(const unsigned int& lhs, const FixedPoint& rhs) {
	return rhs > lhs;
}

//============
//>=
//============

bool operator>=(const FixedPoint& lhs, const int& rhs){
	if (lhs == rhs)
		return true;

	return lhs > rhs;
}
bool operator>=(const FixedPoint& lhs, const unsigned int& rhs) {
	if (lhs == rhs)
		return true;

	return lhs > rhs;
}
bool operator>=(const FixedPoint& lhs, const FixedPoint& rhs) {
	if (lhs == rhs)
		return true;

	return lhs > rhs;
}
bool operator>=(const int& lhs, const FixedPoint& rhs) {
	if (lhs == rhs)
		return true;

	return lhs > rhs;
}
bool operator>=(const unsigned int& lhs, const FixedPoint& rhs) {
	if (lhs == rhs)
		return true;

	return lhs > rhs;
}

//============
//<=
//============

bool operator<=(const FixedPoint& lhs, const int& rhs) {
	if (lhs == rhs)
		return true;

	return lhs < rhs;
}
bool operator<=(const FixedPoint& lhs, const unsigned int& rhs) {
	if (lhs == rhs)
		return true;

	return lhs < rhs;
}
bool operator<=(const FixedPoint& lhs, const FixedPoint& rhs) {
	if (lhs == rhs)
		return true;

	return lhs < rhs;
}
bool operator<=(const int& lhs, const FixedPoint& rhs) {
	if (lhs == rhs)
		return true;

	return lhs < rhs;
}
bool operator<=(const unsigned int& lhs, const FixedPoint& rhs) {
	if (lhs == rhs)
		return true;

	return lhs < rhs;

}


//=====================================
//그 외
//=====================================


// Int로 변환				(소수점 이하 절삭)
int FixedPoint::toInt() const {
	int toIntResult = integerPart;
	if (not isPositive)
		toIntResult *= -1;

	return toIntResult;
}

// UnsignedInt로 변환		(소수점 이하 절삭)
unsigned int FixedPoint::toUnsignedInt() const {
	return this->toInt();
}

// float로 변환
float FixedPoint::toFloat() const {
	float toFloatResult = integerPart + (static_cast<float>(decimalPart) * 0.000001f);
	if (not isPositive)
		toFloatResult *= -1;
	
	return toFloatResult;
}

// Double로 변환
double FixedPoint::toDouble() const {
	double toDoubleResult = integerPart + (static_cast<double>(decimalPart) * 0.000001);
	if (not isPositive)
		toDoubleResult *= -1;

	return toDoubleResult;
}

// 절대값 전달
FixedPoint FixedPoint::abs() const {
	return FixedPoint(integerPart, decimalPart, true);
}

// 정수부 전달
unsigned int FixedPoint::getIntegerPart() const {
	return integerPart;
}


// 소수부 전달
unsigned int FixedPoint::getDecimalPart() const {
	return decimalPart;
}

// 부호 전달
bool FixedPoint::getSign() const {
	return isPositive;
}

// 부호 출력
char FixedPoint::printSign() const {
	if (isPositive)
		return '+';
	else
		return '-';
}

// 정수부 조작
void FixedPoint::setIntegerPart(unsigned int data) {
	integerPart = data;
	return;
}

// 소수부 조작
// data가 999999 초과일시 아무일도 일어나지 않음
void FixedPoint::setDecimalPart(unsigned int data) {
	if (data > 999999)
		return;

	decimalPart = data;
	return;
}

// 부호 조작
void FixedPoint::setIsPositive(bool data) {
	isPositive = data;
	return;
}