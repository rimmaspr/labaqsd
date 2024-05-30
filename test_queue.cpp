#include <iostream>
#include "Queue.cpp"
using namespace std;

bool checktest(int *test, int size, int numtest) {
	Sequence<int> *seq_to_stack = new ListSequence<int>(test, size);
	Sequence<int> *seq = new ListSequence<int>(test, size);
	cout << "Test " << numtest << ": " << endl;
	seq->Print();
	cout << endl;
	//seq_to_stack->Print();
	Queue<int> compqueue = Queue<int>(seq);
	Queue<int> queue = Queue<int>(seq_to_stack);
	//stack.Print();
	
	bool err = false;
	if (queue.IsEmpty() && seq->GetLength() != 0) {
		cout << "Error in IsEmpty: expected " << bool(seq->GetLength()) << ", actual " << queue.IsEmpty() << endl;
		err = true;
	}
	
	seq->Append(7);
	queue.Enqueue(7);
	size++;
	if (queue != compqueue) {
		cout << "Error in Enqueue: expected\n";
		compqueue.Print() ;
		cout << "actual";
		queue.Print(); 
		cout << endl;
		err = true;
	}
	
	seq->Append(123);
	queue.Enqueue(123);
	size++;
	if (queue != compqueue) {
		cout << "Error in Enqueue: expected \n" << endl;
		compqueue.Print() ;
		cout << "actual \n" << endl;
		queue.Print(); 
		cout << endl;
		err = true;
	}
	
	try {
		if (!size) {
			cout << "Error in Dequeue: expected out of range" << endl;
		}
		int val = seq->GetFirst();
		seq->DeleteAt(0);
		int val2 = queue.Dequeue();
		if (queue != compqueue || val != val2) {
			cout << "Error in Dequeue: expected" << endl;
			compqueue.Print();
			cout << "actual" << endl;
			queue.Print();
			cout << endl;
			err = true;
		}
	}
	catch (std::out_of_range) {
		if (size) {
			cout << "Error in Dequeue: unexpected out of range" << endl;
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
