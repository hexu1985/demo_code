#ifndef __list_h
#define __list_h

#include <cstddef>
#include <type_traits>
#include <initializer_list>
#include <limits>

#include "dclist.h"
#include "dclist_iterator.h"

template <typename T> 
using list_iterator = DCList_iterator<T>;

template <typename T>
class list: private DCList<T> {
public:
    typedef T value_type;
    typedef T &reference;
    typedef T *pointer;
    typedef ptrdiff_t difference_type;
    typedef size_t size_type;
    typedef list_iterator<T> iterator;

    list()
    {
        list_init(this);
    }

    list(std::initializer_list<value_type> il)
    {
        list_init(this);
        for (auto &e : il) {
            list_insert_tail(this, new DCList_node<T>(e));
        }
    }

    explicit list(size_type n, const value_type &val = value_type())
    {
        list_init(this);
        for (size_type i = 0; i < n; i++) {
            list_insert_tail(this, new DCList_node<T>(val));
        }
    }

    template <typename InputIterator, typename = typename
        std::enable_if<!std::is_integral<InputIterator>::value>::type>
    list(InputIterator first, InputIterator last)
    {
        list_init(this);
        while (first != last) {
            list_insert_tail(this, new DCList_node<T>(*first++));
        }
    }

    list(const list &lst)
    {
        list_init(this);
        for (auto &e : lst) {
            list_insert_tail(this, new DCList_node<T>(e));
        }
    }

    ~list()
    {
        list_destroy(this);
    }

    list &operator =(const list &x)
    {
        if (this != &x) {
            assign(x.begin(), x.end());
        }
        return *this;
    }

    list &operator =(std::initializer_list<value_type> il)
    {
        assign(il);
    }

    template <typename InputIterator, typename = typename
        std::enable_if<!std::is_integral<InputIterator>::value>::type>
    void assign(InputIterator first, InputIterator last)
    {
        list tmp(first, last);
        this->swap(tmp);
    }

    void assign(size_type n, const value_type &val)
    {
        list tmp(n, val);
        this->swap(tmp);
    }

    void assign(std::initializer_list<value_type> il)
    {
        list tmp(il);
        this->swap(tmp);
    }

    bool empty() const
    {
        return list_is_empty(const_cast<list *>(this));
    }

    void push_front(const value_type &val)
    {
        list_insert_head(this, new DCList_node<T>(val));
    }

    void pop_front()
    {
        delete list_node<T>(list_delete_head(this));
    }

    void push_back(const value_type &val)
    {
        list_insert_tail(this, new DCList_node<T>(val));
    }

    void pop_back()
    {
        delete list_node<T>(list_delete_tail(this));
    }

    iterator begin() const
    {
        return list_begin(const_cast<list *>(this)); 
    }

    iterator end() const
    {
        return list_end(const_cast<list *>(this));
    }

    iterator insert(iterator pos, const value_type &val)
    {
        auto x = new DCList_node<T>(val);
        list_insert(pos.get_node(), x);

        return iterator(x);
    }

    iterator insert(iterator pos, size_type n, const value_type &val)
    {
        if (n == 0)
            return pos;

        auto x = new DCList_node<T>(val);
        list_insert(pos.get_node(), x);

        for (size_type i = 1; i < n; i++) {
            list_insert(pos.get_node(), new DCList_node<T>(val));
        }

        return iterator(x);
    }

    template <typename InputIterator, typename = typename
        std::enable_if<!std::is_integral<InputIterator>::value>::type>
    iterator insert(iterator pos, InputIterator first, InputIterator last)
    {
        if (first == last)
            return pos;

        auto x = new DCList_node<T>(*first++);
        list_insert(pos.get_node(), x);

        while (first != last) {
            list_insert(pos.get_node(), new DCList_node<T>(*first++));
        }

        return iterator(x);
    }

    iterator insert(iterator pos, std::initializer_list<value_type> il)
    {
        return insert(pos, il.begin(), il.end());
    }

    iterator erase(iterator pos)
    {
        auto x = pos.get_node();
        ++pos;

        list_delete(x);
        delete x;

        return pos;
    }

    iterator erase(iterator first, iterator last)
    {
        while (first != last) {
            auto x = first.get_node();
            ++first;

            list_delete(x);
            delete x;
        }

        return last;
    }

    void remove(const value_type &val)
    {
        list_remove(this, val);
    }

    template <typename Predicate>
    void remove_if(Predicate pred)
    {
        list_remove_if(this, pred);
    }

    void reverse()
    {
        list_reverse(this);
    }

    void sort()
    {
        list_selection(this);
    }

    template <typename Compare>
    void sort(Compare comp)
    {
        list_selection(this, comp);
    }

    void splice(iterator pos, list &lst)
    {
		if (lst.empty())
            return;

        list_transfer(pos.get_node(), list_head(&lst), list_tail(&lst));
    }

    void splice(iterator pos, list &lst, iterator i)
    {
        list_transfer(pos.get_node(), i.get_node());
    }

    void splice(iterator pos, list &lst, iterator first, iterator last)
    {
        if (first == last)
            return;

        list_transfer(pos.get_node(), first.get_node(), list_prev(last.get_node()));
    }

    void swap(list &lst)
    {
        list_swap(this, &lst);
    }

    void clear()
    {
        list_clear(this);
    }

    reference front()
    {
        return *list_data(list_node<T>(list_head(this)));
    }

    reference back()
    {
        return *list_data(list_node<T>(list_tail(this)));
    }

    size_type max_size() const
    {
		return std::numeric_limits<size_type>::max();
    }

    size_type size() const
    {
        return list_size(const_cast<list *>(this));
    }

    void resize(size_type n, const value_type &val = value_type())
    {
        for (int i = n-size(); i > 0; i--) {
            push_back(val);
        }

        for (int i = size()-n; i > 0; i--) {
            pop_back();
        }
    }

    void merge(list &lst)
    {
        list_merge(this, &lst);
    }

    template <typename Compare>
    void merge(list &lst, Compare comp)
    {
        list_merge(this, &lst, comp);
    }

    void unique()
    {
        list_unique(this);
    }

    template <typename BinaryPredicate>
    void unique(BinaryPredicate p)
    {
        list_unique(this, p);
    }
};

#endif
