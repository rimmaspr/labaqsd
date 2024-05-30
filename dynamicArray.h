#pragma once

template <class T> class DynamicArray {
//public:
private: 	
	T* elems;
	int size;
	
public:
	DynamicArray() 
	{
		size = 0;
		elems = NULL;
	}
	
	DynamicArray(T* items, int count)
	{
		if (count < 0) {
			throw std::out_of_range("Size is less than zero.");
		}
		size = count;
		if (count) {
			elems = new T[count]{};
		}
		else {
			elems = NULL;
		}
		
		for (int i = 0; i < count; i++) {
			elems[i] = items[i];
		}
	}
	
	DynamicArray(const DynamicArray<T> &dynamicArray)
	{   
		size = dynamicArray.size;
		elems = new T[size]{};
		
		for (int i = 0; i < size; i++) {
			elems[i] = dynamicArray.elems[i];
		}
	}
	
	DynamicArray(int count)
	{   
		if (count < 0) {
			throw std::out_of_range("Size is less than zero.");
		}
		size = count;

		if (size) {
			elems = new T[count]{};
		}
		else {
			elems = NULL;
		}
	}

	~DynamicArray()
	{
		delete [] elems;
	}
	
	void Delete() {
		delete [] elems;
	}
	
	T Get(int index) {
		if (index < 0 || index >= size) {
			throw std::out_of_range("Index is out of range.");
		}
		return elems[index];
	}
	
	int GetSize() {
		return size;
	}
	
	void Print() {
		if (!size) {
			std::cout << "empty" << std::endl;
			return;
		}
		std::cout << "Elements: ";
		for (int i = 0; i < size; i++) {
			std::cout << elems[i] << " ";
		}
		std::cout << "\nSize: " << size << std::endl;
	}
	
	void Set(int index, T value) {
		if (index < 0 || index >= size) {
			throw std::out_of_range("Index is out of range.");
		}
		elems[index] = value;
	}
	
	void Resize(int newSize) {
		if (newSize < 0) {
			throw std::out_of_range("Size is less than zero.");
		}
		
		T* hlp{};
		hlp = new T[newSize]{};
		
		int copies{};
		if (newSize > size) {
			copies = size;
		}
		else {
			copies = newSize;
		}
			
		size = newSize;
			
		for (int i = 0; i < copies; i++) {
			hlp[i] = elems[i];
		}
		delete [] elems;
		
		elems = new T[newSize]{};

		for (int i = 0; i < copies; i++) {
			elems[i] = hlp[i];
		}
		delete [] hlp;
	}
	
	void Equate(const DynamicArray<T> &dynamicArray) {
		if (size) {
			delete [] elems;
		}
		size = dynamicArray.size;
		elems = new T[size]{};
		
		for (int i = 0; i < size; i++) {
			elems[i] = dynamicArray.elems[i];
		}
	}
	
	void DeleteAt(int index) {
        if (!size) {
        	throw std::out_of_range("Array is empty.");
        }
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range.");
        }
        
        T* hlp = new T[size-1]{};
        for (int i = 0; i < index; i++) {
            hlp[i] = elems[i];
        }
        for (int i = index+1; i < size; i++) {
            hlp[i-1] = elems[i];
        }
        
        delete [] elems;
        elems = hlp;
        size--;
    }
    
    void Sort() {
		for (int i = 0; i < size - 1; i++) {
		    for (int j = 0; j < size - i - 1; j++) {
		        if (elems[j] > elems[j + 1]) {
		            T temp = elems[j];
		            elems[j] = elems[j + 1];
		            elems[j + 1] = temp;
		        }
		    }
		}
	}
};
