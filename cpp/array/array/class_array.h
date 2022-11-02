#include <iostream>

#ifndef _CLASS_ARRAY_
#define _CLASS_ARRAY_

using namespace std;

const int DEFAULT_CAPACITY = 10;
class ArrayException {};

class Array {
	int* ptr;
	int size, capacity;
	void increaseCapacity(int newCapacity);
public:
	Array(const int& startCapacity);
	Array(const Array& arr);
	Array();
	~Array();

	Array& operator =(const Array& arr);

	int getSize();
	int& operator [] (int index);
	void insert(int elem, int index);
	void insert(int elem);
	void remove(int index);

	friend ostream& operator <<(ostream& out, const Array& arr);

};


#endif // !_CLASS_ARRAY_
