#pragma once


class MyDoubleVector {
public:

	MyDoubleVector(size_t init_capacity = Default_Capacity);
	MyDoubleVector(const MyDoubleVector& v);
	~MyDoubleVector();

	//Operators;
	MyDoubleVector& operator=(const MyDoubleVector& v);
	void operator+=(const MyDoubleVector& v);
	double& operator[] (size_t index);
	MyDoubleVector operator+(const MyDoubleVector& v);
	MyDoubleVector operator-(const MyDoubleVector& v);
	double operator*(const MyDoubleVector& v);
	MyDoubleVector operator-();//unary
	bool operator==(const MyDoubleVector& v);
	void operator()(double x);//벡터의 요소들을 모두 x로 변경

							  //Member functions;
	void pop_back();
	void push_back(double x);
	size_t capacity() const;
	size_t size() const;
	void reserve(size_t n);
	bool empty() const;
	void clear();


private:
	static const size_t Default_Capacity = 100;
	double *data;
	size_t capacity_v;
	size_t used;
};