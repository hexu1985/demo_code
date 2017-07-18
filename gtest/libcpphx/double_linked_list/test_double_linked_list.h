#ifndef __test_double_linked_list_h
#define __test_double_linked_list_h

#include <iostream>
#include <string>
#include <stdexcept>

#include <gtest/gtest.h>

#include "algo/double_linked_list.h"

namespace impl = Hx::Double_linked;

template <typename T>
struct List_node: public impl::list_node_t {
	T key;

	List_node() {}
	List_node(const T &k): key(k) {}
};


template <typename T>
class List: public impl::list_t {
public:
	typedef List_node<T> node_type;

	List() { impl::list_init(this); }

	~List() { clear(); }

	bool empty() const { return impl::list_empty(this); }

	size_t size() const { return impl::list_size(this); }

	void push_front(const T &k) 
	{
		node_type *node = new node_type(k);
		impl::list_insert(impl::list_head(this), node);
	}

	void push_back(const T &k)
	{
		node_type *node = new node_type(k);
		impl::list_insert(impl::list_past_tail(this), node);
	}

	void pop_front()
	{
		if (empty())
			throw std::underflow_error("pop_front error: list is empty!");

		node_type *node = static_cast<node_type *>(impl::list_head(this));
		impl::list_remove(node);
		delete node;
	}

	void pop_back()
	{
		if (empty())
			throw std::underflow_error("pop_back error: list is empty!");

		node_type *node = static_cast<node_type *>(impl::list_tail(this));
		impl::list_remove(node);
		delete node;
	}

	const T &front() const
	{
		if (empty())
			throw std::underflow_error("front error: list is empty!");

		node_type *node = static_cast<node_type *>(impl::list_head(this));
		return node->key;
	}

	T &front()
	{
		if (empty())
			throw std::underflow_error("front error: list is empty!");

		node_type *node = static_cast<node_type *>(impl::list_head(this));
		return node->key;
	}

	const T &back() const
	{
		if (empty())
			throw std::underflow_error("back error: list is empty!");

		node_type *node = static_cast<node_type *>(impl::list_tail(this));
		return node->key;
	}

	T &back()
	{
		if (empty())
			throw std::underflow_error("back error: list is empty!");

		node_type *node = static_cast<node_type *>(impl::list_tail(this));
		return node->key;
	}

	node_type *find(const T &k)
	{
		impl::list_node_t *first = impl::list_head(this);
		impl::list_node_t *last = impl::list_past_tail(this);
		for ( ; first != last; first = first->next) {
			node_type *node = static_cast<node_type *>(first);
			if (node->key == k)
				return node;
		}
		return NULL;
	}

	node_type *insert(node_type *x, const T &k)
	{
		node_type *node = new node_type(k);
		impl::list_insert(x, node);
		return node;
	}

	void erase(node_type *x)
	{
		impl::list_remove(x);
		delete x;
	}

	void splice(List &list)
	{
		if (list.empty())
			return;

		impl::list_transfer(impl::list_past_tail(this),
				impl::list_head(&list), impl::list_tail(&list));
	}

	void swap(List &list)
	{
		impl::list_swap(this, &list);
	}

	void clear()
	{
		impl::list_node_t *first = impl::list_head(this);
		impl::list_node_t *last = impl::list_past_tail(this);
		while (first != last) {
			node_type *node = static_cast<node_type *>(first);
			first = first->next;
			delete node;
		}
		impl::list_init(this);
	}

	bool is_sorted() const
	{
		return true;
	}

	void reverse()
	{
		impl::list_reverse(this);
	}

	void insert_sort()
	{
	}

	void quick_sort()
	{
	}

	void unique()
	{
	}

	void merge(List &list)
	{
	}

	void print(const std::string &prefix = "", size_t n_per_line = 10)
	{
		if (!prefix.empty())
			std::cout << prefix << ":\n";

		if (empty()) {
			std::cout << "list is empty\n";
			return;
		}

		impl::list_node_t *first = impl::list_head(this);
		impl::list_node_t *last = impl::list_past_tail(this);
		size_t count = 0;
		for ( ; first != last; first = first->next) {
			node_type *node = static_cast<node_type *>(first);
			std::cout << node->key << ", ";
			count++;
			if (count % n_per_line == 0) {
				std::cout << '\n';
			}
		}
		if (count % n_per_line != 0) {
			std::cout << '\n';
		}
	}
};

#endif
