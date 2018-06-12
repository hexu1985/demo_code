#ifndef __dclist_node_h
#define __dclist_node_h

#include <functional>
#include "dclist_node_base.h"

// double chain list node
template <typename T>
struct DCList_node : public DCList_node_base {
    T data;  // 数据成员

    DCList_node() {} 
    DCList_node(const T &data) { this->data = data; } 
};

// 将DCList_link强转成DCList_node<T> *
template <typename T>
DCList_node<T> *list_node(DCList_link x)
{
    return static_cast<DCList_node<T> *>(x);
}

template <typename T>
DCList_node<T> *list_next(DCList_node<T> *x)
{
    return list_node<T>(x->next);
}

template <typename T>
DCList_node<T> *list_prev(DCList_node<T> *x)
{
    return list_node<T>(x->prev);
}

// 获取element数据成员
template <typename T>
T *list_data(DCList_node<T> *x)
{
    return &(x->data);
}

// 遍历list的[x, nil)区间所有结点, Function处理data
template <typename T, typename Function>
void list_for_each(DCList_node<T> *x, DCList_node<T> *nil, Function fn)
{
    for ( ; x != nil; x = list_next(x)) {
        fn(*list_data(x));
    }
}

// 查找list的[x, nil)区间中data等于指定值的结点
template <typename T>
DCList_node<T> *list_search(DCList_node<T> *x, DCList_node<T> *nil, const T &val)
{
    while (x != nil && *list_data(x) != val) {
        x = list_next(x);
    }
    return x;
}

template <typename T, typename Predicate>
DCList_node<T> *list_search_if(DCList_node<T> *x, DCList_node<T> *nil, Predicate pred)
{
    while (x != nil && !pred(*list_data(x))) {
        x = list_next(x);
    }
    return x;
}

// 查找[x, nil)之间值最大的结点, 
// 并返回该结点的指针,
template <typename T, typename Compare = std::less<T>>
DCList_node<T> *list_find_max(DCList_node<T> *x, DCList_node<T> *nil, Compare comp = Compare())
{
    if (x == nil) return x;

    DCList_node<T> *max = x;
    x = list_next(x);

    while (x != nil) {
        // max->next->data < x->next->data
        if (comp(*list_data(max), *list_data(x))) {
            max = x;
        }
        x = list_next(x);
    }

    return max;
}

// 对[x, nil)之间的链表进行选择排序
//
// [113] <=> [515] <=> [101] <=>
//   ^-x       ^-t
//
// [] <=> [627] <=> [758] <=> [838] <=>
//  ^-out
//          ||
//          \/
//
// [113] <=> [101] <=>
//   ^-x
//
// [] <=> [515] <=> [627] <=> [758] <=> [838] <=>
//  ^-out
//
template <typename T, typename Compare = std::less<T>>
void list_selection(DCList_node<T> *x, DCList_node<T> *nil, Compare comp = Compare())
{
    DCList_link out = x->prev;
    while (x != nil) {
        auto t = list_find_max(x, nil, comp);   // t为[x, nil)之间最大元素结点
        if (t == x)
            x = list_next(t);
        list_delete(t);
        list_insert(out->next, t);              // 将t插入out的后头
    }
}

// 查找x结点和y结点中值小的结点, 
// 并把该结点从链表中摘除, 并返回该结点的指针,
template <typename T, typename Compare = std::less<T>>
DCList_node<T> *list_min(DCList_node<T> *x, DCList_node<T> *y, Compare comp = Compare())
{
    DCList_link min = x;
    if (comp(*list_data(y), *list_data(x))) {   // y->data < x->data
        min = y;
    } 
    return list_node<T>(min);
}

// 合并[x, x_nil)和[y, y_nil)之间的结点, 根据Compare指定的偏序关系, 结果存到[x, x_nil)区间
template <typename T, typename Compare = std::less<T>>
void list_merge(DCList_node<T> *x, DCList_node<T> *x_nil, DCList_node<T> *y, DCList_node<T> *y_nil, Compare comp = Compare())
{
    while (x != x_nil && y != y_nil) {
        auto t = list_min(x, y, comp);  // t为x和y后最小元素结点
        if (t == x) {
            x = list_next(t);
        } else {
            y = list_next(t);
            list_transfer(x, t);        // 将t插入x的前头
        }
    }

    if (y != y_nil) {
        list_transfer(x_nil, y, y_nil->prev);
    }
}

// 去除链表中[x, nil)之间的重复元素, 根据Compare指定的等价关系
template <typename T, typename Compare = std::equal_to<T>, typename Deleter = std::default_delete<DCList_node<T>>>
void list_unique(DCList_node<T> *x, DCList_node<T> *nil, Compare comp = Compare(), Deleter del = Deleter())
{
    if (x == nil)
        return;

    while (x != nil) {
        if (comp(*list_data(x), *list_data(list_next(x)))) {    // x->data == x->next->data
            auto y = list_next(x);
            list_delete(y);
            del(y);
        } else {
            x = list_next(x);
        }
    }
}

#endif

