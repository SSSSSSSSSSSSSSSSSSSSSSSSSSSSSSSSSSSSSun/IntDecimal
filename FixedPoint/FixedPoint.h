#pragma once
#include <cmath>
#include <iostream>

class FixedPoint
{
private:
	unsigned int integerPart;		// ������
	unsigned int decimalPart;		// �Ҽ��� (0~999999)
	bool isPositive;				// ��ȣ, 0�� ���� ��� �������� true�� �δ� ���� ��Ģ���� ��
public:

	//=====================================
	//������
	//=====================================

	FixedPoint();						// 0.0

	FixedPoint(const int&);				// int�� ����				(~2147483648~2147483647)
	FixedPoint(const unsigned int&);	// unsigned int�� ����		(0~4294967295)
	FixedPoint(const int&, const unsigned int&);	// ������, �Ҽ��η� ���� (�Ҽ��� 999999 �ʰ��� 0���� ���)
	FixedPoint(const unsigned int&, const unsigned int&, const bool&);
	// ������, �Ҽ���, ��ȣ�� ���� (�Ҽ��� 999999 �ʰ��� 0���� ���)
	
	FixedPoint(float);
	// float�� ����				(��ȿ���� 6�ڸ����� ��ȿ / �Ҽ��� 7�ڸ� ���� ����)
	//							(�������� ����)
	//							(��, -2147480000 ���Ͻ� -214748000�� ǥ�� (INT_MIN == -2147483648)
	//							(��, +2147480000 �̻�� +214748000�� ǥ�� (INT_MAX == +2147483647)
	
	FixedPoint(double);
	// double�� ����			(��ȿ���� 6�ڸ����� ��ȿ / �Ҽ��� 7�ڸ� ���� ����)
	//							(�������� ����)
	//							(��, -2147483647 ���Ͻ� -2147483647�� ǥ�� (INT_MIN == -2147483648)
	//							(��, +2147483647 �̻�� +2147483647�� ǥ�� (INT_MAX == +2147483647)

	FixedPoint(const FixedPoint&);		// �������

	//=====================================
	//������, float, double���� ���/�� ������ ��� ���� (��Ȯ�� ����)
	//=====================================

	//============================
	//���� ������
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
	//(��ȿ���� 6�ڸ����� ��ȿ / �Ҽ��� 7�ڸ� ���� ����)
	//(�������� ����)
	//(��, -2147480000 ���Ͻ� -214748000�� ǥ�� (INT_MIN == -2147483648)
	//(��, +2147480000 �̻�� +214748000�� ǥ�� (INT_MAX == +2147483647)

	FixedPoint& operator=(double);
	//(��ȿ���� 6�ڸ����� ��ȿ / �Ҽ��� 7�ڸ� ���� ����)
	//(�������� ����)
	//(��, -2147483647 ���Ͻ� -2147483647�� ǥ�� (INT_MIN == -2147483648)
	//(��, +2147483647 �̻�� +2147483647�� ǥ�� (INT_MAX == +2147483647)

	FixedPoint& operator=(const FixedPoint&);

	//============================
	//���� ������
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

	// �����γ� ������ �����÷ο�� INT_MIN-0.999999 ����
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
	//�� ��
	//=====================================

	int toInt()  const;						// Int�� ��ȯ			(�Ҽ��� ���� ����)
	unsigned int toUnsignedInt() const;		// UnsignedInt�� ��ȯ	(�Ҽ��� ����/��ȣ(-) ����)
	float toFloat() const;					// float�� ��ȯ
	double toDouble() const;				// Double�� ��ȯ

	FixedPoint abs() const;					// ���밪 ����

	unsigned int getIntegerPart() const; 	// ������ ����
	unsigned int getDecimalPart() const; 	// �Ҽ��� ����
	bool getSign() const;					// ��ȣ ����
	char printSign() const			;		// ��ȣ ���

	void setIntegerPart(unsigned int);		// ������ ����
	void setDecimalPart(unsigned int);		// �Ҽ��� ����
	void setIsPositive(bool);				// ��ȣ ����
	
};