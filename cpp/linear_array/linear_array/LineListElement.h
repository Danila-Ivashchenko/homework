//#include "LineList.h"

#ifndef _LINELISTELEMENT_
#define _LINELISTELEMENT_

template <class T>
class LineListElement {
	private:
		T value;
		LineListElement* next;
	public:
		LineListElement(const T& data, LineListElement* anext);
		const T& getData() const;
		LineListElement* getNext();

		template <class T> friend class LineList;
};

template <class T>
LineListElement<T>::LineListElement(const T& adata, LineListElement<T>* anext){
	data = adata;
	next = anext;
}

template <class T>
LineListElement<T>* LineListElement<T>::getNext()
{
	return next;
}


#endif // !_LINELISTELEMENT_

