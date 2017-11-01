#pragma once
#include "node.h"
#include <cstdlib>
#include <assert.h>

template <class Item>
class stack
{
public:
	stack() { top_ptr = NULL; }
	stack(const stack<Item>& source);
	void push(const Item& entry);
	void pop();
	bool empty() const;
	Item top() const;

private:
	node<Item> *top_ptr;
};


template <class Item>
stack<Item>::stack(const stack<Item>& source)
{
	node<Item>* tail_ptr;
	list_copy(source.top_ptr, top_ptr, tail_ptr);
}

template <class Item>
void stack<Item>::push(const Item& entry)
{
	list_head_insert(top_ptr, entry);
}

template <class Item>
void stack<Item>::pop()
{
	assert(!empty());
	list_head_remove(top_ptr);
}

template <class Item>
bool stack<Item>::empty() const
{
	return top_ptr == NULL;
}

template <class Item>
Item stack<Item>::top() const
{
	assert(!empty());
	return top_ptr->data();
}