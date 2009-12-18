/*
 * Node.h
 *
 *  Created on: 27-mai-2009
 *      Author: mythrys
 */

#ifndef NODE_H
#define NODE_H

template <class T> class Node {
public:
	Node(T* element);
	Node(T* element, Node* next);
	Node<T>* getNext();
	void setNext(Node* next);
	T* getElement();
	void setElement(T* element);
	~Node();
private :
	T element;
	Node<T>* next;
};

#include "Node.tpp"
#endif /* NODE_H_ */
