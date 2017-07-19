/*
 * singleLinkedList.h
 *
 *  Created on: Jun 27, 2017
 *  Author: Anand Kulkarni
 *  Email: anand.kulkarni.sg@gmail.com
 *
 */

#ifndef SINGLELINKEDLIST_H_
#define SINGLELINKEDLIST_H_

#include<iostream>
#include<string>

using namespace std;

// The basic Node of the singleLinkedList<T> i.e singleLinkedListNode<T> below.

template<typename T> class SingleLinkedListNode {

private:
	T _datum;
	SingleLinkedListNode<T>* _next;

public:
	SingleLinkedListNode();
	void setData(T data);
	void setNext(SingleLinkedListNode<T>*);
	T getData();
	SingleLinkedListNode<T>* getNext();
};

template<typename T> SingleLinkedListNode<T>::SingleLinkedListNode() {
	_datum = static_cast<T>(NULL);
	_next = nullptr;
}

template<typename T> void SingleLinkedListNode<T>::setData(T datum) {
	_datum = datum;
}

template<typename T> void SingleLinkedListNode<T>::setNext(SingleLinkedListNode<T>* next) {
	_next = next;
}

template<typename T> T SingleLinkedListNode<T>::getData() {
	return _datum;
}

template<typename T> SingleLinkedListNode<T>* SingleLinkedListNode<T>::getNext() {
	return _next;
}

// The singleLinkedList<T> implementation is below.

template<typename T> class SingleLinkedList {

private:
	SingleLinkedListNode<T>* _head;
	long _size;

public:
	SingleLinkedList<T>();
	void insert(T);
	void remove(T);
	void print();
	SingleLinkedListNode<T>* getNodeByVal(T);
	bool deleteNode(SingleLinkedListNode<T>*, bool);
	void swapItems(SingleLinkedListNode<T>*, SingleLinkedListNode<T>*);
	~SingleLinkedList<T>();
	long size();

};

template<typename T> SingleLinkedList<T>::SingleLinkedList() {
	_head = nullptr;
	_size = 0;
}

template<typename T> void SingleLinkedList<T>::insert(T datum) {

	SingleLinkedListNode<T>* newNode = new SingleLinkedListNode<T>();
	newNode->setData(datum);
	newNode->setNext(nullptr);
	SingleLinkedListNode<T>* temp = _head;
	if (temp != nullptr) {
		while (temp->getNext() != nullptr) {
			temp = temp->getNext();
		}
		temp->setNext(newNode);
	} else {
		_head = newNode;
	}
	++_size;
}

template<typename T> void SingleLinkedList<T>::remove(T datum) {

	bool isFound = false;
	// Case 1 : empty LinkedList.
	if (_head == nullptr || _size == 0)
		return;

	// Case 2 : Head is the item to be removed.
	SingleLinkedListNode<T>* iterator = _head;
	if (iterator->getData() == datum) {
		_head = iterator->getNext();
		delete iterator;
		--_size;
		return;
	}

	// Case 3 : item is found either in middle or at end.
	SingleLinkedListNode<T>* prev;
	while (iterator->getNext() != nullptr) {
		prev = iterator;
		iterator = iterator->getNext();
		if (iterator->getData() == datum) {
			isFound = true;
			break;
		}
	}

	if (isFound) {
		prev->setNext(iterator->getNext());
		delete iterator;
		--_size;
	}
}

template<typename T> void SingleLinkedList<T>::print() {

	SingleLinkedListNode<T>* iterator = _head;
	while (iterator != nullptr) {
		cout << iterator->getData() << "-->";
		iterator = iterator->getNext();
	}
	cout << "nullptr" << endl;
}

template<typename T> long SingleLinkedList<T>::size() {
	return _size;
}

template<typename T> SingleLinkedListNode<T>* SingleLinkedList<T>::getNodeByVal(T datum) {

	SingleLinkedListNode<T>* iterator = _head;

	// Check if the linkedList contains any valid data. else return nullptr.
	if (_size == 0 || _head == nullptr)
		return (nullptr);

	// Case 1: If the datum is the head then return it.
	if (_head->getData() == datum)
		return (_head);

	// Case 2: If the list has more than one item.
	while (iterator->getNext() != nullptr) {
		if (iterator->getData() == datum) {
			return (iterator);
		}
		iterator = iterator->getNext();
	}

	// Case 3: Edge case when last item.
	if (iterator->getData() == datum) {
		return (iterator);
	} else {
		return (nullptr);
	}
}

template<typename T> bool SingleLinkedList<T>::deleteNode(SingleLinkedListNode<T>* node, bool forceMode) {

	bool isDeleted = false;

	// Case 1: The linkedList is empty.
	// Case 1: Edge Case: If a nullptr is pased return.
	if (_head == nullptr || _size == 0 || node == nullptr)
		return (isDeleted);

	// Case 2: The linkedList has some data. set the iterator to the node data passed
	SingleLinkedListNode<T>* iterator = node;

	// If this item is the last item then do not delete it but set it to nullptr.
	// This does not work if the item is at the end of the List.
	// This algorithm cant work on the edge case. so return a warning.

	if (iterator->getNext() == nullptr) {
		if (!forceMode) {
			cout << "Warning : This method does not work if the item is at the end of the LinkedList" << endl;
			cout << "Warning : since forceMode is not set will skip deletion" << endl;
		} else {

			// Now we are being asked to delete the item at the end. To accomplish this we need to manually find the previous item.
			cout << "Warning : attempting a search for previous item [ costly lookup mode ] since forceMode is on" << endl;

			// Case 1: Only one item is left and hence the head is itself the last item.
			if (_head == iterator) {
				delete iterator;
				_head = nullptr;
				--_size;
				if (_size != 0) {
					cout
							<< "Fatal Error: possible implementation issue with linkedList. head is pointing to nullptr with size not equal to zero.Please investigate"
							<< endl;
				}
				isDeleted = true;
				return (isDeleted);
			}

			SingleLinkedListNode<T>* previousIterator = _head;
			// Case 2: More than one item is present in the linked List.
			while (previousIterator->getNext() != iterator && previousIterator->getNext() != nullptr) {
				previousIterator = previousIterator->getNext();
			}
			// Now the previousIterator is at previous position pointing to iterator item. Terminate the previousIterator by setting its next to nullptr.
			// delete the iterator item.
			previousIterator->setNext(nullptr);
			delete iterator;
			isDeleted=true;
		}
		return (isDeleted);
	}

	// If the item is in the middle somewhere and has a next item then below case.
	if (iterator->getNext() != nullptr) {
		SingleLinkedListNode<T>* next = iterator->getNext();
		iterator->setData(next->getData());
		iterator->setNext(next->getNext());
		delete next; // Because the iterator itself has assumed the face of next item. so next is not needed.
		isDeleted = true;
		--_size;
		return (isDeleted);
	}

	return (isDeleted);
}

// Swap Two items given on the LinkedList.

template<typename T> void SingleLinkedList<T>::swapItems(SingleLinkedListNode<T>* node1, SingleLinkedListNode<T>* node2) {

	// We have no business if the linkedList is empty.
	if (_head == nullptr || _size == 0)
		return;

	// swap the items only if both are valid [ that means size must be greater than 1 ]
	if (node1 != nullptr && node2 != nullptr && _size > 1) {
		T datum = node1->getData();
		node1->setData(node2->getData());
		node2->setData(datum);
	}
}

template<typename T> SingleLinkedList<T>::~SingleLinkedList() {

	SingleLinkedListNode<T>* iterator = _head;
	while (iterator != nullptr) {
		SingleLinkedListNode<T>* next = iterator->getNext();
		delete iterator;
		iterator = next;
	}
}

#endif /* SINGLELINKEDLIST_H_ */
