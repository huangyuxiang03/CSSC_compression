#pragma once
#include<iostream>
#include<cmath>
using namespace std;

template <class T>
class Array
{
private:
	int size;
	int maxsize;
public:
	T* element;
public:
	Array(int maxsize_ = 3)
	{
		size = 0;
		maxsize = maxsize_;
		element = new T[maxsize];
	}
	~Array()
	{
		delete[]element;
	}

	int& operator[](int loc)
	{
		int i;
		i = this->element[loc];
		return i;
	}
	int get_size() { return size; }
	int get_maxsize() { return maxsize; }
	void resize();
	void append(T t);							//增
	void remove(int loc);						//删
	void revise(int loc, T t);					//改
	T	 get_element(int loc);					//查
	void clear();
	void concat(Array<T>* array1, Array<T>* array2, Array<T>*& array3);	//合并两个数组						
};