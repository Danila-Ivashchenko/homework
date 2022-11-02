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

};

#endif // !_LINELISTELEMENT_

