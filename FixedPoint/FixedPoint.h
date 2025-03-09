#pragma once
#include <cmath>
#include <iostream>

class FixedPoint
{
private:
	unsigned int integerPart;		// 정수부
	unsigned int decimalPart;		// 소수부 (0~999999)
	bool isPositive;				// 부호, 0의 경우는 상관 안하지만 true로 두는 것을 원칙으로 함
public:

	//=====================================
	//생성자
	//=====================================

	FixedPoint();						// 0.0

	FixedPoint(const int&);				// int로 생성				(~2147483648~2147483647)
	FixedPoint(const unsigned int&);	// unsigned int로 생성		(0~4294967295)
	FixedPoint(const int&, const unsigned int&);	// 정수부, 소수부로 생성 (소수부 999999 초과시 0으로 계산)
	FixedPoint(const unsigned int&, const unsigned int&, const bool&);
	// 정수부, 소수부, 부호로 생성 (소수부 999999 초과시 0으로 계산)
	
	FixedPoint(float);
	// float로 생성				(유효숫자 6자리까지 유효 / 소수점 7자리 이하 절삭)
	//							(권장하지 않음)
	//							(단, -2147480000 이하시 -214748000로 표기 (INT_MIN == -2147483648)
	//							(단, +2147480000 이상시 +214748000로 표기 (INT_MAX == +2147483647)
	
	FixedPoint(double);
	// double로 생성			(유효숫자 6자리까지 유효 / 소수점 7자리 이하 절삭)
	//							(권장하지 않음)
	//							(단, -2147483647 이하시 -2147483647로 표기 (INT_MIN == -2147483648)
	//							(단, +2147483647 이상시 +2147483647로 표기 (INT_MAX == +2147483647)

	FixedPoint(const FixedPoint&);		// 복사생성

	//=====================================
	//연산자, float, double과의 산술/비교 연산자 사용 안함 (정확도 낮음)
	//=====================================

	//============================
	//단항 연산자
	//============================

	friend FixedPoint operator-(const FixedPoint&);
	friend bool operator!(const FixedPoint&);
	friend std::ostream& operator<<(std::ostream&, const FixedPoint&);

	FixedPoint& operator+=(const int&);
	FixedPoint& operator+=(const unsigned int&);
	FixedPoint& operator+=(const FixedPoint&);

	FixedPoint& operator-=(const int&);
	FixedPoint& operator-=(const unsigned int&);
	FixedPoint& operator-=(const FixedPoint&);

	FixedPoint& operator*=(const int&);
	FixedPoint& operator*=(const unsigned int&);
	FixedPoint& operator*=(const FixedPoint&);

	FixedPoint& operator/=(const int&);
	FixedPoint& operator/=(const unsigned int&);
	FixedPoint& operator/=(const FixedPoint&);

	FixedPoint& operator=(const int&);
	FixedPoint& operator=(const unsigned int&);

	FixedPoint& operator=(float);
	//(유효숫자 6자리까지 유효 / 소수점 7자리 이하 절삭)
	//(권장하지 않음)
	//(단, -2147480000 이하시 -214748000로 표기 (INT_MIN == -2147483648)
	//(단, +2147480000 이상시 +214748000로 표기 (INT_MAX == +2147483647)

	FixedPoint& operator=(double);
	//(유효숫자 6자리까지 유효 / 소수점 7자리 이하 절삭)
	//(권장하지 않음)
	//(단, -2147483647 이하시 -2147483647로 표기 (INT_MIN == -2147483648)
	//(단, +2147483647 이상시 +2147483647로 표기 (INT_MAX == +2147483647)

	FixedPoint& operator=(const FixedPoint&);

	//============================
	//이항 연산자
	//============================

	friend FixedPoint operator+(const FixedPoint&, const int&);
	friend FixedPoint operator+(const FixedPoint&, const unsigned int&);
	friend FixedPoint operator+(const FixedPoint&, const FixedPoint&);
	friend FixedPoint operator+(const int&, const FixedPoint&);
	friend FixedPoint operator+(const unsigned int&, const FixedPoint&);

	friend FixedPoint operator-(const FixedPoint&, const int&);
	friend FixedPoint operator-(const FixedPoint&, const unsigned int&);
	friend FixedPoint operator-(const FixedPoint&, const FixedPoint&);
	friend FixedPoint operator-(const int&, const FixedPoint&);
	friend FixedPoint operator-(const unsigned int&, const FixedPoint&);

	// 정수부나 지수부 오버플로우시 INT_MIN-0.999999 리턴
	friend FixedPoint operator*(const FixedPoint&, const int&);
	friend FixedPoint operator*(const FixedPoint&, const unsigned int&);
	friend FixedPoint operator*(const FixedPoint&, const FixedPoint&);
	friend FixedPoint operator*(const int&, const FixedPoint&);
	friend FixedPoint operator*(const unsigned int&, const FixedPoint&);

	friend FixedPoint operator/(const FixedPoint&, const int&);
	friend FixedPoint operator/(const FixedPoint&, const unsigned int&);
	friend FixedPoint operator/(const FixedPoint&, const FixedPoint&);
	friend FixedPoint operator/(const int&, const FixedPoint&);
	friend FixedPoint operator/(const unsigned int&, const FixedPoint&);

	friend bool operator==(const FixedPoint&, const int&);
	friend bool operator==(const FixedPoint&, const unsigned int&);
	friend bool operator==(const FixedPoint&, const FixedPoint&);
	friend bool operator==(const int&, const FixedPoint&);
	friend bool operator==(const unsigned int&, const FixedPoint&);

	friend bool operator!=(const FixedPoint&, const int&);
	friend bool operator!=(const FixedPoint&, const unsigned int&);
	friend bool operator!=(const FixedPoint&, const FixedPoint&);
	friend bool operator!=(const int&, const FixedPoint&);
	friend bool operator!=(const unsigned int&, const FixedPoint&);

	friend bool operator>(const FixedPoint&, const int&);
	friend bool operator>(const FixedPoint&, const unsigned int&);
	friend bool operator>(const FixedPoint&, const FixedPoint&);
	friend bool operator>(const int&, const FixedPoint&);
	friend bool operator>(const unsigned int&, const FixedPoint&);

	friend bool operator<(const FixedPoint&, const int&);
	friend bool operator<(const FixedPoint&, const unsigned int&);
	friend bool operator<(const FixedPoint&, const FixedPoint&);
	friend bool operator<(const int&, const FixedPoint&);
	friend bool operator<(const unsigned int&, const FixedPoint&);

	friend bool operator>=(const FixedPoint&, const int&);
	friend bool operator>=(const FixedPoint&, const unsigned int&);
	friend bool operator>=(const FixedPoint&, const FixedPoint&);
	friend bool operator>=(const int&, const FixedPoint&);
	friend bool operator>=(const unsigned int&, const FixedPoint&);

	friend bool operator<=(const FixedPoint&, const int&);
	friend bool operator<=(const FixedPoint&, const unsigned int&);
	friend bool operator<=(const FixedPoint&, const FixedPoint&);
	friend bool operator<=(const int&, const FixedPoint&);
	friend bool operator<=(const unsigned int&, const FixedPoint&);

	//=====================================
	//그 외
	//=====================================

	int toInt()  const;						// Int로 변환			(소수점 이하 절삭)
	unsigned int toUnsignedInt() const;		// UnsignedInt로 변환	(소수점 이하/부호(-) 절삭)
	float toFloat() const;					// float로 변환
	double toDouble() const;				// Double로 변환

	FixedPoint abs() const;					// 절대값 전달

	unsigned int getIntegerPart() const; 	// 정수부 전달
	unsigned int getDecimalPart() const; 	// 소수부 전달
	bool getSign() const;					// 부호 전달
	char printSign() const			;		// 부호 출력

	void setIntegerPart(unsigned int);		// 정수부 조작
	void setDecimalPart(unsigned int);		// 소수부 조작
	void setIsPositive(bool);				// 부호 조작
	
};