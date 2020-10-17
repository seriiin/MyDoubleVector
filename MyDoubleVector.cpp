#include <iostream>
#include "MyDoubleVector.h"
#include <cstdlib>
#include <algorithm>
#include <cassert>

using namespace std;

MyDoubleVector::MyDoubleVector(size_t init_capacity) {
	//Postcondition : MyDoubleVector�� �ʱ�ȭ �Ǿ����
	data = new double[init_capacity];
	capacity_v = init_capacity;
	used = 0;
}

MyDoubleVector::MyDoubleVector(const MyDoubleVector& v) {
	////Postcondition : Deep Copy�� ���� ����
	data = new double[v.capacity_v];
	capacity_v = v.capacity_v;
	used = v.used;
	copy(v.data, v.data + used, data);
}

MyDoubleVector::~MyDoubleVector() {
	//Postcondition : �޸� ��ȯ
	delete[] data;
}

//Operators;
MyDoubleVector& MyDoubleVector:: operator=(const MyDoubleVector& v) {
	//Postcondition : LHS�� RHS���� ���� 

	if (*this == v)		//������ ���Ϳ� ���� v�� ������ Ȯ��
		return *this;	//���ٸ� ���� ��ü ��ȯ

//���� v�� ���� ũ���� ��ü�� ������ �� ����
	if (capacity_v != v.capacity_v) {
		delete[] data;
		data = new double[v.capacity_v];
		capacity_v = v.capacity_v;
	}

	used = v.used;
	copy(v.data, v.data + used, data);
	return *this;
}

void MyDoubleVector::operator+=(const MyDoubleVector& v) {
	//���� ������ ������� ���� ������ ������ ����� ���� ���� 
	//���������� ũ�⺸�� Ŭ ��� ����
	if (used + v.used > capacity_v)
		reserve(used + v.used);
	copy(v.data, v.data + v.used, data + used);
	used = used + v.used;
}

double& MyDoubleVector:: operator[] (size_t index) {
	//Precondition : index�� ���� ������ �����̾���Ѵ�(0���� ũ�ų� ����, used���� �۾ƾ���)
	//Postcondition : �ش�Ǵ� index�� element�� ���� ��ȯ�Ѵ�.
	assert(used > index);

	return data[index];
}

MyDoubleVector MyDoubleVector:: operator+(const MyDoubleVector& v) {
	//Precondition : size�� ���� ������, ����
	//Postcondition : �κ��͸� '+'����ó���� ��ü ��ȯ
	assert(used == v.used);
	MyDoubleVector ret(*this);
	for (int i = 0; i < used; i++)
		ret.data[i] = data[i] + v.data[i];
	return ret;
}

MyDoubleVector MyDoubleVector:: operator-(const MyDoubleVector& v) {
	//Precondition : size�� ���� ������, ����
	//Postcondition : �κ��͸� '-'����ó���� ��ü ��ȯ
	assert(used == v.used);
	MyDoubleVector ret(*this);
	for (int i = 0; i < used; i++)
		ret.data[i] = data[i] - v.data[i];
	return ret;
}

double MyDoubleVector::operator*(const MyDoubleVector& v) {
	//Precondition : size�� ���� ������, ����
	MyDoubleVector answer(*this);
	double result_value = 0.0;
	if (answer.size() == v.size())
	{
		for (int i = 0; i < answer.size(); i++)
			answer.data[i] *= v.data[i];
		for (int i = 0; i < answer.size(); i++)
			result_value += answer.data[i];
	}
	else
		exit(1);
	return result_value;
}

MyDoubleVector MyDoubleVector :: operator-() {
	//Postcondition : vector�� ��� element���� ���� '-'��ȣ�� �ٴ´�
	//Postcondition : ������ ��ȣ��'-'����ó���� ��ü ��ȯ
	MyDoubleVector ret(*this);
	for (int i = 0; i < used; ++i)
		ret.data[i] = -(data[i]);
	return ret;
}

bool MyDoubleVector :: operator==(const MyDoubleVector& v) {
	//Precondition : ��ü ��
	//Postcondition : �� vector�� ��� element�� ���Ͽ� ��� ���� ��쿡�� true return
	if (size() != v.size()) 
		return false;
	else {
		for (int i = 0; i < this->size(); i++)
			if (data[i] != v.data[i]) return false;
		return true;
	}
}

void MyDoubleVector::operator()(double x) {
	//Precondition : doble���� ���� �Է�
	//Postcondition : vector�� ��� element�� x�� ����
	for (int i = 0; i < used; ++i)
		data[i] = x;
}


//Member functions;
void MyDoubleVector::pop_back() {
	//Postcondition :vector�� ������ element�� ����
	if (empty()) return;
	--used;
}

void MyDoubleVector::push_back(double x) {
	//Precondition : double�� ��������
	//Postcondition : vector�� ������ ��� �ڿ� x�� �߰�
	if (used == capacity_v)
		reserve(used + 1);
	data[used++] = x;
}

size_t MyDoubleVector::capacity() const {
	//Postcondition : ��밡���� vector�� ũ��
	return capacity_v;
}
size_t MyDoubleVector::size() const {
	//Postcondition : ���� vector�� ũ��
	return used;
}

void MyDoubleVector::reserve(size_t n) {
	//Precondition : vector�� �Ҵ��� ����� �Է�
	//Postcondition : �Էµ� n���� vector�� capcity�� ����
	double* large_vector;
	if (n == capacity_v)
		return;
	assert(n >= used);
	large_vector = new double[n];
	copy(data, data + used, large_vector);
	delete[] data;
	data = large_vector;
	capacity_v = n;
}

bool MyDoubleVector::empty() const {
	//Postcondition : vector�� ����ִ��� Ȯ��
	if (size() == 0)
		return true;
	else
		return false;
}

void MyDoubleVector::clear() {
	//Postcondition : ���� vector�� 0���� �������
	used = 0;
}