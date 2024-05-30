//#include <iostream>
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
class Stack 
{
protected:
	int top{-1};
	Sequence<T> *elems{};
public:
	Stack() {  }
	Stack(Sequence<T> *seq) {
		top = seq->GetLength()-1;
		elems = seq;
	}
	
	~Stack() {
		elems->Delete();
		delete elems;
	}
	
	bool IsEmpty() {
		if (top == -1) {
			return true;
		}
		return false;
	}
	
	int GetLength() {
		return top + 1;
	}	
	
	void Push(T elem) {
		elems->Append(elem);
		top++;
	}
	
	T Top() {
		if (this->IsEmpty()) {
			throw std::out_of_range("Stack is empty");
		}
		return elems->Get(top);
	}
	
	T Pop() {
		if (this->IsEmpty()) {
			throw std::out_of_range("Stack is empty");
		}
		T last = elems->Get(top);
		elems->DeleteAt(top);
		top--;
		return last;
	}
	void Concat(const Stack<T> &stack) {
		elems->Concat(stack.elems);
		top += stack.elems->GetLength();
	}
	
	Stack<T>* GetSubstack(int start, int end) {
		Stack<T> *newstack = new Stack<T>(this->elems->GetSubsequence(start, end));
		return newstack;
	}
	
	int SearchSubstack(const Stack<T> &stack) {
		if (stack.top == -1) {
			throw std::invalid_argument("Stack you are trying to find is empty.");
		}
		int index{-1}, count{};
		for (int i = 0; i <= top; i++) {
			if (elems->Get(i) != stack.elems->Get(count)) {
				count = 0;
			}
			else if (count == stack.top) {
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
		elems->Print();
		cout << "Top: " << top << endl;
	}
	
	bool operator==(Stack<T> &stack) {
		/*
		if (this->top != stack.top) {
			return false;
		}
		*/
		if (!(*(this->elems) == *(stack.elems))) {
			return false;
		}
		return true;
	}
	bool operator!=(Stack<T> &stack) {
		return !(*this == stack);
	}
};

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
	Stack<int> stack = Stack<int>(seq);

	delete [] arr;
	Stack<int>* newstack{};
		
	bool flag = 1;
	while(flag) {
		int choise;
		cout << "\n1 - check empty\n2 - push\n3 - get last\n4 - pop\n5 - concat\n6 - get sub stack\n7 - search sub stack\n8 - print stack\n0 - exit" << endl;
		choise = getchoise(0, 11);
		switch (choise) {
		case 0:
			flag = 0;
			break;
		case 1:
			if (stack.IsEmpty()) {
				cout << "stack is empty"<< endl;
			}
			else {
				cout << "stack is not empty" << endl;
			}
			break;
		case 2:
			int elem;
			cout << "enter elem" << endl;
			elem = getint();
			stack.Push(elem);
			cout << "elem has been added" << endl;
			break;
		case 3:
			cout << "top elem: " << stack.Top() << endl;
				break;
		case 4:
			cout << "elem: " << stack.Pop() << endl;
			break;
		case 5:
			int count;
			cout << "enter count of elems of stack you want to add:" << endl;
			count = getint();
			{
				int* a = new int[count]{};
				cout << "enter elems" << endl;
				for (int i = 0; i < count; i++) {
					a[i] = getint();
				}
				Sequence<int> *seq2 = new ArraySequence<int>(a, count);
				Stack<int> st2 = Stack<int>(seq2);
				stack.Concat(st2);
				delete [] a;
			}
			cout << "stacks are concatenated" << endl;
			break;
		case 6:
			int start, end;
			cout << "enter start index: ";
			start = getint();
			cout << "enter end index: ";
			end = getint();
			newstack = stack.GetSubstack(start, end);
			cout << "sub stack: " << endl;
			(*newstack).Print();
			break;
		case 7:
			cout << "enter count of elems of stack you want to search" << endl;
			count = getint();
			int index;
			{
				int* array = new int[count]{};
				cout << "enter elems" << endl;
				for (int i = 0; i < count; i++) {
					array[i] = getint();
				}
				Sequence<int> *seq2 = new ArraySequence<int>(array, count);
				Stack<int> st2 = Stack<int>(seq2);
				index = stack.SearchSubstack(st2);
				delete [] array;
			}
			if (index == -1) {
				cout << "stack is not found" << endl;
				break;
			}
			cout << "stack is found, it starts at index " << index << endl;
			break;
		case 8:
			stack.Print();
			break;
		}	
	}
	
	delete newstack;
	return 0;
}

