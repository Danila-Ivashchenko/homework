#pragma once
#include "LineListElement.h"
#include <iostream>

using namespace std;

#ifndef _LINELIST_CLASS_
#define _LINELIST_CLASS_



class LineListException {};

template <class T>
class LineList {
	LineListElement<T>* start;
	LineListElement<T>* last;
	int size;
public:
	LineList& operator =(const LineList& list);
	LineList(const LineList& list);
	LineList();
	~LineList();
	LineListElement<T>* getStart();
	LineListElement<T>* getLast();
	void deleteFirst();
	void deleteAfter(LineListElement<T>* ptr);
	void deleteByindex(int i);
	void insertFirst(const T& data);
	void insertLast(const T& data);
	void insertAfter(LineListElement<T>* ptr, const T& data);
	void fillList(int n);
	//LineListElement<T>* iosif(int n, int k);
	int getSize();
	LineListElement<T>& operator[](int index);
template <class T> friend ostream& operator << (ostream& out, LineList& list);

};




/* Конструкторы класса */

template <class T>
LineList<T>::LineList() {
	size = 0;
	start = 0;
	last = 0;
}
template <class T>
LineList<T>::LineList(const LineList<T>& list) {
	if (list.size == 0) {
		start = 0;
		size = 0;
		return *this;
	}
	LineListElement<T>* ptr = list.start;
	start = new LineListElement<T>(ptr->getData(), 0);
	size = list.size;
	last = start;
	while (ptr && ptr->getNext())
	{
		ptr = ptr->getNext();
		LineListElement<T>* temp = new LineListElement<T>(ptr->getData(), 0);
		last->next = temp;
		last = last->getNext();
	}
	return *this;
}

template <class T>
LineList<T>& LineList<T>::operator =(const LineList<T>& list) {
	if (list.size == 0) {
		start = 0;
		size = 0;
		return *this;
	}
	LineListElement<T>* ptr = list.start;
	start = new LineListElement<T>(ptr->getData(), 0);
	size = list.size;
	last = start;
	while (ptr && ptr->getNext())
	{
		ptr = ptr->getNext();
		LineListElement<T>* temp = new LineListElement<T>(ptr->getData(), 0);
		last->next = temp;
		last = last->getNext();
	}
	return *this;
}

/* Операции с элементами */

template <class T>
LineListElement<T>* LineList<T>::getStart() {
	if (size != 0) {
		return start;
	}
	else {
		throw LineListException();
	}
}

template <class T>
LineListElement<T>* LineList<T>::getLast() {
	if (size != 0) {
		return last;
	}
	else {
		throw LineListException();
	}
}


template <class T>
void LineList<T>::insertFirst( const T& data)
{
	LineListElement<T>* second = start;
	start = new LineListElement<T>(data, second);
	if (!last)
		last = start;
	size += 1;
}

template <class T>
void LineList<T>::insertLast(const T& data)
{
	if (!start) {
		LineListElement<T>* second = start;
		start = new LineListElement<T>(data, second);
		if (!last)
			last = start;
		size += 1;
	}
	else if (!last) {
		last = start;
		start = new LineListElement<T>(data, last);
		last = start->next;
		size += 1;
	}
	else {
		LineListElement<T>* temp = last->next;
		last->next = new LineListElement<T>(data, temp);
		last = last->next;
		size += 1;
	}
}

template <class T>
void LineList<T>::deleteAfter(LineListElement<T>* ptr) {
	if (ptr && ptr->next) {
		if (ptr == last)
			throw LineListException();
		else {
			LineListElement<T>* temp = ptr->next;
			if (ptr->next == last) {
				ptr->next = 0;
				last = ptr;
			}
			else {
				ptr->next = ptr->next->next;
			}
			delete temp;
			size -= 1;
		}
	}
	else {
		throw LineListException();
	}
}

template<class T>
void LineList<T>::deleteByindex(int i)
{
	if (i == 0) {
		deleteFirst();
	}
	else {
		LineListElement<T>* ptr = start;
		for (int index = 0; index < i - 1; index++, ptr = ptr->getNext()) {
		}
		deleteAfter(ptr);
	}
}

template <class T>
void LineList<T>::insertAfter(LineListElement<T>* ptr, const T& data) {
	if (ptr) {
		LineListElement<T>* temp = ptr->next;
		ptr->next = new LineListElement<T>(data, temp);
		if (ptr == last) {
			last = last->next;
		}
		size += 1;
	}
	else throw LineListException();
}


template <class T>
void LineList<T>::deleteFirst() {
	if (start) {
		LineListElement<T>* temp = start->getNext();
		delete start;
		start = temp;
		size -= 1;
	}
	else throw LineListException();
}

template<class T>
LineListElement<T>& LineList<T>::operator[](int index)
{
	//if (size <= index)
	//	throw LineListException();
	LineListElement<T>* ptr = start;
	for (int i = 0; i < index + 1; i++, ptr = ptr->getNext()) {
		if (i == index)
			return *ptr;
	}	
}

/* Деконструктор */

template <class T>
LineList<T>::~LineList() {
	while (start)
		deleteFirst();
}

/* Прочии функции */

template <class T>
ostream& operator<<(ostream& out, LineList<T>& list)
{
	
	if (list.getSize() == 0)
		out << "EMPTY ";
	else {
		LineListElement<T>* ptr = list.getStart();
		while (ptr)
		{
			out << ptr->getData() << ' ';
			ptr = ptr->getNext();
		}
	}
	return out;
}

template <class T>
int LineList<T>::getSize() {
	return size;
}

template <class T>
void LineList<T>::fillList(int n) {
	while (start) {
		deleteFirst();
	}
	for (int i = 0; i < n; i++)
		insertLast(i + 1);
}

//template<class T>
//LineListElement<T>* LineList<T>::iosif(int n, int k){
//	if (size != n)
//		fillList(n);
//	LineListElement<T>* temp = start; // текущий элемент дял удаления элемента за ним
//	int pos_c = 0; // текущая позиция
//	int pos = 0;
//	
//
//	while (size != 1) {
//		pos = (pos + k - 1) % size;
//		if (pos <= pos_c) {
//			pos_c = 0;
//			temp = start;
//		}
//		for (int i = pos_c; pos_c < pos - 1; i++) {
//			if (temp == last) {
//				temp = start;
//				pos_c = 0;
//			}
//			else {
//				temp = temp->next;
//				pos_c += 1;
//			}
//		}
//		if (pos == 0) {
//			deleteFirst();
//			temp = start;
//			pos_c = 0;
//		}
//		else
//			deleteAfter(temp);
//		
//	}
//	return start;
//}


#endif // !_LINELIST_CLASS_