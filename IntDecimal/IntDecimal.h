#pragma once
class IntDecimal
{
private:
	unsigned int integerPart;		// 정수부
	int decimalPart;				// 소수부 (0~999999)
	bool isPositive;				// 부호, 0의 경우는 상관 안하지만 true로 두는 것을 원칙으로 함
public:

	IntDecimal();						// 0.0

	IntDecimal(const short&);			// short로 생성				(~32768~32767)
	IntDecimal(const unsigned short&);	// unsigned short로 생성	(0~65535)
	IntDecimal(const int&);				// int로 생성				(~2147483648~2147483647)

	IntDecimal(float);
	// float로 생성				(유효숫자 6자리까지 유효 / 소수점 7자리 이하 절삭)
	//							(단, -2147480000 이하시 -214748000로 표기 (INT_MIN == -2147483648)
	//							(단, +2147480000 이상시 +214748000로 표기 (INT_MAX == +2147483647)
	
	IntDecimal(double);
	// double로 생성			(소수점 7자리 이하 절삭)
	//							(단, -2147483647 이하시 -2147483647로 표기 (INT_MIN == -2147483648)
	//							(단, +2147483647 이상시 +2147483647로 표기 (INT_MAX == +2147483647)

	IntDecimal(const IntDecimal&);		// 복사생성


	int toInt();						// Int로 변환			(소수점 이하 절삭)
	unsigned int toUnsignedInt();		// UnsignedInt로 변환	(소수점 이하/부호(-) 절삭)
	float toFloat();					// float로 변환
	double toDouble();					// Double로 변환


	int getIntegerPart(); 	// 정수부 전달
	int getDecimalPart(); 	// 소수부 전달
	bool getSign();			// 부호 전달
	char printSign();		// 부호 출력
};

