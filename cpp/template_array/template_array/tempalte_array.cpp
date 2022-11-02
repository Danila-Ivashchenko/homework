#include "template_array.h"

using namespace std;

template <class T> Array<T>::Array(const int& startCapacity) {
	if (startCapacity <= 0)
		capacity = DEFAULT_CAPACITY;
	else
		capacity = startCapacity;

	ptr = new T[capacity];
	size = 0;
}

template <class T>
Array<T>::Array(const Array& arr) {
	ptr = new int[arr.capacity];
	size = arr.size;
	for (int i = 0; i < size; i++)
		ptr[i] = arr.ptr[i];
}

template <class T>
Array<T>::Array() {
	ptr = new int[DEFAULT_CAPACITY];
	capacity = DEFAULT_CAPACITY;
	size = 0;
}

template <class T>
Array<T>::~Array() {
	delete[] ptr;
}

template<class T>
Array<T>& Array<T>::operator=(const Array& arr)
{
	if (this == &arr)
		return *this;
	if (capacity != arr.capacity){
		delete[] ptr;
		ptr = new int[arr.capacity];
		capacity = arr.capacity;
	}
	size = arr.size;
	for (int i = 0; i < size; i++)
		ptr[i] = arr.ptr[i];
	return *this;
}

template<class T>
T& Array<T>::operator[](int index)
{
	if (index >= size || index < 0) {
		throw ArrayException();
	}
	else
		return ptr[index];
}

template<class T>
void Array<T>::increaseCapacity(int newCapacity) {
	capacity = newCapacity < capacity * 2 ? capacity * 2 : newCapacity;
	int* newPtr = new int[capacity];
	for (int i = 0; i < size; i++)
		newPtr[i] = ptr[i];
	delete[] ptr;
	ptr = newPtr;
}

template<class T>
void Array<T>::insert(int elem, int index)
{
	if (index < 0 || index > size)
		throw ArrayException();
	if (size == capacity)
		increaseCapacity(size + 1);
	for (int j = size - 1; j >= index; j--)
		ptr[j + 1] = ptr[j];
	size++;
	ptr[index] = elem;
}

template<class T>
void Array<T>::insert(int elem)
{
	insert(elem, size);
}

template<class T>
void Array<T>::remove(int index)
{
	if (index < 0 || index >= size)
		throw ArrayException();
	for (int j = index; j < size - 1; j++)
		ptr[j] = ptr[j + 1];
	ptr[size - 1] = 0;
	size--;
}

template<class T>
int Array<T>::getSize() {
	return size;
}

template<class T>
ostream& operator <<(ostream& out, const Array<T>& arr)
{
	out << "Total size: " << arr.size << endl;
	for (int i = 0; i < arr.size; i++)
		out << arr.ptr[i] << endl;
	return out;
}