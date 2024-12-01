#include "data.h"

dataE::queue::queue() {
	hp = nullptr;
	tp = nullptr;
}

dataE::queue::~queue() {
	while (hp != nullptr) {
		node* oldhp = hp;
		hp = hp -> next;
		delete oldhp;
	}
}


std::string dataE::queue::getItem() {
	//Returns first item of queue

	if (hp == nullptr) {
		return "-1ERROR"; //If the queue is empty, returns error
	}
	else {
		return hp->data; //Otherwise, return the value of the first item
	}
}

void dataE::queue::pop() {
  if (hp == tp) {
    delete hp;
    hp = nullptr;
    tp = nullptr;
    return;
  }
	//Removes front of queue
	node* oldhp = hp;
	hp = hp->next;
	delete oldhp;
}

void dataE::queue::push(std::string data) {
	//Pushes to back of queue
	
	node* newNode = new node;
	newNode->data = data;
	if (hp == nullptr) {
		hp = newNode;
		tp = newNode;
	}
	else {
		tp->next = newNode;
		tp = newNode;
	}
}