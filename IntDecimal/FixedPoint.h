#pragma once
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

	FixedPoint(const short&);			// short�� ����				(~32768~32767)
	FixedPoint(const unsigned short&);	// unsigned short�� ����	(0~65535)
	FixedPoint(const int&);				// int�� ����				(~2147483648~2147483647)
	FixedPoint(const unsigned int&);	// unsigned int�� ����		(0~4294967295)
	FixedPoint(int&, const unsigned int&);	// ������, �Ҽ��η� ���� (�Ҽ��� 999999 �ʰ��� 0���� ���)
	FixedPoint(const unsigned int&, const unsigned int&, const bool&);
	// ������, �Ҽ���, ��ȣ�� ���� (�Ҽ��� 999999 �ʰ��� 0���� ���)
	
	FixedPoint(float);
	// float�� ����				(��ȿ���� 6�ڸ����� ��ȿ / �Ҽ��� 7�ڸ� ���� ����)
	//							(��, -2147480000 ���Ͻ� -214748000�� ǥ�� (INT_MIN == -2147483648)
	//							(��, +2147480000 �̻�� +214748000�� ǥ�� (INT_MAX == +2147483647)
	
	FixedPoint(double);
	// double�� ����			(��ȿ���� 6�ڸ����� ��ȿ / �Ҽ��� 7�ڸ� ���� ����)
	//							(��, -2147483647 ���Ͻ� -2147483647�� ǥ�� (INT_MIN == -2147483648)
	//							(��, +2147483647 �̻�� +2147483647�� ǥ�� (INT_MAX == +2147483647)

	FixedPoint(const FixedPoint&);		// �������

	//=====================================
	//������, float, double���� ������ ��� ���� (��Ȯ�� ����)
	//=====================================

	FixedPoint operator-() const;

	FixedPoint operator+(const short&) const;
	FixedPoint operator+(const unsigned short&) const;
	FixedPoint operator+(const int&) const;
	FixedPoint operator+(const unsigned int&) const;
	FixedPoint operator+(const FixedPoint&) const;

	FixedPoint operator-(const short&) const;
	FixedPoint operator-(const unsigned short&) const;
	FixedPoint operator-(const int&) const;
	FixedPoint operator-(const unsigned int&) const;
	FixedPoint operator-(const FixedPoint&) const;

	FixedPoint operator*(const short&) const;
	FixedPoint operator*(const unsigned short&) const;
	FixedPoint operator*(const int&) const;
	FixedPoint operator*(const unsigned int&) const;
	FixedPoint operator*(const FixedPoint&) const;

	FixedPoint operator/(const short&) const;
	FixedPoint operator/(const unsigned short&) const;
	FixedPoint operator/(const int&) const;
	FixedPoint operator/(const unsigned int&) const;
	FixedPoint operator/(const FixedPoint&) const;

	FixedPoint& operator+=(const short&) const;
	FixedPoint& operator+=(const unsigned short&) const;
	FixedPoint& operator+=(const int&) const;
	FixedPoint& operator+=(const unsigned int&) const;
	FixedPoint& operator+=(const FixedPoint&) const;

	FixedPoint& operator-=(const short&) const;
	FixedPoint& operator-=(const unsigned short&) const;
	FixedPoint& operator-=(const int&) const;
	FixedPoint& operator-=(const unsigned int&) const;
	FixedPoint& operator-=(const FixedPoint&) const;

	FixedPoint& operator*=(const short&) const;
	FixedPoint& operator*=(const unsigned short&) const;
	FixedPoint& operator*=(const int&) const;
	FixedPoint& operator*=(const unsigned int&) const;
	FixedPoint& operator*=(const FixedPoint&) const;

	FixedPoint& operator/=(const short&) const;
	FixedPoint& operator/=(const unsigned short&) const;
	FixedPoint& operator/=(const int&) const;
	FixedPoint& operator/=(const unsigned int&) const;
	FixedPoint& operator/=(const FixedPoint&) const;

	bool operator==(const short&) const;
	bool operator==(const unsigned short&) const;
	bool operator==(const int&) const;
	bool operator==(const unsigned int&) const;
	bool operator==(const FixedPoint&) const;

	bool operator>=(const short&) const;
	bool operator>=(const unsigned short&) const;
	bool operator>=(const int&) const;
	bool operator>=(const unsigned int&) const;
	bool operator>=(const FixedPoint&) const;

	bool operator<=(const short&) const;
	bool operator<=(const unsigned short&) const;
	bool operator<=(const int&) const;
	bool operator<=(const unsigned int&) const;
	bool operator<=(const FixedPoint&) const;

	bool operator>(const short&) const;
	bool operator>(const unsigned short&) const;
	bool operator>(const int&) const;
	bool operator>(const unsigned int&) const;
	bool operator>(const FixedPoint&) const;

	bool operator<(const short&) const;
	bool operator<(const unsigned short&) const;
	bool operator<(const int&) const;
	bool operator<(const unsigned int&) const;
	bool operator<(const FixedPoint&) const;

	FixedPoint& operator=(const short&);
	FixedPoint& operator=(const unsigned short&);
	FixedPoint& operator=(const int&);
	FixedPoint& operator=(const unsigned int&);

	FixedPoint& operator=(float);
	//(��ȿ���� 6�ڸ����� ��ȿ / �Ҽ��� 7�ڸ� ���� ����)
	//(��, -2147480000 ���Ͻ� -214748000�� ǥ�� (INT_MIN == -2147483648)
	//(��, +2147480000 �̻�� +214748000�� ǥ�� (INT_MAX == +2147483647)

	FixedPoint& operator=(double);
	//(��ȿ���� 6�ڸ����� ��ȿ / �Ҽ��� 7�ڸ� ���� ����)
	//(��, -2147483647 ���Ͻ� -2147483647�� ǥ�� (INT_MIN == -2147483648)
	//(��, +2147483647 �̻�� +2147483647�� ǥ�� (INT_MAX == +2147483647)

	FixedPoint& operator=(const FixedPoint&);

	bool operator!() const;

	//=====================================
	//�� ��
	//=====================================

	int toInt()  const;						// Int�� ��ȯ			(�Ҽ��� ���� ����)
	unsigned int toUnsignedInt() const;		// UnsignedInt�� ��ȯ	(�Ҽ��� ����/��ȣ(-) ����)
	float toFloat() const;					// float�� ��ȯ
	double toDouble() const;				// Double�� ��ȯ

	FixedPoint abc() const;					// ���밪 ����

	unsigned int getIntegerPart() const; 	// ������ ����
	unsigned int getDecimalPart() const; 	// �Ҽ��� ����
	bool getSign() const;					// ��ȣ ����
	char printSign() const			;		// ��ȣ ���


	
};

