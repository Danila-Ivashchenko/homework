#include "LineListElement.h"
#include <iostream>

using namespace std;

#ifndef _LineList_
#define _LineList_

class LineListException {};

template <class T> 
class LineList {
	LineListElement<T>* start;
	//LineList(const LineList& list);
	//LineList& operator =(const LineList& list);
public:
	LineList();
	~LineList();
	LineListElement<T>* getStart();
	void deleteFirst();
	void deleteAfter(LineListElement<T>* ptr);
	void insertFirst(const T& data);
	void insertAfter(LineListElement<T>* ptr, const T& data);
	template <class T> friend ostream& operator <<(ostream& out, LineList& list);
};

// Конструкторы линейного листа


template<class T>
LineList<T>::LineList()
{
	start = 0;
}

// Операции с элементами линейного листа

template <class T>
LineListElement<T>* LineList<T>::getStart() {
	return start;
}

template <class T>
void LineList<T>::insertFirst(const T& data){
	LineListElement<T>* second = start;
	start = new LineListElement<T>(data, second);
}

template <class T>
void LineList<T>::deleteFirst(){
	if (start)
	{
		LineListElement<T>* temp = start->next;
		delete start;
		start = temp;
	}
	else throw LineListException();
}

template <class T>
void LineList<T>::deleteAfter(LineListElement<T>* ptr) {
	if (ptr && ptr->next) {
		LineListElement<T>* temp = ptr->next;
		ptr->next = ptr->next->next;
		delet temp;
	}
	else throw LineListException();
}

template <class T>
void LineList<T>::insertAfter(LineListElement<T>* ptr, const T& data) {
	LineListElement<T>* temp = ptr->next;
	ptr->next = new LineListElement<T>(data, temp);
}

// Деконструктор
template <class T>
LineList<T>::~LineList() {
	while (start) {
		deleteFirst();
	}
}

// Работа с потоками

template <class T>
ostream& operator << (ostream& out, LineList<T>& list){
	LineListElement<T>* ptr = list.start;
	if (!ptr)
		out << "EMPTY ";
	else while (ptr)
	{
		out << ptr->getData() << ' ';
		ptr = ptr->getNext();
	}
	return out;
}

#endif // !_LineList_
