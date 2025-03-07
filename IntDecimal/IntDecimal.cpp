#include "IntDecimal.h"

//������

// 0.0
IntDecimal::IntDecimal()
	: integerPart(0), decimalPart(0) {}

// short�� ����				(~32768~32767)
IntDecimal::IntDecimal(const short& integer)
	: integerPart(integer), decimalPart(0) {}

// unsigned short�� ����	(0~65535)
IntDecimal::IntDecimal(const unsigned short& integer)
	: integerPart(integer), decimalPart(0) {}

// int�� ����				(~2147483648~2147483647)
IntDecimal::IntDecimal(const int& integer)
	: integerPart(integer), decimalPart(0) {}

// float�� ����				(��, ���� �ʰ��� -2147483648�̳� 2147483647�� ǥ��/�Ҽ��� 7�ڸ����� �ݿø�)
IntDecimal::IntDecimal(const float& floatNumber) {
	

}

// double�� ����			(��, ���� �ʰ��� -2147483648�̳� 2147483647�� ǥ��/�Ҽ��� 7�ڸ����� �ݿø�)
IntDecimal::IntDecimal(const double&) {

}

// ���������
IntDecimal::IntDecimal(const IntDecimal&) {

}





// Int�� ��ȯ
float IntDecimal::toInt() {

}

// UnsignedInt�� ��ȯ
float IntDecimal::toUnsignedInt() {

}

// float�� ��ȯ
float IntDecimal::toFloat() {

}

// Double�� ��ȯ
float IntDecimal::toDouble() {

}