#pragma once

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


#include <mutex>
class ga_queue
{
	//node struct needs two things:
	//a pointer to the next node
	//and the data in the node, in this case, a void pointer
	struct node {
		void* data;
		node* next;
	};

public:
	//define all the functions
	//constructor, destructor, push, pop and get count
	ga_queue(int node_count);
	~ga_queue();

	void push(void* data);
	bool pop(void** data);

	int get_count() const;

private:
	//private variables for keeping track of the queue
	int nodeCount;

	//head and tail of the linked list (queue is implemented as L.L.)
	node* head;
	node* tail;

	//two lock-queue implementation
	std::mutex headLock;
	std::mutex tailLock;

};
