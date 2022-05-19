#pragma once

#ifndef __ARRAY__
#define __ARRAY__

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
	int get_index(T t);
	void clear();
	void concat(Array<T>* array1, Array<T>* array2, Array<T>*& array3);	//合并两个数组						
};

#endif //!__ARRAY__
//#include "Array.h"


template<class T>
void Array<T>::resize()
{
	if (size >= maxsize)
	{
		T* newarr;
		int new_maxsize = ceil(maxsize + maxsize / 2);
		newarr = new T[new_maxsize];
		for (int i = 0; i < maxsize; i++)
		{
			newarr[i] = element[i];
		}
		delete[]element;
		element = newarr;
		maxsize = new_maxsize;
	}
}

template<class T>
void Array<T>::append(T t)
{
	if (this->size >= this->maxsize)
		this->resize();
	this->element[this->size++] = t;
}

template<class T>
void Array<T>::remove(int loc)
{
	if (loc >= size)
	{
		cout << "Error, out of array valid range!";
		return;
	}
	else
	{
		if (loc = size - 1)
		{
			size--;
		}
		else
		{
			for (int i = loc; i < size - 1; i++)
			{
				element[i] = element[i++];
			}
			size--;
		}
	}
}

template<class T>
void Array<T>::revise(int loc, T t)
{
	if (loc >= size)
	{
		cout << "Error, out of array valid range!";
		return;
	}
	else
	{
		element[loc] = t;
	}
}

template<class T>
T Array<T>::get_element(int loc)
{
	if (loc >= size)
	{
		cout << "Error, out of array valid range!";
		return -1;
	}
	else
	{
		return element[loc];
	}
}

template<class T>
int Array<T>::get_index(T t)
{
	for (int i = 0; i < size ; i++)
	{
		if (element[i] == t) return i;
	}
	return -1;
}

template<class T>
void Array<T>::clear()
{
	size = 0;
	maxsize = 3;
	T* newelement = new T[maxsize];
	delete[]element;
	element = newelement;
}

template<class T>
void Array<T>::concat(Array<T>* array1, Array<T>* array2, Array<T>*& array3)
{
	int m = array1->get_size(), n = array2->get_size();
	if (m == 0 && n == 0)
		return;	//如果都为空，则任意返回一个
	quick_sort(array1->element, 0, m - 1);
	quick_sort(array2->element, 0, n - 1);
	if (m == 0)
		array3 = array2;
	if (n == 0)
		array3 = array1;
	int i = 0, j = 0;
	while (i < m && j < n)
	{
		if (array1->get_element(i) >= array2->get_element(j))
		{
			array3->append(array2->get_element(j));
			j++;
		}
		else
		{
			array3->append(array1->get_element(i));
			i++;
		}
	}
	while (i < m)
	{
		array3->append(array1->get_element(i));
		i++;
	}
	while (j < n)
	{
		array3->append(array2->get_element(j));
		j++;
	}
	//return array3;
}
