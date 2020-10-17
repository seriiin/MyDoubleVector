#include <iostream>
#include "MyDoubleVector.h"
#include <cstdlib>
#include <algorithm>
#include <cassert>

using namespace std;

MyDoubleVector::MyDoubleVector(size_t init_capacity) {
	//Postcondition : MyDoubleVector는 초기화 되어야함
	data = new double[init_capacity];
	capacity_v = init_capacity;
	used = 0;
}

MyDoubleVector::MyDoubleVector(const MyDoubleVector& v) {
	////Postcondition : Deep Copy로 벡터 생성
	data = new double[v.capacity_v];
	capacity_v = v.capacity_v;
	used = v.used;
	copy(v.data, v.data + used, data);
}

MyDoubleVector::~MyDoubleVector() {
	//Postcondition : 메모리 반환
	delete[] data;
}

//Operators;
MyDoubleVector& MyDoubleVector:: operator=(const MyDoubleVector& v) {
	//Postcondition : LHS에 RHS값을 저장 

	if (*this == v)		//기존의 벡터와 벡터 v가 같은지 확인
		return *this;	//같다면 기존 객체 반환

//벡터 v과 같은 크기의 객체를 생성한 후 대입
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
	//기존 벡터의 사이즈와 새로 덧붙일 벡터의 사이즈를 더한 값이 
	//기존벡터의 크기보다 클 경우 증가
	if (used + v.used > capacity_v)
		reserve(used + v.used);
	copy(v.data, v.data + v.used, data + used);
	used = used + v.used;
}

double& MyDoubleVector:: operator[] (size_t index) {
	//Precondition : index가 접근 가능한 영역이어야한다(0보다 크거나 같고, used보다 작아야함)
	//Postcondition : 해당되는 index의 element의 값을 반환한다.
	assert(used > index);

	return data[index];
}

MyDoubleVector MyDoubleVector:: operator+(const MyDoubleVector& v) {
	//Precondition : size가 같지 않으면, 종료
	//Postcondition : 두벡터를 '+'연산처리한 객체 반환
	assert(used == v.used);
	MyDoubleVector ret(*this);
	for (int i = 0; i < used; i++)
		ret.data[i] = data[i] + v.data[i];
	return ret;
}

MyDoubleVector MyDoubleVector:: operator-(const MyDoubleVector& v) {
	//Precondition : size가 같지 않으면, 종료
	//Postcondition : 두벡터를 '-'연산처리한 객체 반환
	assert(used == v.used);
	MyDoubleVector ret(*this);
	for (int i = 0; i < used; i++)
		ret.data[i] = data[i] - v.data[i];
	return ret;
}

double MyDoubleVector::operator*(const MyDoubleVector& v) {
	//Precondition : size가 같지 않으면, 종료
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
	//Postcondition : vector의 모든 element들의 값에 '-'부호가 붙는다
	//Postcondition : 벡터의 부호를'-'연산처리한 객체 반환
	MyDoubleVector ret(*this);
	for (int i = 0; i < used; ++i)
		ret.data[i] = -(data[i]);
	return ret;
}

bool MyDoubleVector :: operator==(const MyDoubleVector& v) {
	//Precondition : 객체 비교
	//Postcondition : 두 vector의 모든 element를 비교하여 모두 같은 경우에만 true return
	if (size() != v.size()) 
		return false;
	else {
		for (int i = 0; i < this->size(); i++)
			if (data[i] != v.data[i]) return false;
		return true;
	}
}

void MyDoubleVector::operator()(double x) {
	//Precondition : doble형의 값을 입력
	//Postcondition : vector의 모든 element에 x값 대입
	for (int i = 0; i < used; ++i)
		data[i] = x;
}


//Member functions;
void MyDoubleVector::pop_back() {
	//Postcondition :vector의 마직막 element를 제거
	if (empty()) return;
	--used;
}

void MyDoubleVector::push_back(double x) {
	//Precondition : double형 변수대입
	//Postcondition : vector의 마지막 요소 뒤에 x를 추가
	if (used == capacity_v)
		reserve(used + 1);
	data[used++] = x;
}

size_t MyDoubleVector::capacity() const {
	//Postcondition : 사용가능한 vector의 크기
	return capacity_v;
}
size_t MyDoubleVector::size() const {
	//Postcondition : 사용된 vector의 크기
	return used;
}

void MyDoubleVector::reserve(size_t n) {
	//Precondition : vector에 할당할 사이즈를 입력
	//Postcondition : 입력된 n으로 vector의 capcity를 조절
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
	//Postcondition : vector가 비어있는지 확인
	if (size() == 0)
		return true;
	else
		return false;
}

void MyDoubleVector::clear() {
	//Postcondition : 사용된 vector를 0으로 만들어줌
	used = 0;
}