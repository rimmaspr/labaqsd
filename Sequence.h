#pragma once

#include <iostream>
#include "dynamicArray.h"
#include "linkedList.h"

using namespace std;

template <class T> class ArraySequence;
template <class T> class ListSequence;

template <class T> 
class Sequence
{
public:
	virtual T GetFirst() = 0;
	virtual T GetLast() = 0;
	virtual T Get(int index) = 0;
	virtual int GetLength() = 0;
	
	virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) = 0;
	
	virtual void Append(T item) = 0;
	virtual void Prepend(T item) = 0;
	virtual void InsertAt(T item, int index) = 0;
	
	virtual Sequence<T>* ImmutableAppend(T item) = 0;
	virtual Sequence<T>* ImmutablePrepend(T item) = 0;
	virtual Sequence<T>* ImmutableInsertAt(T item, int index) = 0;
	
	virtual void Concat(Sequence<T> *seq) = 0;
	virtual Sequence<T>* ImmutableConcat(Sequence<T> *seq) = 0;
	
	virtual void Print() = 0;
	
	virtual void DeleteAt(int index) = 0;
	virtual void Delete() = 0;
	virtual void Sort() = 0;
	
	virtual bool operator==(Sequence<T> &seq) {
		if (this->GetLength() != seq.GetLength()) {
			return false;
		}
		for (int i = 0; i < this->GetLength(); i++) {
			if (this->Get(i) != seq.Get(i)) { 
				return false;
			}
		}
		return true;
	}
	
	virtual T operator [](int index) {
		return this->Get(index);
	}
	
	virtual void operator +(Sequence<T> *seq) {
		this->Concat(seq);
	}
	/*
	virtual void operator=(ArraySequence<T> &seq) = 0;
	virtual void operator=(ListSequence<T> &seq) = 0;
	*/
};


template <class T> 
class ArraySequence: public Sequence<T>
{
private:
	DynamicArray<T>* elems = NULL;
public:
	ArraySequence(T* items, int count) : elems(new DynamicArray<T>(items, count)) {} 
	ArraySequence() : elems(new DynamicArray<T>(0)) {}
	ArraySequence(const ArraySequence<T> &arr) : elems(new DynamicArray<T>(*(arr.elems))) {}
	
	virtual ~ArraySequence() {
		delete elems;
	}
	virtual void Delete() override {
		delete elems;
	}

	virtual T GetFirst() override {
		return this->elems->Get(0);;
	}
	virtual T GetLast() override {
		return this->elems->Get(this->elems->GetSize()-1);;
	}		
	virtual T Get(int index) override {
		return this->elems->Get(index);
	}
	virtual int GetLength() override {
		return this->elems->GetSize();
	}
	
	virtual void Append(T item) override {
		this->elems->Resize(this->elems->GetSize()+1);
		this->elems->Set(this->elems->GetSize()-1, item);
	}
	virtual void Prepend(T item) override {
		this->elems->Resize(this->elems->GetSize()+1);
		for (int i = this->GetLength()-1; i > 0; i--) {
			this->elems->Set(i, this->elems->Get(i-1));
		}
		this->elems->Set(0, item);
	}
	virtual void InsertAt(T item, int index) override {
		if (index < 0 || index > this->elems->GetSize()) {
			throw std::out_of_range("Index is out of range.");
		}
		this->elems->Resize(this->elems->GetSize()+1);
		for (int i = this->elems->GetSize()-1; i > index; i--) {
			this->elems->Set(i, this->elems->Get(i-1));
		}
		this->elems->Set(index, item);
	}
	
	virtual ArraySequence<T>* ImmutableAppend(T item) override {
		ArraySequence<T> *newsequence = new ArraySequence(*this);
		newsequence->Append(item);
		return newsequence;
	}
	virtual ArraySequence<T>* ImmutablePrepend(T item) override {
		ArraySequence<T> *newsequence = new ArraySequence(*this);
		newsequence->Prepend(item);
		return newsequence;
	}
	virtual ArraySequence<T>* ImmutableInsertAt(T item, int index) override {
		ArraySequence<T> *newsequence = new ArraySequence(*this);
		newsequence->InsertAt(item, index);
		return newsequence;
	}
	
	virtual void Print() override {
		this->elems->Print();
	}
	
	virtual ArraySequence<T>* GetSubsequence(int startIndex, int endIndex) override {
		if (startIndex < 0 || startIndex >= this->elems->GetSize() || endIndex < 0 || endIndex >= this->elems->GetSize()) {
			throw std::out_of_range("Index is out of range.");
		}
		if (startIndex > endIndex) {
			throw std::invalid_argument("The start index must be less than the end index");
		}
		
		int subsize = endIndex - startIndex + 1;
		int items[subsize];
		
		for (int i = startIndex; i <= endIndex; i++) {
			items[i - startIndex] = this->elems->Get(i);
		}
		ArraySequence<T> *subseq = new ArraySequence<T>(items, subsize);
		return subseq;
	}
	
	virtual void Concat(Sequence<T> *seq) override {
		if (!(seq->GetLength())) return;
		
		for (int i = 0; i < seq->GetLength(); i++) {
			this->Append(seq->Get(i));
		}
	}
	virtual ArraySequence<T>* ImmutableConcat(Sequence<T> *seq) override {
		ArraySequence<T> *newsequence = new ArraySequence(*this);
		newsequence->Concat(seq);
		return newsequence;
	}
	
	virtual void DeleteAt(int index) override {
		this->elems->DeleteAt(index);
	}
	virtual void Sort() override {
		this->elems->Sort();
	}
};

template <class T> 
class ListSequence : public Sequence<T>
{
private: 
	LinkedList<T>* elems;
public:
	ListSequence(T* items, int count) : elems(new LinkedList<T>(items, count)) {}
	ListSequence() : elems(new LinkedList<T>()) {}
	ListSequence(const ListSequence<T> &list) : elems(new LinkedList<T>(*(list.elems))) {}
	ListSequence(const LinkedList<T> &list) : elems(new LinkedList<T>(list)) {}
	
	virtual ~ListSequence() {
		delete elems;
	}
	virtual void Delete() override {
		delete elems;
	}
	
	virtual T GetFirst() override {
		return this->elems->GetFirst();
	}
	virtual T GetLast() override {
		return this->elems->GetLast();
	}
	virtual T Get(int index) override {
		return this->elems->Get(index);
	}
	virtual T GetLength() override {
		return this->elems->GetLength();
	}
	
	virtual ListSequence<T>* GetSubsequence(int startIndex, int endIndex) override {
		LinkedList<T>* sublist = this->elems->GetSubList(startIndex, endIndex);
		ListSequence<T>* subseq = new ListSequence(*sublist);
		delete sublist;
		return subseq;
	}
	
	virtual void Append(T item) override {
		this->elems->Append(item);	
	}
	virtual void Prepend(T item) override {
		this->elems->Prepend(item);
	}
	virtual void InsertAt(T item, int index) override {
		this->elems->InsertAt(item, index);
	}
	
	virtual ListSequence<T>* ImmutableAppend(T item) override {
		ListSequence<T> *newsequence = new ListSequence(*(this->elems));
		newsequence->Append(item);
		return newsequence;
	}
	virtual ListSequence<T>* ImmutablePrepend(T item) override {
		ListSequence<T> *newsequence = new ListSequence(*(this->elems));
		newsequence->Prepend(item);
		return newsequence;
	}
	virtual ListSequence<T>* ImmutableInsertAt(T item, int index) override {
		ListSequence<T> *newsequence = new ListSequence(*(this->elems));
		newsequence->InsertAt(item, index);
		return newsequence;
	}
	
	virtual void Concat(Sequence<T> *seq) {
		for (int i = 0; i < seq->GetLength(); i++) {
			this->Append(seq->Get(i));
		}
	}
	virtual ListSequence<T>* ImmutableConcat(Sequence<T> *seq) override {
		ListSequence<T> *newsequence = new ListSequence(*(this->elems));
		newsequence->Concat(seq);
		return newsequence;
	}
	
	virtual void Print() override {
		this->elems->Print();
	}
	
	virtual void DeleteAt(int index) override {
		this->elems->DeleteAt(index);
	}
	virtual void Sort() override {
		this->elems->Sort();
	}
};
