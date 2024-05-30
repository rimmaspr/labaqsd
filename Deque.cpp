#include <iostream>
#include "Sequence.h"

int getint() {
	int value{};
	int scanf_value{};
	scanf_value = scanf("%d", &value);
	
	if (!scanf_value) {	
		std::cout << "Invalid input. Try again: ";
		scanf("%*[^\n]");
		return getint();
	}
	return value;
}

int getchoise(int minval, int maxval) {
	int choise{};
	choise = getint();
	if (choise < minval || choise > maxval) {
		std::cout << "Invalid input. Enter number from " << minval << " to " << maxval << ": ";
		return getchoise(minval, maxval);
	}
	return choise;
}

template <class T>
class Deque
{
protected:
	int last{-1};
	Sequence<T> *elems{};
public:
	Deque() {  }
	Deque(Sequence<T> *seq) {
		last = seq->GetLength()-1;
		elems = seq;
	}
	
	~Deque() {
		elems->Delete();
		delete elems;
	}
	
	bool IsEmpty() {
		if (last == -1) {
			return true;
		}
		return false;
	}
	
	void Append(T elem) {
		elems->Append(elem);
		last++;
	}
	void Prepend(T elem) {
		elems->Prepend(elem);
		last++;
	}
	
	T CheckFirst() {
		if (this->IsEmpty()) {
			throw std::out_of_range("Deque is empty");
		}
		return elems->Get(0);
	}
	T CheckLast() {
		if (this->IsEmpty()) {
			throw std::out_of_range("Deque is empty");
		}
		return elems->Get(last);
	}
	
	T DeleteFirst() {
		if (this->IsEmpty()) {
			throw std::out_of_range("Deque is empty");
		}
		T first = elems->Get(0);
		elems->DeleteAt(0);
		last--;
		return first;
	}
	
	T DeleteLast() {
		if (this->IsEmpty()) {
			throw std::out_of_range("Deque is empty");
		}
		T first = elems->Get(last);
		elems->DeleteAt(last);
		last--;
		return first;
	}
	
	void Concat(const Deque<T> &deq) {
		elems->Concat(deq.elems);
		last += deq.elems->GetLength();
	}
	
	Deque<T>* GetSubQueue(int start, int end) {
		Deque<T> *newdeq = new Deque<T>(this->elems->GetSubsequence(start, end));
		return newdeq;
	}
	
	int SearchSubDeque(const Deque<T> &deque) {
		if (deque.last == -1) {
			throw std::invalid_argument("Deque you are trying to find is empty.");
		}
		int index{-1}, count{};
		for (int i = 0; i <= last; i++) {
			if (elems->Get(i) != deque.elems->Get(count)) {
				count = 0;
			}
			else if (count == deque.last) {
				index = i - count;
				break;
			}
			else {
				count++;
			}
		}
		return index;
	}
	
	void Sort() {
		elems->Sort();
	}
	
	void Print() {
		elems->Print();
		cout << "Last: " << last << endl;
	}
	
	bool operator==(Deque<T> &deque) {
		/*
		if (this->last != deque.last) {
			return false;
		}
		*/
		if (!(*(this->elems) == *(deque.elems))) {
			return false;
		}
		return true;
	}
	bool operator!=(Deque<T> &deque) {
		return !(*this == deque);
	}
};

/*
int main() {
	int count;
	cout << "enter count of elems:" << endl;
	count = getint();
		
	int* arr = new int[count]{};
	cout << "enter elems" << endl;
	for (int i = 0; i < count; i++) {
		arr[i] = getint();
	}
	Sequence<int> *seq = new ArraySequence<int>(arr, count);
	Deque<int> deque = Deque<int>(seq);

	delete [] arr;
	Deque<int>* newdeque{};
		
	bool flag = 1;
	while(flag) {
		int choise;
		cout << "\n1 - check empty\n2 - check first\n3 - check last\n4 - append elem\n5 - prepend elem\n6 - delete first\n7 - delete last\n8 - concat\n9 - get sub deque\n10 - search sub deque\n11 - print deque\n12 - sort deque\n0 - exit" << endl;
		choise = getchoise(0, 12);
		switch (choise) {
		case 0:
			flag = 0;
			break;
		case 1:
			if (deque.IsEmpty()) {
				cout << "deque is empty"<< endl;
			}
			else {
				cout << "deque is not empty" << endl;
			}
			break;
		case 2:
			cout << "first elem: " << deque.CheckFirst() << endl;
			break;
		case 3:
			cout << "last elem: " << deque.CheckLast() << endl;
				break;
		case 4:
			int elem4;
			cout << "enter elem" << endl;
			elem4 = getint();
			deque.Append(elem4);
			cout << "elem has been added to the end" << endl;
			break;
		case 5:
			int elem5;
			cout << "enter elem" << endl;
			elem5 = getint();
			deque.Prepend(elem5);
			cout << "elem has been added to the beginning" << endl;
			break;
		case 6:
			cout << "first elem has been deleted: " << deque.DeleteFirst() << endl;
				break;
		case 7:
			cout << "last elem has been deleted: " << deque.DeleteLast() << endl;
				break;
		case 8:
			int count;
			cout << "enter count of elems of queue you want to add:" << endl;
			count = getint();
			{
				int* a = new int[count]{};
				cout << "enter elems" << endl;
				for (int i = 0; i < count; i++) {
					a[i] = getint();
				}
				Sequence<int> *seq2 = new ArraySequence<int>(a, count);
				Deque<int> q2 = Deque<int>(seq2);
				deque.Concat(q2);
				delete [] a;
			}
			cout << "deques are concatenated" << endl;
			break;
		case 9:
			int start, end;
			cout << "enter start index: ";
			start = getint();
			cout << "enter end index: ";
			end = getint();
			newdeque = deque.GetSubQueue(start, end);
			cout << "sub deque: " << endl;
			(*newdeque).Print();
			break;
		case 10:
			cout << "enter count of elems of deque you want to search" << endl;
			count = getint();
			int index;
			{
				int* array = new int[count]{};
				cout << "enter elems" << endl;
				for (int i = 0; i < count; i++) {
					array[i] = getint();
				}
				Sequence<int> *seq2 = new ArraySequence<int>(array, count);
				Deque <int> deq2 = Deque<int>(seq2);
				index = deque.SearchSubDeque(deq2);
				delete [] array;
			}
			if (index == -1) {
				cout << "subdeque is not found" << endl;
				break;
			}
			cout << "subdeque is found, it starts at index " << index << endl;
			break;
		case 11:
			deque.Print();
			break;
		case 12:
			deque.Sort();
			cout << "deque is sorted" << endl;
		}	
	}
	
	delete newdeque;
	return 0;
}
*/
