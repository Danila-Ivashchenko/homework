#include "LineList.h"
#include <iostream>
#include <chrono>

using namespace std;

int iosif(const int& n, const int& k) {
	LineList <int> a;
	a.fillList(n);

	LineListElement<int>* temp = a.getStart(); // текущий элемент дял удаления элемента за ним
	int pos_c = 0; // текущая позиция
	int pos = 0;


	while (a.getSize() != 1) {
		pos = (pos + k - 1) % a.getSize();
		if (pos <= pos_c) {
			pos_c = 0;
			temp = a.getStart();
		}
		for (int i = pos_c; pos_c < pos - 1; i++) {
			if (temp == a.getLast()) {
				temp = a.getStart();
				pos_c = 0;
			}
			else {
				temp = temp->getNext();
				pos_c += 1;
			}
		}
		if (pos == 0) {
			a.deleteFirst();
			temp = a.getStart();
			pos_c = 0;
		}
		else
			a.deleteAfter(temp);

	}
	return a.getStart()->getData();

}

int main()
{

    int n = 1000, k = 2;
   
    //for (int i = 0; i < 7; i++) {
    //     LineList <int> a;
    //     if (i > 0) {
    //         if (i % 2 == 0)
    //             n *= 2;
    //         else
    //             n *= 5;
    //     };
    //     double start = clock();
    //     /*a.fillList(n);
    //     cout << "n = " << n << ", answer = " << *a.iosif(n, k) << ", time = " << (clock() - start) / 1000 << endl;
    //     start = clock();*/
    //     cout << "n = " << n << ", answer = " << iosif(n, k) << ", time = " << (clock() - start) / 1000 << endl;
    // }

	LineList <char> a;
	a.insertFirst('s');

	cout << *a.getStart() << " = *" << a.getStart() << " " << &*a.getStart();






    return 0;
}