
#ifndef STACK_H
#define STACK_H

// this is the node class used to build up the LIFO stack
template <class Data>
class Node {

private:

	Data holdMe;
	Node *next;
	
public:

	/*****************************************/
	/** WHATEVER CODE YOU NEED TO ADD HERE!! */
	/*****************************************/

	~Node () {}

	Node (Data _data) : holdMe(_data), next(nullptr) { }

	Node (Data _data, Node* _next) : holdMe(_data), next(_next) { }

	Data getData() {
		return holdMe;
	}

	bool hasNext() {
		return next != nullptr;
	}

	Node* getNext() {
		return next;
	}

};

// a simple LIFO stack
template <class Data> 
class Stack {

	Node <Data> *head;

public:

	// destroys the stack
	~Stack () {
		Node <Data>* next; 
		while (head) {
			next = head->getNext();
			delete head;
			head = next;
		}
	 }

	// creates an empty stack
	Stack () { 
		head = nullptr;
	}

	// adds pushMe to the top of the stack
	void push (Data _data) {
		Node <Data>* newData = new Node <Data>(_data, head);
		head = newData;
	 }

	// return true if there are not any items in the stack
	bool isEmpty () {
		return head == nullptr;
	}

	// pops the item on the top of the stack off, returning it...
	// if the stack is empty, the behavior is undefined
	Data pop () {
		Data res;
		Node <Data>* pre = nullptr;
		if (head != nullptr) {
			res = head->getData();
			pre = head->getNext();
			delete head;
			head = pre;
		}
		return res;
	}
};

#endif
