#pragma once
class IntDecimal
{
private:
	int integerPart;		// 정수부
	int decimalPart;		// 소수부 (0~999999)

public:

	IntDecimal();						// 0.0

	IntDecimal(const short&);			// short로 생성				(~32768~32767)
	IntDecimal(const unsigned short&);	// unsigned short로 생성	(0~65535)
	IntDecimal(const int&);				// int로 생성				(~2147483648~2147483647)

	IntDecimal(const float&);			// float로 생성				(단, 범위 초과시 -2147483648이나 2147483647로 표기/소수점 7자리에서 반올림)
	IntDecimal(const double&);			// double로 생성			(단, 범위 초과시 -2147483648이나 2147483647로 표기/소수점 7자리에서 반올림)

	IntDecimal(const IntDecimal&);		// 복사생성


	float toInt();						// Int로 변환
	float toUnsignedInt();				// UnsignedInt로 변환
	float toFloat();					// float로 변환
	float toDouble();					// Double로 변환
};

