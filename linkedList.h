#pragma once

template <class T> class LinkedList;

template <class T> 
class Node
{
	friend class LinkedList<T>;
private:
	T field;			
	class Node<T> *next;	
};

template <class T> 
class LinkedList
{	
protected:
	Node<T> *head;		
	int size{};			
	
public:
	LinkedList() {
		head = NULL;
		size = 0;
	}
	LinkedList(T* items, int count)
	{
		size = count;
		if (!count) {
			head = NULL;
			return;
		}
		head = new Node<T>;
		
		head->field = items[0];
		Node<T> *before = head;
		for (int i = 1; i < count; i++) {
			Node<T> *ptr{};
			try {
				ptr = new Node<T>;
			}
			catch (std::bad_alloc) {
				std::cout << "Error allocation memory." << std::endl;
				return;
			}
			ptr->field = items[i];
			before->next = ptr;
			before = ptr;
		}
	}
	
	LinkedList<T>(const LinkedList<T> &list)
	{   
		size = list.size;
		head = new Node<T>;
		Node<T> *listptr = list.head;
		head->field = listptr->field;
		Node<T> *before = head;
		for (int i = 1; i < list.size; i++) {
			listptr = listptr->next;
			Node<T> *ptr{};
			ptr = new Node<T>;
			ptr->field = listptr->field;
			before->next = ptr;
			before = ptr;
		}
	}
	
	~LinkedList()
	{
		Node<T> *ptr1 = head;
		Node<T> *ptr2 = NULL;
		for (int i = 0; i < size; i++) {
			ptr2 = ptr1->next;
			delete ptr1;
			ptr1 = ptr2;
		}
	}
	
	void Delete() {
		Node<T> *ptr1 = head;
		Node<T> *ptr2 = NULL;
		for (int i = 0; i < size; i++) {
			ptr2 = ptr1->next;
			delete ptr1;
			ptr1 = ptr2;
		}
	}
	
	T GetFirst() {
		if (!size) {
			throw std::out_of_range("List is empty.");
		}
		return head->field;
	}
	
	T GetLast() {
		if (!size) {
			throw std::out_of_range("List is empty.");
		}
		Node<T> *ptr{head};
		for (int i = 0; i < size-1; i++) {
			ptr = ptr->next;
		}
		return ptr->field;
	}
	
	T Get(int index) {
		if (index < 0 || index >= size) {
			throw std::out_of_range("Index is out of range.");
		}
		Node<T> *ptr{head};
		for (int i = 0; i < index; i++) {
			ptr = ptr->next;
		}
		return ptr->field;
	}
	
	LinkedList<T>* GetSubList(int startIndex, int endIndex) {//список элтов
		if (startIndex < 0 || startIndex >= size || endIndex < 0 || endIndex >= size) {
			throw std::out_of_range("Index is out of range.");
		}
		if (startIndex > endIndex) {
			throw std::invalid_argument("The start index must be less than the end index");
		}
		
		Node<T> *ptr{head};
		int subsize = endIndex - startIndex + 1;
		int elems[subsize];
		
		for (int i = 0; i < startIndex; i++)
			ptr = ptr->next;
		
		for (int i = startIndex; i < endIndex; i++) {
			elems[i - startIndex] = ptr->field;
			ptr = ptr->next;
		}
		elems[endIndex-startIndex] = ptr->field;
		LinkedList<T> *sublist = new LinkedList<T>(elems, subsize);
		return sublist;
	}
	
	int GetLength() {			
		return size;
	}
	
	void Append(T item) {
		if (size) {
			Node<T> *ptr{head};
			for (int i = 0; i < size-1; i++) {
				ptr = ptr->next;
			}
			Node<T> *last{};
			last = new Node<T>;
		
			ptr->next = last;
			last->field = item;
		}
		else {
			head = new Node<T>;
			head->field = item;
		}
		size++;
	}
	
	void Prepend(T item) {
		Node<T> *elem{};
		elem = new Node<T>;
		elem->field = item;
		if (!size) {
			elem->next = NULL;
			head = elem;
		}
		else {
			elem->next = head;
			head = elem;
		}
		size++;
	}
	
	void InsertAt(T item, int index) {
		if (index < 0 || index > size) {
			throw std::out_of_range("Index is out of range.");
			return;
		}
		if (!size || !index) {
			Prepend(item);
			return;
		}
		
		else {
			Node<T> *elem{};
			elem = new Node<T>;
			
			Node<T> *ptr{head};
			for (int i = 0; i < index-1; i++) {
				ptr = ptr->next;
			}
			Node<T> *ptr2{ptr->next};
			ptr->next = elem;
			elem->field = item;
			elem->next = ptr2;
			size++;
		}
	}
	
	void Concat(LinkedList<T> list) {
		Node<T> *ptr = list.head;
		for (int i = 0; i < list.size; i++) {
			this->Append(ptr->field);
			ptr = ptr->next;
		}
		
	}

	void Print() {
		if (!head) {
			std::cout << "empty" << std::endl;
			return;
		}
		Node<T> *ptr{head};
		std::cout << "Elements: ";
		for (int i = 0; i < size; i++) {
			std::cout << ptr->field << " ";
			ptr = ptr->next;
		}
		std::cout << "\nSize: " << size << std::endl;
	}

	void Equate(const LinkedList<T> &list) {
		if (size) {
			Delete();
		}
		size = list.size;
		head = new Node<T>;
		Node<T> *listptr = list.head;
		head->field = listptr->field;
		Node<T> *before = head;
		for (int i = 1; i < list.size; i++) {
			listptr = listptr->next;
			Node<T> *ptr{};
			ptr = new Node<T>;
			ptr->field = listptr->field;
			before->next = ptr;
			before = ptr;
		}
	}
	
	void DeleteAt(int index) {
        if (!size) {
			throw std::out_of_range("List is empty.");
		}	
		if (index < 0 || index >= size) {
			throw std::out_of_range("Index is out of range");
		}
		
		size--;
        Node<T> *current{head};
        if (!index) {
            head = head->next;
            delete current;
            return;
        }

        for (int i = 0; i < index-1; i++) {
            current = current->next;
        }

        Node<T> *nodeToDelete{current->next};
        
        if (index != size) {
        	current->next = nodeToDelete->next;
        }
        else {
        	current->next = NULL;
        }
        
        delete nodeToDelete;
	}
	
	void Swap(int index1, int index2) {
        if (index1 < 0 || index1 >= size || index2 < 0 || index2 >= size) {
            std::cout << "Index is out of range." << std::endl;
            return;
        }

        if (index1 == index2) {
            return;
        }

        Node<T>* Node1 = head;
        for (int i = 0; i < index1; i++) {
            Node1 = Node1->next;
        }

        Node<T>* Node2 = head;
        for (int i = 0; i < index2; i++) {
            Node2 = Node2->next;
        }

        T temp = Node1->field;
        Node1->field = Node2->field;
        Node2->field = temp;
	}
	
	void Sort() {
		for (int i = 0; i < size - 1; i++) {
		    for (int j = 0; j < size - i - 1; j++) {
		        if (this->Get(j) > this->Get(j + 1)) {
		            Swap(j, j+1);
		        }
		    }
		}
	}
};
