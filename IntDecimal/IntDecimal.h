#pragma once
class IntDecimal
{
private:
	unsigned int integerPart;		// 정수부
	unsigned int decimalPart;		// 소수부 (0~999999)
	bool isPositive;				// 부호, 0의 경우는 상관 안하지만 true로 두는 것을 원칙으로 함
public:

	//=====================================
	//생성자
	//=====================================

	IntDecimal();						// 0.0

	IntDecimal(const short&);			// short로 생성				(~32768~32767)
	IntDecimal(const unsigned short&);	// unsigned short로 생성	(0~65535)
	IntDecimal(const int&);				// int로 생성				(~2147483648~2147483647)
	IntDecimal(const unsigned int&);	// unsigned int로 생성		(0~4294967295)
	IntDecimal(const int&, const unsigned int&);	// 정수부, 소수부로 생성 (소수부 999999 초과시 0으로 계산)
	IntDecimal(const unsigned int&, const unsigned int&, const bool&);
	// 정수부, 소수부, 부호로 생성 (소수부 999999 초과시 0으로 계산)
	
	IntDecimal(float);
	// float로 생성				(유효숫자 6자리까지 유효 / 소수점 7자리 이하 절삭)
	//							(권장하지 않음)
	//							(단, -2147480000 이하시 -214748000로 표기 (INT_MIN == -2147483648)
	//							(단, +2147480000 이상시 +214748000로 표기 (INT_MAX == +2147483647)
	
	IntDecimal(double);
	// double로 생성			(유효숫자 6자리까지 유효 / 소수점 7자리 이하 절삭)
	//							(권장하지 않음)
	//							(단, -2147483647 이하시 -2147483647로 표기 (INT_MIN == -2147483648)
	//							(단, +2147483647 이상시 +2147483647로 표기 (INT_MAX == +2147483647)

	IntDecimal(const IntDecimal&);		// 복사생성

	//=====================================
	//연산자, float, double과의 연산자 사용 안함 (정확도 낮음)
	//=====================================

	IntDecimal operator-() const;

	IntDecimal operator+(const short&) const;
	IntDecimal operator+(const unsigned short&) const;
	IntDecimal operator+(const int&) const;
	IntDecimal operator+(const unsigned int&) const;
	IntDecimal operator+(const IntDecimal&) const;

	IntDecimal operator-(const short&) const;
	IntDecimal operator-(const unsigned short&) const;
	IntDecimal operator-(const int&) const;
	IntDecimal operator-(const unsigned int&) const;
	IntDecimal operator-(const IntDecimal&) const;

	// 정수부나 지수부 오버플로우시 INT_MIN-0.999999 리턴
	IntDecimal operator*(const short&) const;
	IntDecimal operator*(const unsigned short&) const;
	IntDecimal operator*(const int&) const;
	IntDecimal operator*(const unsigned int&) const;
	IntDecimal operator*(const IntDecimal&) const;

	IntDecimal operator/(const short&) const;
	IntDecimal operator/(const unsigned short&) const;
	IntDecimal operator/(const int&) const;
	IntDecimal operator/(const unsigned int&) const;
	IntDecimal operator/(const IntDecimal&) const;

	IntDecimal& operator+=(const short&) const;
	IntDecimal& operator+=(const unsigned short&) const;
	IntDecimal& operator+=(const int&) const;
	IntDecimal& operator+=(const unsigned int&) const;
	IntDecimal& operator+=(const IntDecimal&) const;

	IntDecimal& operator-=(const short&) const;
	IntDecimal& operator-=(const unsigned short&) const;
	IntDecimal& operator-=(const int&) const;
	IntDecimal& operator-=(const unsigned int&) const;
	IntDecimal& operator-=(const IntDecimal&) const;

	IntDecimal& operator*=(const short&) const;
	IntDecimal& operator*=(const unsigned short&) const;
	IntDecimal& operator*=(const int&) const;
	IntDecimal& operator*=(const unsigned int&) const;
	IntDecimal& operator*=(const IntDecimal&) const;

	IntDecimal& operator/=(const short&) const;
	IntDecimal& operator/=(const unsigned short&) const;
	IntDecimal& operator/=(const int&) const;
	IntDecimal& operator/=(const unsigned int&) const;
	IntDecimal& operator/=(const IntDecimal&) const;

	bool operator==(const short&) const;
	bool operator==(const unsigned short&) const;
	bool operator==(const int&) const;
	bool operator==(const unsigned int&) const;
	bool operator==(const IntDecimal&) const;

	bool operator>=(const short&) const;
	bool operator>=(const unsigned short&) const;
	bool operator>=(const int&) const;
	bool operator>=(const unsigned int&) const;
	bool operator>=(const IntDecimal&) const;

	bool operator<=(const short&) const;
	bool operator<=(const unsigned short&) const;
	bool operator<=(const int&) const;
	bool operator<=(const unsigned int&) const;
	bool operator<=(const IntDecimal&) const;

	bool operator>(const short&) const;
	bool operator>(const unsigned short&) const;
	bool operator>(const int&) const;
	bool operator>(const unsigned int&) const;
	bool operator>(const IntDecimal&) const;

	bool operator<(const short&) const;
	bool operator<(const unsigned short&) const;
	bool operator<(const int&) const;
	bool operator<(const unsigned int&) const;
	bool operator<(const IntDecimal&) const;

	IntDecimal& operator=(const short&);
	IntDecimal& operator=(const unsigned short&);
	IntDecimal& operator=(const int&);
	IntDecimal& operator=(const unsigned int&);

	IntDecimal& operator=(float);
	//(유효숫자 6자리까지 유효 / 소수점 7자리 이하 절삭)
	//(권장하지 않음)
	//(단, -2147480000 이하시 -214748000로 표기 (INT_MIN == -2147483648)
	//(단, +2147480000 이상시 +214748000로 표기 (INT_MAX == +2147483647)

	IntDecimal& operator=(double);
	//(유효숫자 6자리까지 유효 / 소수점 7자리 이하 절삭)
	//(권장하지 않음)
	//(단, -2147483647 이하시 -2147483647로 표기 (INT_MIN == -2147483648)
	//(단, +2147483647 이상시 +2147483647로 표기 (INT_MAX == +2147483647)

	IntDecimal& operator=(const IntDecimal&);

	bool operator!() const;

	//=====================================
	//그 외
	//=====================================

	int toInt()  const;						// Int로 변환			(소수점 이하 절삭)
	unsigned int toUnsignedInt() const;		// UnsignedInt로 변환	(소수점 이하/부호(-) 절삭)
	float toFloat() const;					// float로 변환
	double toDouble() const;				// Double로 변환

	IntDecimal abc() const;					// 절대값 전달

	unsigned int getIntegerPart() const; 	// 정수부 전달
	unsigned int getDecimalPart() const; 	// 소수부 전달
	bool getSign() const;					// 부호 전달
	char printSign() const			;		// 부호 출력


	
};

