/*
** RPI Game Architecture Engine
**
** Portions adapted from:
** Viper Engine - Copyright (C) 2016 Velan Studios - All Rights Reserved
**
** This file is distributed under the MIT License. See LICENSE.txt.
**
** Owen Hey | Professor Ameres
** Game Architecture, Spring 2019
** 661729120, heyo0@rpi.edu
*/

#include "ga_queue.h"

ga_queue::ga_queue(int node_count)
{
	nodeCount = 0;//in my implementation, nodecount is just counting
				//the number of the nodes in the set, so I will
				//not use node_count

	//a "dummy" node as the head of the queue,
	//both the head and the tail point to it
	node* myNode = new node();
	myNode->data = nullptr;
	myNode->next = nullptr;

	head = myNode;
	tail = myNode;
}

ga_queue::~ga_queue()
{
	//deconstructor
	node* current = head;
	node* next = head->next;
	//while we aren't at the end of the linked list
	while (next != nullptr) {
		//go forward deleting current and advancing once along the queue
		delete(current);
		current = next;
		next = next->next;
	}
	//finally, delete the final node
	delete(current);
}

void ga_queue::push(void* data)
{
	//make a new node in the heap
	//and put the data into it
	//its "next" is null because it
	//is placed at the end of the list
	node* myNode = new node();
	myNode->data = data;
	myNode->next = nullptr;
	
	//lock the tail
	tailLock.lock();
		//point old tail to this node
		//and make this node the tail
		tail->next = myNode;
		tail = myNode;
		nodeCount++; //increment node count
	tailLock.unlock();
}

bool ga_queue::pop(void** data)
{
	//first lock the head
	headLock.lock();
		//remember that the 'head' is a dummy node. So the first real
		//node is the one the head points to.
		node* node = (head->next);
		//if there is something in the queue (other than the dummy node)
		if (node == nullptr) {
			delete(node);
			//meaning that there was nothing to pop
			headLock.unlock();
			return false;
		}
		
		*data = node->data;//place the value in the memory of data
		head->next = node->next;
		delete(node);
		//delete the node from the heap and decrement nodecount
		nodeCount--;
		if (nodeCount == 0) {
			//this is if the last thing in the queue is deleted,
			//have to reassign the tail to be pointing at the dummy node
			tail = head;
		}
	headLock.unlock();
	return true;//we got an element off the queue
}

int ga_queue::get_count() const
{
	return nodeCount;
}
