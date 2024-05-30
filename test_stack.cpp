#include <iostream>
#include "Stack.cpp"
using namespace std;

bool checktest(int *test, int size, int numtest) {
	Sequence<int> *seq_to_stack = new ListSequence<int>(test, size);
	Sequence<int> *seq = new ListSequence<int>(test, size);
	cout << "Test " << numtest << ": " << endl;
	seq->Print();
	cout << endl;
	//seq_to_stack->Print();
	Stack<int> compstack = Stack<int>(seq);
	Stack<int> stack = Stack<int>(seq_to_stack);
	//stack.Print();
	
	bool err = false;
	if (stack.IsEmpty() && seq->GetLength() != 0) {
		cout << "Error in IsEmpty: expected " << bool(seq->GetLength()) << ", actual " << stack.IsEmpty() << endl;
		err = true;
	}
	
	try {										
		if (stack.Top() != seq->GetLast()) {
			cout << "Error in Top: expected " << seq->GetLast() << ", actual " << stack.Top() << endl;
			err = true;
		}
	}
	catch (std::out_of_range) {
		if (size) {
			cout << "Error in Top: unexpected out of range" << endl;
			err = true;
		}
	}
	
	seq->Append(7);
	stack.Push(7);
	size++;
	if (stack != compstack) {
		cout << "Error in Push: expected";
		compstack.Print() ;
		cout << "actual";
		stack.Print(); 
		cout << endl;
		err = true;
	}
	
	seq->Append(123);
	stack.Push(123);
	size++;
	if (stack != compstack) {
		cout << "Error in Push: expected \n" << endl;
		compstack.Print() ;
		cout << "actual \n" << endl;
		stack.Print(); 
		cout << endl;
		err = true;
	}
	
	try {
		if (!size) {
			cout << "Error in Pop: expected out of range" << endl;
		}
		int val = seq->GetLast();
		seq->DeleteAt(seq->GetLength()-1);
		int val2 = stack.Pop();
		if (stack != compstack || val != val2) {
			cout << "Error in Pop: expected" << endl;
			compstack.Print();
			cout << "actual" << endl;
			stack.Print();
			cout << endl;
			err = true;
		}
	}
	catch (std::out_of_range) {
		if (size) {
			cout << "Error in Pop: unexpected out of range" << endl;
			err = true;
		}
	}

	return err;
}

int main() {

	int test1[5]{1, 2, 3, 4, 5};
	int test2[1] {};
	int test3[0] {};
	int test4[20] {-4, 13, 92, 6, 0, 11, -3, 15, 835, -0};
	bool res1 = checktest(test1, 5, 1);
	bool res2 = checktest(test2, 1, 2);
	bool res3 = checktest(test3, 0, 3);
	bool res4 = checktest(test4, 20, 4);
	cout << "All test are checked." << endl;
	if (!(res1 || res2 || res3 || res4)) {
		cout << "Errors not found!" << endl;
	}
	return 0;
}
