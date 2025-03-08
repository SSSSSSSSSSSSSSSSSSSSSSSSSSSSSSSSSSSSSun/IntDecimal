#include "FixedPoint.h"
#include <cmath>
#include <iostream>

//=====================================
//������
//=====================================

// 0.0
FixedPoint::FixedPoint()
	: integerPart(0), decimalPart(0), isPositive(true) {}



// short�� ����				(~32768~32767)
FixedPoint::FixedPoint(const short& integer)
	: decimalPart(0)
{
	if (integer < 0) {
		integerPart = integer * -1;
		isPositive = false;
	}
	else {
		integerPart = integer;
		isPositive = true;
	}
}



// unsigned short�� ����	(0~65535)
FixedPoint::FixedPoint(const unsigned short& integer)
	: integerPart(integer), decimalPart(0), isPositive(true){}



// int�� ����				(~2147483648~2147483647)
FixedPoint::FixedPoint(const int& integer)
	: decimalPart(0)
{
	if (integer < 0) {
		integerPart = integer * -1;
		isPositive = false;
	}
	else {
		integerPart = integer;
		isPositive = true;
	}
}


// unsigned int�� ����		(0~4294967295)
FixedPoint::FixedPoint(const unsigned int& integer)
	: integerPart(integer), decimalPart(0), isPositive(true) {
}


// float�� ����	(����� �������� ����)
// (��ȿ���� 6�ڸ����� ��ȿ / �Ҽ��� 7�ڸ� ���� ����)
// (��, -2147480000 ���Ͻ� -214748000�� ǥ�� (INT_MIN == -2147483648)
// (��, +2147480000 �̻�� +214748000�� ǥ�� (INT_MAX == +2147483647)
FixedPoint::FixedPoint(float floatNumber) {

	// +2147480000 �̻�� +214748000�� ǥ��
	if (floatNumber >= 2147480000) {
		integerPart = 2147480000;
		decimalPart = 0;
		isPositive = true;
		return;
	}

	// -2147480000 ���Ͻ� -214748000�� ǥ��
	if (floatNumber <= -2147480000) {
		integerPart = 2147480000;
		decimalPart = 0;
		isPositive = false;
		return;
	}

	// 0
	if (floatNumber == 0) {
		integerPart = 0;
		decimalPart = 0;
		isPositive = true;
	}

	// ���/���� �Ǻ��ؼ� ���
	if (floatNumber >= 0) {
		isPositive = true;
	}
	else {
		isPositive = false;
		floatNumber *= -1.0f;
	}


	short numDigits = static_cast<short>(log10(floatNumber));

	// ���밪 10 �̻� �� ��

	if (numDigits > 0) {
		numDigits++;		// �ڸ��� ǥ���� ���� 1 ����

		floatNumber *= powf(10.0f, static_cast<float>(6 - numDigits));
		float cuttedIntegerPart;
		modf(floatNumber, &cuttedIntegerPart);
		integerPart = static_cast<unsigned int>(cuttedIntegerPart);
		if (numDigits < 6) {
			decimalPart = integerPart % static_cast<unsigned int>(pow(10, 6 - numDigits));
			integerPart /= static_cast<unsigned int>(pow(10, 6 - numDigits));
			decimalPart *= static_cast<unsigned int>(pow(10, numDigits));
		}
		else {
			integerPart *= static_cast<unsigned int>(pow(10, numDigits - 1));
			decimalPart = 0;
		}

		return;
	}
	

	// ���밪 1 �̻� 10 �̸��� ��

	if (floatNumber >= 1) {
		floatNumber *= 100000;
		float cuttedIntegerPart;
		modf(floatNumber, &cuttedIntegerPart);
		integerPart = static_cast<unsigned int>(cuttedIntegerPart);
		decimalPart = integerPart % 100000;
		integerPart /= 100000;
		decimalPart *= 10;

		return;
	}

	// ���밪 1 �̸��� ��

	integerPart = 0;
	float cuttedIntegerPart;
	modf(floatNumber*1000000.0f, &cuttedIntegerPart);
	decimalPart = cuttedIntegerPart;

	if (decimalPart == 0)	// 0�϶� ��ȣ�� +�� �ٲ���
		isPositive = true;

}



// double�� ����
// (��ȿ���� 6�ڸ����� ��ȿ / �Ҽ��� 7�ڸ� ���� ����)
// (��, -2147483647 ���Ͻ� -2147483647�� ǥ�� (INT_MIN == -2147483648)
// (��, +2147483647 �̻�� +2147483647�� ǥ�� (INT_MAX == +2147483647)
FixedPoint::FixedPoint(double doubleNumber) {

	// +2147483647 �̻�� +2147483647�� ǥ��
	if (doubleNumber >= 2147483647) {
		integerPart = 2147483647;
		decimalPart = 0;
		isPositive = true;
		return;
	}

	// -2147483647 ���Ͻ� -2147483647�� ǥ��
	if (doubleNumber <= -2147483647) {
		integerPart = -2147483647;
		decimalPart = 0;
		isPositive = false;
		return;
	}
	
	// 0
	if (doubleNumber == 0) {
		integerPart = 0;
		decimalPart = 0;
		isPositive = true;
	}

	// ���/���� �Ǻ��ؼ� ���
	if (doubleNumber >= 0) {
		isPositive = true;
	}
	else {
		isPositive = false;
		doubleNumber *= -1;
	}

	
	short numDigits = static_cast<short>(log10(doubleNumber));

	// ���밪 10 �̻� �� ��

	if (numDigits > 0) {
		numDigits++;		// �ڸ��� ǥ���� ���� 1 ����

		doubleNumber *= pow(10.0, static_cast<double>(6 - numDigits));
		double cuttedIntegerPart;
		modf(doubleNumber, &cuttedIntegerPart);
		integerPart = static_cast<unsigned int>(cuttedIntegerPart);
		if (numDigits < 6) {
			decimalPart = integerPart % static_cast<unsigned int>(pow(10, 6 - numDigits));
			integerPart /= static_cast<unsigned int>(pow(10, 6 - numDigits));
			decimalPart *= static_cast<unsigned int>(pow(10, numDigits));
		}
		else {
			integerPart *= static_cast<unsigned int>(pow(10, numDigits - 1));
			decimalPart = 0;
		}

		return;
	}


	// ���밪 1 �̻� 10 �̸��� ��

	if (doubleNumber >= 1) {
		doubleNumber *= 100000;
		std::cout << '=' << doubleNumber << std::endl;
		double cuttedIntegerPart;
		modf(doubleNumber, &cuttedIntegerPart);
		integerPart = static_cast<unsigned int>(cuttedIntegerPart);
		decimalPart = integerPart % 100000;
		integerPart /= 100000;
		decimalPart *= 10;
		return;
	}

	// ���밪 1 �̸��� ��

	integerPart = 0;
	double cuttedIntegerPart;
	modf(doubleNumber*1000000, &cuttedIntegerPart);
	decimalPart = static_cast<unsigned int>(cuttedIntegerPart);

	if (decimalPart == 0)	// 0�϶� ��ȣ�� +�� �ٲ���
		isPositive = true;
	
}

// ������, �Ҽ��η� ���� (�Ҽ��� 999999 �ʰ��� 0���� ���)
FixedPoint::FixedPoint(int& inputIntegerPart, const unsigned int& inputDecimalPart){
	if (inputIntegerPart >= 0) {
		isPositive = true;
		integerPart = static_cast<unsigned int>(inputIntegerPart);
	}
	else {
		isPositive = false;
		integerPart = static_cast<unsigned int>(-inputIntegerPart);
	}
	
	decimalPart = inputDecimalPart;
	if (inputDecimalPart > 999999)
		decimalPart = 0;

}

// ������, �Ҽ���, ��ȣ�� ���� (�Ҽ��� 999999 �ʰ��� 0���� ���)
FixedPoint::FixedPoint(const unsigned int& inputIntegerPart, const unsigned int& inputDecimalPart, const bool& inputIsPositive)
	: integerPart(inputIntegerPart), decimalPart(inputDecimalPart), isPositive(inputIsPositive)
{}

// ���������
FixedPoint::FixedPoint(const FixedPoint& original)
	: integerPart(original.integerPart), decimalPart(original.decimalPart), isPositive(original.isPositive) {}




//=====================================
//������
//=====================================

//============
//���� ������ -
//============
FixedPoint FixedPoint::operator-() const {
	return FixedPoint(this->integerPart, this->decimalPart, not (this->isPositive));
}


//============
//+
//============
 
FixedPoint FixedPoint::operator+(const short& data) const {
	unsigned int newIntegerPart;
	unsigned int newDecimalPart;
	bool dataIsPositive;

	if (data >= 0)
		dataIsPositive = true;
	else
		dataIsPositive = false;

	// + + or - -
	if (isPositive == dataIsPositive) {
		if (isPositive) {
			newIntegerPart = integerPart + static_cast<unsigned int>(data);
			return FixedPoint(newIntegerPart, decimalPart, dataIsPositive);
		}
		else {
			newIntegerPart = integerPart + static_cast<unsigned int>(-data);
			return FixedPoint(newIntegerPart, decimalPart, dataIsPositive);
		}
	}

	// ���ļ� 0
	if (-(*this) == data) {
		return FixedPoint();
	}
	
	// + -
	if (isPositive) {
		// this�� ���밪�� �� Ŭ��
		if (*this > -data) {
			newIntegerPart = integerPart - static_cast<unsigned int>(-data);
			return FixedPoint(newIntegerPart, decimalPart, isPositive);
		}
		else {
			newIntegerPart = static_cast<unsigned int>(-data) - integerPart;

			// �Ҽ��� ���, // 0�� data�� �Ҽ��θ� �ǹ� (.000000)
			if (decimalPart > 0) {
				newIntegerPart--;
				newDecimalPart = 0 + 1000000 - decimalPart;
			}
			return FixedPoint(newIntegerPart, newDecimalPart, dataIsPositive);
		}
	}
	// - +
	else {
		// data�� ���밪�� �� Ŭ��
		if (-(*this) > data) {
			newIntegerPart = integerPart - static_cast<unsigned int>(data);
			return FixedPoint(newIntegerPart, decimalPart, isPositive);
		}
		else {
			newIntegerPart = static_cast<unsigned int>(data) - integerPart;

			// �Ҽ��� ���, // 0�� data�� �Ҽ��θ� �ǹ� (.000000)
			if (decimalPart > 0) {
				newIntegerPart--;
				newDecimalPart = 0 + 1000000 - decimalPart;
			}
			return FixedPoint(newIntegerPart, newDecimalPart, dataIsPositive);
		}
	}

}

FixedPoint FixedPoint::operator+(const unsigned short& data) const {
	unsigned int newIntegerPart;
	unsigned int newDecimalPart;
	bool dataIsPositive = true;

	// + +
	if (isPositive == dataIsPositive) {
		newIntegerPart = integerPart + data;
		return FixedPoint(newIntegerPart, decimalPart, dataIsPositive);
	}

	// ���ļ� 0
	if (-(*this) == data) {
		return FixedPoint();
	}
	// - +
	else {
		// data�� ���밪�� �� Ŭ��
		if (-(*this) > data) {
			newIntegerPart = integerPart - data;
			return FixedPoint(newIntegerPart, decimalPart, isPositive);
		}
		else {
			newIntegerPart = data - integerPart;

			// �Ҽ��� ���, // 0�� data�� �Ҽ��θ� �ǹ� (.000000)
			if (decimalPart > 0) {
				newIntegerPart--;
				newDecimalPart = 0 + 1000000 - decimalPart;
			}
			return FixedPoint(newIntegerPart, newDecimalPart, dataIsPositive);
		}
	}
}


FixedPoint FixedPoint::operator+(const int& data) const {
	unsigned int newIntegerPart;
	unsigned int newDecimalPart;
	bool dataIsPositive;

	if (data >= 0)
		dataIsPositive = true;
	else
		dataIsPositive = false;

	// + + or - -
	if (isPositive == dataIsPositive) {
		if (isPositive) {
			newIntegerPart = integerPart + static_cast<unsigned int>(data);
			return FixedPoint(newIntegerPart, decimalPart, dataIsPositive);
		}
		else {
			newIntegerPart = integerPart + static_cast<unsigned int>(-data);
			return FixedPoint(newIntegerPart, decimalPart, dataIsPositive);
		}
	}

	// ���ļ� 0
	if (-(*this) == data) {
		return FixedPoint();
	}

	// + -
	if (isPositive) {
		// this�� ���밪�� �� Ŭ��
		if (*this > -data) {
			newIntegerPart = integerPart - static_cast<unsigned int>(-data);
			return FixedPoint(newIntegerPart, decimalPart, isPositive);
		}
		else {
			newIntegerPart = static_cast<unsigned int>(-data) - integerPart;

			// �Ҽ��� ���, // 0�� data�� �Ҽ��θ� �ǹ� (.000000)
			if (decimalPart > 0) {
				newIntegerPart--;
				newDecimalPart = 0 + 1000000 - decimalPart;
			}
			return FixedPoint(newIntegerPart, newDecimalPart, dataIsPositive);
		}
	}
	// - +
	else {
		// data�� ���밪�� �� Ŭ��
		if (-(*this) > data) {
			newIntegerPart = integerPart - static_cast<unsigned int>(data);
			return FixedPoint(newIntegerPart, decimalPart, isPositive);
		}
		else {
			newIntegerPart = static_cast<unsigned int>(data) - integerPart;

			// �Ҽ��� ���, // 0�� data�� �Ҽ��θ� �ǹ� (.000000)
			if (decimalPart > 0) {
				newIntegerPart--;
				newDecimalPart = 0 + 1000000 - decimalPart;
			}
			return FixedPoint(newIntegerPart, newDecimalPart, dataIsPositive);
		}
	}
}
FixedPoint FixedPoint::operator+(const unsigned int& data) const {
	unsigned int newIntegerPart;
	unsigned int newDecimalPart;
	bool dataIsPositive = true;

	// + +
	if (isPositive == dataIsPositive) {
		newIntegerPart = integerPart + data;
		return FixedPoint(newIntegerPart, decimalPart, dataIsPositive);
	}

	// ���ļ� 0
	if (-(*this) == data) {
		return FixedPoint();
	}
	// - +
	else {
		// data�� ���밪�� �� Ŭ��
		if (-(*this) > data) {
			newIntegerPart = integerPart - data;
			return FixedPoint(newIntegerPart, decimalPart, isPositive);
		}
		else {
			newIntegerPart = data - integerPart;

			// �Ҽ��� ���, // 0�� data�� �Ҽ��θ� �ǹ� (.000000)
			if (decimalPart > 0) {
				newIntegerPart--;
				newDecimalPart = 0 + 1000000 - decimalPart;
			}
			return FixedPoint(newIntegerPart, newDecimalPart, dataIsPositive);
		}
	}
}

FixedPoint FixedPoint::operator+(const FixedPoint& data) const {
	unsigned int newIntegerPart;
	unsigned int newDecimalPart;

	// + + or - -
	if (isPositive == data.isPositive) {
		newIntegerPart = integerPart + data.integerPart;
		newDecimalPart = decimalPart + data.decimalPart;

		if (newDecimalPart >= 1000000) {
			newIntegerPart++;
			newDecimalPart -= 1000000;
		}

		return FixedPoint(newIntegerPart, newDecimalPart, isPositive);
	}

	// ���ļ� 0
	if (-(*this) == data) {
		return FixedPoint();
	}

	// ��ȣ�� �ٸ���
	
	if (this->abc() > data.abc()) {		// this�� ���밪�� �� Ŭ��
		newIntegerPart = integerPart - data.integerPart;

		// �Ҽ��� ���
		if (decimalPart >= data.decimalPart) {
			newDecimalPart = decimalPart - data.decimalPart;
		}
		else {
			newIntegerPart--;
			newDecimalPart = (decimalPart + 1000000) - data.decimalPart;
		}
		return FixedPoint(newIntegerPart, newDecimalPart, isPositive);
	}
	else {
		newIntegerPart = data.integerPart - integerPart;

		// �Ҽ��� ���
		if (data.decimalPart >= decimalPart) {
			newDecimalPart = data.decimalPart - decimalPart;
		}
		else {
			newIntegerPart--;
			newDecimalPart = (data.decimalPart + 1000000) - decimalPart;
		}

		return FixedPoint(newIntegerPart, newDecimalPart, data.isPositive);

	}



}

//============
//==
//============

bool FixedPoint::operator==(const short& data) const {
	if (not decimalPart)
		return false;

	if (isPositive && data < 0)
		return false;

	if (not isPositive && data > 0)
		return false;

	if (data == integerPart)
		return true;
	return false;
}
bool FixedPoint::operator==(const unsigned short& data) const {
	if (not decimalPart)
		return false;

	if (not isPositive && data > 0)
		return false;

	if (data == integerPart)
		return true;
	return false;
}
bool FixedPoint::operator==(const int& data) const {
	if (not decimalPart)
		return false;

	if (isPositive && data < 0)
		return false;

	if (not isPositive && data > 0)
		return false;

	if (data == integerPart)
		return true;
	return false;
}

bool FixedPoint::operator==(const unsigned int& data) const {
	if (not decimalPart)
		return false;

	if (not isPositive && data > 0)
		return false;

	if (data == integerPart)
		return true;
	return false;
}
bool FixedPoint::operator==(const FixedPoint& data) const {
	if (not (integerPart == data.integerPart))
		return false;

	if (not (decimalPart == data.decimalPart))
		return false;

	if (not (isPositive == data.isPositive)) {
		if (integerPart == 0 && decimalPart == 0) {
			return true;
		}
		return false;
	}

	return true;
}

//============
//>=
//============

bool FixedPoint::operator>=(const short& data) const {
	
	// ������
	if (*this == data)
		return true;

	// ��ȣ �� (+>-)
	if (isPositive && data < 0)
		return true;

	// ��ȣ �� (->+)
	if (not isPositive && data > 0)
		return false;

	// ���� +�϶�
	if (isPositive) {
		if (integerPart >= static_cast<unsigned int>(data))
			return true;			// �����ΰ� ���Ƶ� 5.0�� 5�� �� ���� ������ �Ͼ�� ����
		return false;
	}

	// ���� -�϶�
	if (integerPart >= static_cast<unsigned int>(data) * -1)
		return false;				// �����ΰ� ���Ƶ� -5.0�� -5�� �� ���� ������ �Ͼ�� ����
	return true;

}
bool FixedPoint::operator>=(const unsigned short& data) const {
	// ������
	if (*this == data)
		return true;

	// *this�� -�϶�
	if (not isPositive)
		return false;

	// ���� +�϶�
	if (integerPart >= data)
		return true;				// �����ΰ� ���Ƶ� -5.0�� -5�� �� ���� ������ �Ͼ�� ����
	return false;
}

bool FixedPoint::operator>=(const int& data) const {
	// ������
	if (*this == data)
		return true;

	// ��ȣ �� (+>-)
	if (isPositive && data < 0)
		return true;

	// ��ȣ �� (->+)
	if (not isPositive && data > 0)
		return false;

	// ���� +�϶�
	if (isPositive) {
		if (integerPart >= static_cast<unsigned int>(data))
			return true;			// �����ΰ� ���Ƶ� -5.0�� -5�� �� ���� ������ �Ͼ�� ����
		return false;
	}

	// ���� -�϶�
	if (integerPart >= static_cast<unsigned int>(data) * -1)
		return false;				// �����ΰ� ���Ƶ� -5.0�� -5�� �� ���� ������ �Ͼ�� ����
	return true;
}

bool FixedPoint::operator>=(const unsigned int& data) const {
	// ������
	if (*this == data)
		return true;

	// *this�� -�϶�
	if (not isPositive)
		return false;

	// ���� +�϶�
	if (integerPart >= data)
		return true;				// �����ΰ� ���Ƶ� -5.0�� -5�� �� ���� ������ �Ͼ�� ����
	return false;
}

bool FixedPoint::operator>=(const FixedPoint& data) const {
	// ������
	if (*this == data)
		return true;

	// ��ȣ �� (+>-)
	if (isPositive && not data.isPositive)
		return true;

	// ��ȣ �� (->+)
	if (not isPositive && data.isPositive)
		return false;

	// ���� +�϶� (���밪�� ū�� �� ŭ)
	if (isPositive) {
		if (integerPart > data.integerPart)
			return true;
		if (integerPart < data.integerPart)
			return false;

		if (decimalPart > data.decimalPart)
			return true;
		return false;
	}

	// ���� -�϶� (���밪�� ������ �� ŭ)
	if (integerPart > data.integerPart)
		return false;
	if (integerPart < data.integerPart)
		return true;

	if (decimalPart > data.decimalPart)
		return false;
	return true;
}

//============
//<=
//============

bool FixedPoint::operator<=(const short& data) const {

	// ������
	if (*this == data)
		return true;

	// ��ȣ �� (+<-)
	if (isPositive && data < 0)
		return false;

	// ��ȣ �� (-<+)
	if (not isPositive && data > 0)
		return true;

	// ���� +�϶�
	if (isPositive) {
		if (integerPart >= static_cast<unsigned int>(data))
			return false;			// �����ΰ� ���Ƶ� 5.0�� 5�� �� ���� ������ �Ͼ�� ����
		return true;
	}

	// ���� -�϶�
	if (integerPart >= static_cast<unsigned int>(data) * -1)
		return true;				// �����ΰ� ���Ƶ� -5.0�� -5�� �� ���� ������ �Ͼ�� ����
	return false;

}
bool FixedPoint::operator<= (const unsigned short& data) const {
	// ������
	if (*this == data)
		return true;

	// *this�� -�϶�
	if (not isPositive)
		return true;

	// ���� +�϶�
	if (integerPart >= data)
		return false;				// �����ΰ� ���Ƶ� -5.0�� -5�� �� ���� ������ �Ͼ�� ����
	return true;
}

bool FixedPoint::operator<= (const int& data) const {
	// ������
	if (*this == data)
		return true;

	// ��ȣ �� (+<-)
	if (isPositive && data < 0)
		return false;

	// ��ȣ �� (-<+)
	if (not isPositive && data > 0)
		return true;

	// ���� +�϶�
	if (isPositive) {
		if (integerPart >= static_cast<unsigned int>(data))
			return false;			// �����ΰ� ���Ƶ� -5.0�� -5�� �� ���� ������ �Ͼ�� ����
		return true;
	}

	// ���� -�϶�
	if (integerPart >= static_cast<unsigned int>(data) * -1)
		return true;				// �����ΰ� ���Ƶ� -5.0�� -5�� �� ���� ������ �Ͼ�� ����
	return false;
}

bool FixedPoint::operator<= (const unsigned int& data) const {
	// ������
	if (*this == data)
		return true;

	// *this�� -�϶�
	if (not isPositive)
		return true;

	// ���� +�϶�
	if (integerPart >= data)
		return false;				// �����ΰ� ���Ƶ� -5.0�� -5�� �� ���� ������ �Ͼ�� ����
	return true;
}

bool FixedPoint::operator<=(const FixedPoint& data) const {
	// ������
	if (*this == data)
		return true;

	// ��ȣ �� (+<-)
	if (isPositive && not data.isPositive)
		return false;

	// ��ȣ �� (-<+)
	if (not isPositive && data.isPositive)
		return true;

	// ���� +�϶� (���밪�� ū�� �� ŭ)
	if (isPositive) {
		if (integerPart > data.integerPart)
			return false;
		if (integerPart < data.integerPart)
			return true;

		if (decimalPart > data.decimalPart)
			return false;
		return true;
	}

	// ���� -�϶� (���밪�� ������ �� ŭ)
	if (integerPart > data.integerPart)
		return true;
	if (integerPart < data.integerPart)
		return false;

	if (decimalPart > data.decimalPart)
		return true;
	return false;
}

//============
//>
//============

bool FixedPoint::operator>(const short& data) const {

	// ������
	if (*this == data)
		return false;

	// ��ȣ �� (+>=-)
	if (isPositive && data < 0)
		return true;

	// ��ȣ �� (->=+)
	if (not isPositive && data > 0)
		return false;

	// ���� +�϶�
	if (isPositive) {
		if (integerPart >= static_cast<unsigned int>(data))
			return true;			// �����ΰ� ���Ƶ� 5.0�� 5�� �� ���� ������ �Ͼ�� ����
		return false;
	}

	// ���� -�϶�
	if (integerPart >= static_cast<unsigned int>(data) * -1)
		return false;				// �����ΰ� ���Ƶ� -5.0�� -5�� �� ���� ������ �Ͼ�� ����
	return true;

}
bool FixedPoint::operator>(const unsigned short& data) const {
	// ������
	if (*this == data)
		return false;

	// *this�� -�϶�
	if (not isPositive)
		return false;

	// ���� +�϶�
	if (integerPart >= data)
		return true;				// �����ΰ� ���Ƶ� -5.0�� -5�� �� ���� ������ �Ͼ�� ����
	return false;
}

bool FixedPoint::operator>(const int& data) const {
	// ������
	if (*this == data)
		return false;

	// ��ȣ �� (+>=-)
	if (isPositive && data < 0)
		return true;

	// ��ȣ �� (->=+)
	if (not isPositive && data > 0)
		return false;

	// ���� +�϶�
	if (isPositive) {
		if (integerPart >= static_cast<unsigned int>(data))
			return true;			// �����ΰ� ���Ƶ� -5.0�� -5�� �� ���� ������ �Ͼ�� ����
		return false;
	}

	// ���� -�϶�
	if (integerPart >= static_cast<unsigned int>(data) * -1)
		return false;				// �����ΰ� ���Ƶ� -5.0�� -5�� �� ���� ������ �Ͼ�� ����
	return true;
}

bool FixedPoint::operator>(const unsigned int& data) const {
	// ������
	if (*this == data)
		return false;

	// *this�� -�϶�
	if (not isPositive)
		return false;

	// ���� +�϶�
	if (integerPart >= data)
		return true;				// �����ΰ� ���Ƶ� -5.0�� -5�� �� ���� ������ �Ͼ�� ����
	return false;
}

bool FixedPoint::operator>(const FixedPoint& data) const {
	// ������
	if (*this == data)
		return false;

	// ��ȣ �� (+>=-)
	if (isPositive && not data.isPositive)
		return true;

	// ��ȣ �� (->=+)
	if (not isPositive && data.isPositive)
		return false;

	// ���� +�϶� (���밪�� ū�� �� ŭ)
	if (isPositive) {
		if (integerPart > data.integerPart)
			return true;
		if (integerPart < data.integerPart)
			return false;

		if (decimalPart > data.decimalPart)
			return true;
		return false;
	}

	// ���� -�϶� (���밪�� ������ �� ŭ)
	if (integerPart > data.integerPart)
		return false;
	if (integerPart < data.integerPart)
		return true;

	if (decimalPart > data.decimalPart)
		return false;
	return true;
}

//============
//<
//============

bool FixedPoint::operator<(const short& data) const {

	// ������
	if (*this == data)
		return false;

	// ��ȣ �� (+<-)
	if (isPositive && data < 0)
		return false;

	// ��ȣ �� (-<+)
	if (not isPositive && data > 0)
		return true;

	// ���� +�϶�
	if (isPositive) {
		if (integerPart >= static_cast<unsigned int>(data))
			return false;			// �����ΰ� ���Ƶ� 5.0�� 5�� �� ���� ������ �Ͼ�� ����
		return true;
	}

	// ���� -�϶�
	if (integerPart >= static_cast<unsigned int>(data) * -1)
		return true;				// �����ΰ� ���Ƶ� -5.0�� -5�� �� ���� ������ �Ͼ�� ����
	return false;

}
bool FixedPoint::operator< (const unsigned short& data) const {
	// ������
	if (*this == data)
		return false;

	// *this�� -�϶�
	if (not isPositive)
		return true;

	// ���� +�϶�
	if (integerPart >= data)
		return false;				// �����ΰ� ���Ƶ� -5.0�� -5�� �� ���� ������ �Ͼ�� ����
	return true;
}

bool FixedPoint::operator< (const int& data) const {
	// ������
	if (*this == data)
		return false;

	// ��ȣ �� (+<-)
	if (isPositive && data < 0)
		return false;

	// ��ȣ �� (-<+)
	if (not isPositive && data > 0)
		return true;

	// ���� +�϶�
	if (isPositive) {
		if (integerPart >= static_cast<unsigned int>(data))
			return false;			// �����ΰ� ���Ƶ� -5.0�� -5�� �� ���� ������ �Ͼ�� ����
		return true;
	}

	// ���� -�϶�
	if (integerPart >= static_cast<unsigned int>(data) * -1)
		return true;				// �����ΰ� ���Ƶ� -5.0�� -5�� �� ���� ������ �Ͼ�� ����
	return false;
}

bool FixedPoint::operator< (const unsigned int& data) const {
	// ������
	if (*this == data)
		return false;

	// *this�� -�϶�
	if (not isPositive)
		return true;

	// ���� +�϶�
	if (integerPart >= data)
		return false;				// �����ΰ� ���Ƶ� -5.0�� -5�� �� ���� ������ �Ͼ�� ����
	return true;
}

bool FixedPoint::operator<(const FixedPoint& data) const {
	// ������
	if (*this == data)
		return false;

	// ��ȣ �� (+<-)
	if (isPositive && not data.isPositive)
		return false;

	// ��ȣ �� (-<+)
	if (not isPositive && data.isPositive)
		return true;

	// ���� +�϶� (���밪�� ū�� �� ŭ)
	if (isPositive) {
		if (integerPart > data.integerPart)
			return false;
		if (integerPart < data.integerPart)
			return true;

		if (decimalPart > data.decimalPart)
			return false;
		return true;
	}

	// ���� -�϶� (���밪�� ������ �� ŭ)
	if (integerPart > data.integerPart)
		return true;
	if (integerPart < data.integerPart)
		return false;

	if (decimalPart > data.decimalPart)
		return true;
	return false;
}

FixedPoint& FixedPoint::operator=(const short& data) {
	decimalPart = 0;
	if (data < 0) {
		integerPart = data * -1;
		isPositive = false;
	}
	else {
		integerPart = data;
		isPositive = true;
	}
	return *this;
}

FixedPoint& FixedPoint::operator=(const unsigned short& data) {
	decimalPart = 0;
	integerPart = data;
	isPositive = true;
}

FixedPoint& FixedPoint::operator=(const int& data) {
	decimalPart = 0;
	if (data < 0) {
		integerPart = data * -1;
		isPositive = false;
	}
	else {
		integerPart = data;
		isPositive = true;
	}
	return *this;
}

FixedPoint& FixedPoint::operator=(const unsigned int& data) {
	decimalPart = 0;
	integerPart = data;
	isPositive = true;
}

//(��ȿ���� 6�ڸ����� ��ȿ / �Ҽ��� 7�ڸ� ���� ����)
//(��, -2147480000 ���Ͻ� -214748000�� ǥ�� (INT_MIN == -2147483648)
//(��, +2147480000 �̻�� +214748000�� ǥ�� (INT_MAX == +2147483647)

FixedPoint& FixedPoint::operator=(float data) {
	// +2147480000 �̻�� +214748000�� ǥ��
	if (data >= 2147480000) {
		integerPart = 2147480000;
		decimalPart = 0;
		isPositive = true;
		return *this;
	}

	// -2147480000 ���Ͻ� -214748000�� ǥ��
	if (data <= -2147480000) {
		integerPart = 2147480000;
		decimalPart = 0;
		isPositive = false;
		return *this;
	}

	// 0
	if (data == 0) {
		integerPart = 0;
		decimalPart = 0;
		isPositive = true;
	}

	// ���/���� �Ǻ��ؼ� ���
	if (data >= 0) {
		isPositive = true;
	}
	else {
		isPositive = false;
		data *= -1.0f;
	}


	short numDigits = static_cast<short>(log10(data));

	// ���밪 10 �̻� �� ��

	if (numDigits > 0) {
		numDigits++;		// �ڸ��� ǥ���� ���� 1 ����

		data *= powf(10.0f, static_cast<float>(6 - numDigits));
		integerPart = static_cast<unsigned int>(data);
		if (numDigits < 6) {
			decimalPart = integerPart % static_cast<unsigned int>(pow(10, 6 - numDigits));
			integerPart /= static_cast<unsigned int>(pow(10, 6 - numDigits));
			decimalPart *= static_cast<unsigned int>(pow(10, numDigits));
		}
		else {
			integerPart *= static_cast<unsigned int>(pow(10, numDigits - 1));
			decimalPart = 0;
		}

		return *this;
	}


	// ���밪 1 �̻� 10 �̸��� ��

	if (data >= 1) {
		data *= 100000;
		integerPart = static_cast<unsigned int>(data);
		decimalPart = integerPart % 100000;
		integerPart /= 100000;
		decimalPart *= 10;

		return *this;
	}

	// ���밪 1 �̸��� ��

	integerPart = 0;
	decimalPart = static_cast<unsigned int>((data - integerPart) * 1000000.0f);

	if (decimalPart == 0)	// 0�϶� ��ȣ�� +�� �ٲ���
		isPositive = true;

	return *this;
}

//(��ȿ���� 6�ڸ����� ��ȿ / �Ҽ��� 7�ڸ� ���� ����)
//(��, -2147483647 ���Ͻ� -2147483647�� ǥ�� (INT_MIN == -2147483648)
//(��, +2147483647 �̻�� +2147483647�� ǥ�� (INT_MAX == +2147483647)
FixedPoint& FixedPoint::operator=(double data) {
	// +2147483647 �̻�� +2147483647�� ǥ��
	if (data >= 2147483647) {
		integerPart = 2147483647;
		decimalPart = 0;
		isPositive = true;
		return *this;
	}

	// -2147483647 ���Ͻ� -2147483647�� ǥ��
	if (data <= -2147483647) {
		integerPart = -2147483647;
		decimalPart = 0;
		isPositive = false;
		return *this;
	}


	// ���/���� �Ǻ��ؼ� ���
	if (data >= 0) {
		isPositive = true;
	}
	else {
		isPositive = false;
		data *= -1;
	}

	short numDigits = static_cast<short>(log10(data));

	// ���밪 10 �̻� �� ��

	if (numDigits > 0) {
		numDigits++;		// �ڸ��� ǥ���� ���� 1 ����

		data *= pow(10.0, static_cast<double>(6 - numDigits));
		integerPart = static_cast<unsigned int>(data);
		if (numDigits < 6) {
			decimalPart = integerPart % static_cast<unsigned int>(pow(10, 6 - numDigits));
			integerPart /= static_cast<unsigned int>(pow(10, 6 - numDigits));
			decimalPart *= static_cast<unsigned int>(pow(10, numDigits));
		}
		else {
			integerPart *= static_cast<unsigned int>(pow(10, numDigits - 1));
			decimalPart = 0;
		}

		return *this;
	}


	// ���밪 1 �̻� 10 �̸��� ��

	if (data >= 1) {
		data *= 100000;
		std::cout << data << std::endl;
		
		double cuttedIntegerPart;
		modf(data, &cuttedIntegerPart);
		integerPart = static_cast<unsigned int>(cuttedIntegerPart);

		std::cout << integerPart << std::endl;
		decimalPart = integerPart % 100000;
		integerPart /= 100000;
		decimalPart *= 10;

		return *this;
	}

	// ���밪 1 �̸��� ��

	integerPart = 0;
	decimalPart = static_cast<unsigned int>((data - integerPart) * 1000000.0f);

	if (decimalPart == 0)	// 0�϶� ��ȣ�� +�� �ٲ���
		isPositive = true;

	return *this;
}

FixedPoint& FixedPoint::operator=(const FixedPoint& data) {
	integerPart = data.integerPart;
	decimalPart = data.decimalPart;
	isPositive = data.isPositive;

	return *this;
}



bool FixedPoint::operator!() const {
	if (integerPart)
		return true;
	if (decimalPart)
		return true;
}

//=====================================
//�� ��
//=====================================


// Int�� ��ȯ				(�Ҽ��� ���� ����)
int FixedPoint::toInt() const {
	int toIntResult = integerPart;
	if (not isPositive)
		toIntResult *= -1;

	return toIntResult;
}

// UnsignedInt�� ��ȯ		(�Ҽ��� ����/��ȣ(-) ����)
unsigned int FixedPoint::toUnsignedInt() const {
	unsigned int toIntResult = integerPart;
	return toIntResult;
}

// float�� ��ȯ
float FixedPoint::toFloat() const {
	float toFloatResult = integerPart + (static_cast<float>(decimalPart) * 0.000001f);
	if (not isPositive)
		toFloatResult *= -1;
	
	return toFloatResult;
}

// Double�� ��ȯ
double FixedPoint::toDouble() const {
	double toDoubleResult = integerPart + (static_cast<double>(decimalPart) * 0.000001);
	if (not isPositive)
		toDoubleResult *= -1;

	return toDoubleResult;
}

// ���밪 ����
FixedPoint FixedPoint::abc() const {
	return FixedPoint(integerPart, decimalPart, true);
}

// ������ ����
unsigned int FixedPoint::getIntegerPart() const {
	return integerPart;
}


// �Ҽ��� ����
unsigned int FixedPoint::getDecimalPart() const {
	return decimalPart;
}

// ��ȣ ����
bool FixedPoint::getSign() const {
	return isPositive;
}

// ��ȣ ���
char FixedPoint::printSign() const {
	if (isPositive)
		return '+';
	else
		return '-';
}