#pragma once
class IntDecimal
{
private:
	unsigned int integerPart;		// ������
	int decimalPart;				// �Ҽ��� (0~999999)
	bool isPositive;				// ��ȣ, 0�� ���� ��� �������� true�� �δ� ���� ��Ģ���� ��
public:

	IntDecimal();						// 0.0

	IntDecimal(const short&);			// short�� ����				(~32768~32767)
	IntDecimal(const unsigned short&);	// unsigned short�� ����	(0~65535)
	IntDecimal(const int&);				// int�� ����				(~2147483648~2147483647)

	IntDecimal(float);
	// float�� ����				(��ȿ���� 6�ڸ����� ��ȿ / �Ҽ��� 7�ڸ� ���� ����)
	//							(��, -2147480000 ���Ͻ� -214748000�� ǥ�� (INT_MIN == -2147483648)
	//							(��, +2147480000 �̻�� +214748000�� ǥ�� (INT_MAX == +2147483647)
	
	IntDecimal(double);
	// double�� ����			(�Ҽ��� 7�ڸ� ���� ����)
	//							(��, -2147483647 ���Ͻ� -2147483647�� ǥ�� (INT_MIN == -2147483648)
	//							(��, +2147483647 �̻�� +2147483647�� ǥ�� (INT_MAX == +2147483647)

	IntDecimal(const IntDecimal&);		// �������


	int toInt();						// Int�� ��ȯ			(�Ҽ��� ���� ����)
	unsigned int toUnsignedInt();		// UnsignedInt�� ��ȯ	(�Ҽ��� ����/��ȣ(-) ����)
	float toFloat();					// float�� ��ȯ
	double toDouble();					// Double�� ��ȯ


	int getIntegerPart(); 	// ������ ����
	int getDecimalPart(); 	// �Ҽ��� ����
	bool getSign();			// ��ȣ ����
	char printSign();		// ��ȣ ���
};

