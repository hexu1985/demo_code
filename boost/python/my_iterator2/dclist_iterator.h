#ifndef __dclist_iterator_h
#define __dclist_iterator_h

#include "dclist.h"

template <typename T>
struct DCList_iterator {
    DCList_node<T> *node;

    typedef T value_type;
    typedef T *pointer;
    typedef T &reference;
    typedef ptrdiff_t difference_type;
    typedef std::bidirectional_iterator_tag iterator_category;

    typedef DCList_iterator<T> this_type;

    DCList_iterator(): node(NULL) {}

    explicit DCList_iterator(DCList_link link): node(list_node<T>(link)) {}

    reference operator *() const
    {
        return *list_data(node);
    }

    pointer operator ->() const
    {
        return list_data(node);
    }

    this_type &operator ++()
    {
        node = list_next(node);
        return *this;
    }

    this_type operator ++(int)
    {
        this_type tmp(*this);
        node = list_next(node);
        return tmp;
    }

    this_type &operator --()
    {
        node = list_prev(node);
        return *this;
    }

    this_type operator --(int)
    {
        this_type tmp(*this);
        node = list_prev(node);
        return tmp;
    }

    bool operator ==(const this_type &other) const
    {
        return (node == other.node);
    }

    bool operator !=(const this_type &other) const
    {
        return !(*this == other);
    }

    DCList_node<T> *get_node()
    {
        return node;
    }
};

template <typename T>
DCList_iterator<T> list_begin(DCList<T> *list)
{
    assert(list != NULL);
    return DCList_iterator<T>(list_head(list));
}

template <typename T>
DCList_iterator<T> list_end(DCList<T> *list)
{
    assert(list != NULL);
    return DCList_iterator<T>(list_nil(list));
}

#endif
