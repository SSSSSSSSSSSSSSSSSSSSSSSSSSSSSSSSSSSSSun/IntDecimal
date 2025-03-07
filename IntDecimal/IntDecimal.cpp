#include "IntDecimal.h"

//생성자

// 0.0
IntDecimal::IntDecimal()
	: integerPart(0), decimalPart(0) {}

// short로 생성				(~32768~32767)
IntDecimal::IntDecimal(const short& integer)
	: integerPart(integer), decimalPart(0) {}

// unsigned short로 생성	(0~65535)
IntDecimal::IntDecimal(const unsigned short& integer)
	: integerPart(integer), decimalPart(0) {}

// int로 생성				(~2147483648~2147483647)
IntDecimal::IntDecimal(const int& integer)
	: integerPart(integer), decimalPart(0) {}

// float로 생성				(단, 범위 초과시 -2147483648이나 2147483647로 표기/소수점 7자리에서 반올림)
IntDecimal::IntDecimal(const float& floatNumber) {
	

}

// double로 생성			(단, 범위 초과시 -2147483648이나 2147483647로 표기/소수점 7자리에서 반올림)
IntDecimal::IntDecimal(const double&) {

}

// 복사생성자
IntDecimal::IntDecimal(const IntDecimal&) {

}





// Int로 변환
float IntDecimal::toInt() {

}

// UnsignedInt로 변환
float IntDecimal::toUnsignedInt() {

}

// float로 변환
float IntDecimal::toFloat() {

}

// Double로 변환
float IntDecimal::toDouble() {

}