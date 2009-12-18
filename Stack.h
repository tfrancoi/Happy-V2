/*
 * Stack.h
 *
 *  Created on: 27-mai-2009
 *      Author: mythrys
 */

#ifndef STACK_H_
#define STACK_H_

#include "Node.h"



template <class I>
class Stack {
public:
	Stack();
	virtual ~Stack();
	void push(I* item);
	I* pop();
	bool isEmpty();
private:
	Node<I>* first;
};

template <class I>
void clearStack(Stack<I>* s);

#include "Stack.tpp"
#endif /* STACK_H_ */
