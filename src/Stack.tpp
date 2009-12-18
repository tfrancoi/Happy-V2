/*
 * Stack.cpp
 *
 *  Created on: 27-mai-2009
 *      Author: mythrys
 */

#include "Stack.h"
#include <cstdlib>


template <class I>
Stack<I>::Stack() {
	this->first = NULL;

}

template <class I>
Stack<I>::~Stack() {
	delete this->first;
}

template <class I>
bool Stack<I>::isEmpty() {
	return this->first == NULL;
}

template <class I>
I* Stack<I>::pop() {
	if(this->isEmpty()) {
		return NULL;
	}
	I* item = this->first->getElement();
	this->first = this->first->getNext();
	return item;
}

template <class I>
void Stack<I>::push(I* element) {
	Node<I>* n = new Node<I>(element, this->first);
	this->first = n;
}

template <class I>
void clearStack(Stack<I>* s) {
	while(!s->isEmpty()) {
		I* item = s->pop();
		delete item;
	}

}


