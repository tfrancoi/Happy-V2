/*
 * Node.cpp
 *
 *  Created on: 27-mai-2009
 *      Author: mythrys
 */

#include "Node.h"
#include <cstdlib>

template <class T>
Node<T>::Node(T* element) {
	this->element = element;
	this->next = NULL;
}

template <class T>
Node<T>::Node(T* element, Node* next) {
	this->element = element;
	this->next = next;
}



template <class T>
void Node<T>::setNext(Node* next) {
	this->next = next;
}

template <class T>
T* Node<T>::getElement() {
	return element;
}

template <class T>
void Node<T>::setElement(T* element) {
	this->element = element;
}

template <class T>
Node<T>::~Node() {
	delete this->next;
}

template <class T>
Node<T>* Node<T>::getNext() {
	return this->next;
}
