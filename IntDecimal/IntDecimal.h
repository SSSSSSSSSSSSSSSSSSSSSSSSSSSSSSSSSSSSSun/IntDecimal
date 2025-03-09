#pragma once
class IntDecimal
{
private:
	unsigned int integerPart;		// ������
	unsigned int decimalPart;		// �Ҽ��� (0~999999)
	bool isPositive;				// ��ȣ, 0�� ���� ��� �������� true�� �δ� ���� ��Ģ���� ��
public:

	//=====================================
	//������
	//=====================================

	IntDecimal();						// 0.0

	IntDecimal(const int&);				// int�� ����				(~2147483648~2147483647)
	IntDecimal(const unsigned int&);	// unsigned int�� ����		(0~4294967295)
	IntDecimal(const int&, const unsigned int&);	// ������, �Ҽ��η� ���� (�Ҽ��� 999999 �ʰ��� 0���� ���)
	IntDecimal(const unsigned int&, const unsigned int&, const bool&);
	// ������, �Ҽ���, ��ȣ�� ���� (�Ҽ��� 999999 �ʰ��� 0���� ���)
	
	IntDecimal(float);
	// float�� ����				(��ȿ���� 6�ڸ����� ��ȿ / �Ҽ��� 7�ڸ� ���� ����)
	//							(�������� ����)
	//							(��, -2147480000 ���Ͻ� -214748000�� ǥ�� (INT_MIN == -2147483648)
	//							(��, +2147480000 �̻�� +214748000�� ǥ�� (INT_MAX == +2147483647)
	
	IntDecimal(double);
	// double�� ����			(��ȿ���� 6�ڸ����� ��ȿ / �Ҽ��� 7�ڸ� ���� ����)
	//							(�������� ����)
	//							(��, -2147483647 ���Ͻ� -2147483647�� ǥ�� (INT_MIN == -2147483648)
	//							(��, +2147483647 �̻�� +2147483647�� ǥ�� (INT_MAX == +2147483647)

	IntDecimal(const IntDecimal&);		// �������

	//=====================================
	//������, float, double���� ���/�� ������ ��� ���� (��Ȯ�� ����)
	//=====================================
	IntDecimal& operator+=(const int&);
	IntDecimal& operator+=(const unsigned int&);
	IntDecimal& operator+=(const IntDecimal&);

	IntDecimal& operator-=(const int&);
	IntDecimal& operator-=(const unsigned int&);
	IntDecimal& operator-=(const IntDecimal&);

	IntDecimal& operator*=(const int&);
	IntDecimal& operator*=(const unsigned int&);
	IntDecimal& operator*=(const IntDecimal&);

	IntDecimal& operator/=(const int&);
	IntDecimal& operator/=(const unsigned int&);
	IntDecimal& operator/=(const IntDecimal&);

	IntDecimal& operator=(const int&);
	IntDecimal& operator=(const unsigned int&);

	IntDecimal& operator=(float);
	//(��ȿ���� 6�ڸ����� ��ȿ / �Ҽ��� 7�ڸ� ���� ����)
	//(�������� ����)
	//(��, -2147480000 ���Ͻ� -214748000�� ǥ�� (INT_MIN == -2147483648)
	//(��, +2147480000 �̻�� +214748000�� ǥ�� (INT_MAX == +2147483647)

	IntDecimal& operator=(double);
	//(��ȿ���� 6�ڸ����� ��ȿ / �Ҽ��� 7�ڸ� ���� ����)
	//(�������� ����)
	//(��, -2147483647 ���Ͻ� -2147483647�� ǥ�� (INT_MIN == -2147483648)
	//(��, +2147483647 �̻�� +2147483647�� ǥ�� (INT_MAX == +2147483647)

	IntDecimal& operator=(const IntDecimal&);

	friend IntDecimal operator-(const IntDecimal&);
	friend bool operator!(const IntDecimal&);

	friend IntDecimal operator+(const IntDecimal&, const int&);
	friend IntDecimal operator+(const IntDecimal&, const unsigned int&);
	friend IntDecimal operator+(const IntDecimal&, const IntDecimal&);
	friend IntDecimal operator+(const int&, const IntDecimal&);
	friend IntDecimal operator+(const unsigned int&, const IntDecimal&);

	friend IntDecimal operator-(const IntDecimal&, const int&);
	friend IntDecimal operator-(const IntDecimal&, const unsigned int&);
	friend IntDecimal operator-(const IntDecimal&, const IntDecimal&);
	friend IntDecimal operator-(const int&, const IntDecimal&);
	friend IntDecimal operator-(const unsigned int&, const IntDecimal&);

	// �����γ� ������ �����÷ο�� INT_MIN-0.999999 ����
	friend IntDecimal operator*(const IntDecimal&, const int&);
	friend IntDecimal operator*(const IntDecimal&, const unsigned int&);
	friend IntDecimal operator*(const IntDecimal&, const IntDecimal&);
	friend IntDecimal operator*(const int&, const IntDecimal&);
	friend IntDecimal operator*(const unsigned int&, const IntDecimal&);

	friend IntDecimal operator/(const IntDecimal&, const int&);
	friend IntDecimal operator/(const IntDecimal&, const unsigned int&);
	friend IntDecimal operator/(const IntDecimal&, const IntDecimal&);
	friend IntDecimal operator/(const int&, const IntDecimal&);
	friend IntDecimal operator/(const unsigned int&, const IntDecimal&);

	friend bool operator==(const IntDecimal&, const int&);
	friend bool operator==(const IntDecimal&, const unsigned int&);
	friend bool operator==(const IntDecimal&, const IntDecimal&);
	friend bool operator==(const int&, const IntDecimal&);
	friend bool operator==(const unsigned int&, const IntDecimal&);

	friend bool operator>(const IntDecimal&, const int&);
	friend bool operator>(const IntDecimal&, const unsigned int&);
	friend bool operator>(const IntDecimal&, const IntDecimal&);
	friend bool operator>(const int&, const IntDecimal&);
	friend bool operator>(const unsigned int&, const IntDecimal&);

	friend bool operator<(const IntDecimal&, const int&);
	friend bool operator<(const IntDecimal&, const unsigned int&);
	friend bool operator<(const IntDecimal&, const IntDecimal&);
	friend bool operator<(const int&, const IntDecimal&);
	friend bool operator<(const unsigned int&, const IntDecimal&);

	friend bool operator>=(const IntDecimal&, const int&);
	friend bool operator>=(const IntDecimal&, const unsigned int&);
	friend bool operator>=(const IntDecimal&, const IntDecimal&);
	friend bool operator>=(const int&, const IntDecimal&);
	friend bool operator>=(const unsigned int&, const IntDecimal&);

	friend bool operator<=(const IntDecimal&, const int&);
	friend bool operator<=(const IntDecimal&, const unsigned int&);
	friend bool operator<=(const IntDecimal&, const IntDecimal&);
	friend bool operator<=(const int&, const IntDecimal&);
	friend bool operator<=(const unsigned int&, const IntDecimal&);

	//=====================================
	//�� ��
	//=====================================

	int toInt()  const;						// Int�� ��ȯ			(�Ҽ��� ���� ����)
	unsigned int toUnsignedInt() const;		// UnsignedInt�� ��ȯ	(�Ҽ��� ����/��ȣ(-) ����)
	float toFloat() const;					// float�� ��ȯ
	double toDouble() const;				// Double�� ��ȯ

	IntDecimal abs() const;					// ���밪 ����

	unsigned int getIntegerPart() const; 	// ������ ����
	unsigned int getDecimalPart() const; 	// �Ҽ��� ����
	bool getSign() const;					// ��ȣ ����
	char printSign() const			;		// ��ȣ ���

	void setIntegerPart(unsigned int);		// ������ ����
	void setDecimalPart(unsigned int);		// �Ҽ��� ����
	void setIsPositive(bool);				// ��ȣ ����
	
};