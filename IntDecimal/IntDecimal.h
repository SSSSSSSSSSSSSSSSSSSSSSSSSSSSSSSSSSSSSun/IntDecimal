#pragma once
class IntDecimal
{
private:
	int integerPart;		// ������
	int decimalPart;		// �Ҽ��� (0~999999)

public:

	IntDecimal();						// 0.0

	IntDecimal(const short&);			// short�� ����				(~32768~32767)
	IntDecimal(const unsigned short&);	// unsigned short�� ����	(0~65535)
	IntDecimal(const int&);				// int�� ����				(~2147483648~2147483647)

	IntDecimal(const float&);			// float�� ����				(��, ���� �ʰ��� -2147483648�̳� 2147483647�� ǥ��/�Ҽ��� 7�ڸ����� �ݿø�)
	IntDecimal(const double&);			// double�� ����			(��, ���� �ʰ��� -2147483648�̳� 2147483647�� ǥ��/�Ҽ��� 7�ڸ����� �ݿø�)

	IntDecimal(const IntDecimal&);		// �������


	float toInt();						// Int�� ��ȯ
	float toUnsignedInt();				// UnsignedInt�� ��ȯ
	float toFloat();					// float�� ��ȯ
	float toDouble();					// Double�� ��ȯ
};

