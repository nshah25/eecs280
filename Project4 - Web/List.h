#ifndef LIST_H
#define LIST_H
//List.h
//
// doubly-linked, double-ended list with Iterator interface
// Project UID c1f28c309e55405daf00c565d57ff9ad
// EECS 280 Project 4

#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL


template <typename T>
class List {
	//OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:

	//EFFECTS:  returns true if the list is empty
	bool empty() const
	{
		if (first == nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	//EFFECTS: returns the number of elements in this List
	int size() const
	{
		int size = 0;
		for (Node* p = first; p; p = p->next)
		{
			size++;
		}
		return size;
	}

	//REQUIRES: list is not empty
	//EFFECTS: Returns the first element in the list by reference
	T& front()
	{
		return first->datum;
	}


	//REQUIRES: list is not empty
	//EFFECTS: Returns the last element in the list by reference
	T& back()
	{
		return last->datum;
	}

	//EFFECTS:  inserts datum into the front of the list
	void push_front(const T& datum)
	{
		if (empty() == true)
		{
			Node* firstNode = new Node;
			firstNode->datum = datum;
			first = firstNode;
			last = firstNode;
			first->next = nullptr;
			first->prev = nullptr;
		}
		else
		{
			Node* firstNode = new Node;
			firstNode->datum = datum;
			firstNode->next = first;
			firstNode->prev = nullptr;
			first = firstNode;
			first->next->prev = first;
		}
	}

	//EFFECTS:  inserts datum into the back of the list
	void push_back(const T& datum)
	{
		if (empty() == true)
		{
			Node* firstNode = new Node;
			firstNode->datum = datum;
			first = firstNode;
			last = firstNode;
			first->next = nullptr;
			first->prev = nullptr;
		}
		else
		{
			Node* lastNode = new Node;
			lastNode->datum = datum;
			lastNode->prev = last;
			lastNode->next = nullptr; 
			last = lastNode;
			last->prev->next = last;
		}
	}

	//REQUIRES: list is not empty
	//MODIFIES: may invalidate list iterators
	//EFFECTS:  removes the item at the front of the list
	void pop_front()
	{
		Node* tobeDeleted = first;
		first = first->next;

		if (first != nullptr)
		{
			first->prev = nullptr;
		}

		delete tobeDeleted;
	}

	//REQUIRES: list is not empty
	//MODIFIES: may invalidate list iterators
	//EFFECTS:  removes the item at the back of the list
	void pop_back()
	{
		if(last->prev == nullptr)
		{
			Node* tobeDeleted = first;
			first = first->next;
			delete tobeDeleted;
		}
		else
		{
			Node* tobeDeleted = last;
			last->prev->next = nullptr;
			last = last->prev;

			delete tobeDeleted;
		}
	}

	//MODIFIES: may invalidate list iterators
	//EFFECTS:  removes all items from the list
	void clear()
	{
		while (empty() != true)
		{
			pop_front();
		}
	}

	// You should add in a default constructor, destructor, copy constructor,
	// and overloaded assignment operator, if appropriate. If these operations
	// will work correctly without defining these, you can omit them. A user
	// of the class must be able to create, copy, assign, and destroy Lists
	List()
		: first(nullptr), last(nullptr) {}

	List(const List<T>& other)
		: first(nullptr), last(nullptr)
	{
		copy_all(other);
	}

	~List()
	{
		while (empty() == false)
		{
			pop_front();
		}
	}

	List& operator=(const List<T>& other)
	{
		if (this != &other)
		{
			clear();
			copy_all(other);
			return *this;
		}
		else
		{
			return *this;
		}
	}
private:
	//a private type
	struct Node {
		Node* next;
		Node* prev;
		T datum;
	};

	//REQUIRES: list is empty
	//EFFECTS:  copies all nodes from other to this
	void copy_all(const List& other)
	{
		for (Node* p = other.first; p; p = p->next)
		{
			push_back(p->datum);
		}
	}

	Node* first;   // points to first Node in list, or nullptr if list is empty
	Node* last;    // points to last Node in list, or nullptr if list is empty

public:
	////////////////////////////////////////
	class Iterator {
		//OVERVIEW: Iterator interface to List

		// You should add in a default constructor, destructor, copy constructor,
		// and overloaded assignment operator, if appropriate. If these operations
		// will work correctly without defining these, you can omit them. A user
		// of the class must be able to create, copy, assign, and destroy Iterators.

		// Your iterator should implement the following public operators: *,
		// ++ (prefix), default constructor, == and !=.

	public:
		// This operator will be used to test your code. Do not modify it.
		// Requires that the current element is dereferenceable.
		Iterator& operator--()
		{
			assert(node_ptr);
			node_ptr = node_ptr->prev;
			return *this;
		}

		T& operator *() const
		{
			return node_ptr->datum;
		}

		Iterator& operator++()
		{
			node_ptr = node_ptr->next;
			return *this;
		}

		Iterator()
			: node_ptr(nullptr) {}

		bool operator==(const Iterator other) const
		{
			if (node_ptr == other.node_ptr)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		bool operator!=(const Iterator other)  const
		{
			if (node_ptr == other.node_ptr)
			{
				return false;
			}
			else
			{
				return true;
			}
		}

	private:
		Node* node_ptr; //current Iterator position is a List node
		// add any additional necessary member variables here

		// add any friend declarations here
		friend class List;
		// construct an Iterator at a specific position
		Iterator(Node* p)
			: node_ptr(p) {}

	};//List::Iterator
	////////////////////////////////////////

	// return an Iterator pointing to the first element
	Iterator begin() const
	{
		return Iterator(first);
	}

	// return an Iterator pointing to "past the end"
	Iterator end() const
	{
		return Iterator();
	}

	//REQUIRES: i is a valid, dereferenceable iterator associated with this list
	//MODIFIES: may invalidate other list iterators
	//EFFECTS: Removes a single element from the list container
	void erase(Iterator i)
	{
		if (i.node_ptr == last)
		{
			pop_back();
		}
		else if (i == begin())
		{
			pop_front();
		}
		else
		{
			i.node_ptr->prev->next = i.node_ptr->next;
			i.node_ptr->next->prev = i.node_ptr->prev;
			delete i.node_ptr;
		}
	}

	//REQUIRES: i is a valid iterator associated with this list
	//EFFECTS: inserts datum before the element at the specified position.
	void insert(Iterator i, const T& datum)
	{
		if (i == end())
		{
			push_back(datum);
		}
		else if (i == begin())
		{
			push_front(datum);
		}
		else
		{
			Node* newNode = new Node;
			newNode->datum = datum;
			newNode->prev = i.node_ptr;
			newNode->next = i.node_ptr->next;
			newNode->next->prev = newNode;
			newNode->prev->next = newNode;
		}
	}

};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.

#endif // Do not remove this. Write all your code above this line.