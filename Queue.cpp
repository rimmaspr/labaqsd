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
class Queue
{
protected:
	int last{-1};
	Sequence<T> *elems{};
public:
	Queue() {
		elems = new ListSequence<T>();
	}
	Queue(Sequence<T> *seq) {
		last = seq->GetLength()-1;
		elems = seq;
	}
	
	~Queue() {
		elems->Delete();
		delete elems;
	}
	
	bool IsEmpty() {
		if (last == -1) {
			return true;
		}
		return false;
	}
	
	void Enqueue(T elem) {
		elems->Append(elem);
		last++;
	}

	int GetLength() {
		return last + 1;
	}
	T Get(int index) {
		return elems->Get(index);
	}

	T Top() {
		if (this->IsEmpty()) {
			throw std::out_of_range("Queue is empty");
		}
		//cout << "(top = " << top << ")" << endl;
		return elems->Get(0);
	}
	
	T Dequeue() {
		if (this->IsEmpty()) {
			throw std::out_of_range("Queue is empty");
		}
		T first = elems->Get(0);
		elems->DeleteAt(0);
		last--;
		return first;
	}
	void Concat(const Queue<T> &queue) {
		elems->Concat(queue.elems);
		last += queue.elems->GetLength();
	}
	
	Queue<T>* GetSubQueue(int start, int end) {
		Queue<T> *newqueue = new Queue<T>(this->elems->GetSubsequence(start, end));
		return newqueue;
	}
	
	int SearchSubQueue(const Queue<T> &queue) {
		if (queue.last == -1) {
			throw std::invalid_argument("Queue you are trying to find is empty.");
		}
		int index{-1}, count{};
		for (int i = 0; i <= last; i++) {
			if (elems->Get(i) != queue.elems->Get(count)) {
				count = 0;
			}
			else if (count == queue.last) {
				index = i - count;
				break;
			}
			else {
				count++;
			}
		}
		return index;
	}
	
	void Print() {
		if (last == -1) {
			std::cout << "empty" << std::endl;
		} else {
		elems->Print();
		}
	}
	
	bool operator==(Queue<T> &queue) {
		/*
		if (this->last != queue.last) {
			return false;
		}*/
		if (!(*(this->elems) == *(queue.elems))) {
			return false;
		}
		return true;
	}
	bool operator!=(Queue<T> &queue) {
		return !(*this == queue);
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
	Queue<int> queue = Queue<int>(seq);

	delete [] arr;
	
	int count2;
	cout << "enter count of elems:" << endl;
	count2 = getint();
		
	int* arr2 = new int[count2]{};
	cout << "enter elems" << endl;
	for (int i = 0; i < count2; i++) {
		arr2[i] = getint();
	}
	Sequence<int> *seq2 = new ArraySequence<int>(arr2, count2);
	Queue<int> queue2 = Queue<int>(seq2);
	delete [] arr2;
	if (queue != queue2) {
		cout << "not equal" << endl;
	}
	else cout << " equal" << endl;
}
*/
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
	Queue<int> queue = Queue<int>(seq);

	delete [] arr;
	Queue<int>* newqueue{};
		
	bool flag = 1;
	while(flag) {
		int choise;
		cout << "\n1 - check empty\n2 - enqueue\n3 - get first\n4 - dequeue\n5 - concat\n6 - get sub queue\n7 - search sub queue\n8 - print queue\n0 - exit" << endl;
		choise = getchoise(0, 8);
		switch (choise) {
		case 0:
			flag = 0;
			break;
		case 1:
			if (queue.IsEmpty()) {
				cout << "queue is empty"<< endl;
			}
			else {
				cout << "queue is not empty" << endl;
			}
			break;
		case 2:
			int elem;
			cout << "enter elem" << endl;
			elem = getint();
			queue.Enqueue(elem);
			cout << "elem has been added" << endl;
			break;
		case 3:
			cout << "top elem: " << queue.Top() << endl;
				break;
		case 4:
			cout << "elem: " << queue.Dequeue() << endl;
			break;
		case 5:
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
				Queue<int> q2 = Queue<int>(seq2);
				queue.Concat(q2);
				delete [] a;
				//seq2->Delete();
			}
			cout << "queues are concatenated" << endl;
			break;
		case 6:
			int start, end;
			cout << "enter start index: ";
			start = getint();
			cout << "enter end index: ";
			end = getint();
			newqueue = queue.GetSubQueue(start, end);
			cout << "sub queue: " << endl;
			(*newqueue).Print();
			break;
		case 7:
			cout << "enter count of elems of queue you want to search" << endl;
			count = getint();
			int index;
			{
				int* array = new int[count]{};
				cout << "enter elems" << endl;
				for (int i = 0; i < count; i++) {
					array[i] = getint();
				}
				Sequence<int> *seq2 = new ArraySequence<int>(array, count);
				Queue<int> st2 = Queue<int>(seq2);
				index = queue.SearchSubQueue(st2);
				delete [] array;
			}
			if (index == -1) {
				cout << "subqueue is not found" << endl;
				break;
			}
			cout << "subqueue is found, it starts at index " << index << endl;
			break;
		case 8:
			queue.Print();
			break;
		}	
	}
	
	delete newqueue;
	return 0;
}
*/
