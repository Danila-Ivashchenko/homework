#include <iostream>

#ifndef _TEMPLATE_ARRAY_
#define _TEMPLATE_ARRAY_

using namespace std;

const int DEFAULT_CAPACITY = 10;
class ArrayException {};

template <class T> class Array {
	T* ptr;
	int size, capacity;
	int getSize();
public:
	Array(const int& startCapacity);
	Array(const Array& arr);
	Array();
	~Array();

	Array<T>& operator =(const Array& arr);

	T& operator [] (int index);
	void increaseCapacity(int newCapacity);
	void insert(int elem, int index);
	void insert(int elem);
	void remove(int index);

	template <class T> friend ostream& operator <<(ostream& out, const Array<T>& arr);

};


#endif // !_TEMPLATE_ARRAY_

