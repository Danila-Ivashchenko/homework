#pragma once
#include "LineList.h"
#include <iostream>

using namespace std;

#ifndef _LINELISTELEMENT_
#define _LINELISTELEMENT_

template <class T>
class LineListElement {
private:
	T data;
	LineListElement* next;
public:
	LineListElement(const T& adata, LineListElement* anext);
	const T& getData() const;
	LineListElement* getNext();

template <class T> friend class LineList;
template <class T> friend ostream& operator << (ostream& out, LineListElement& elem);
};

template <class T>
LineListElement<T>::LineListElement(const T& adata, LineListElement* anext) {
	data = adata;
	next = anext;
}

template<class T>
const T& LineListElement<T>::getData() const
{
	return data;
}


template<class T>
LineListElement<T>* LineListElement<T>::getNext()
{
	return next;
}

template<class T>
ostream& operator<<(ostream& out, LineListElement<T>& elem)
{
	out << elem.getData();
	return out;
}


#endif // !_LINELISTELEMENT_
