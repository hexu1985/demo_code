#ifndef __dclist_h
#define __dclist_h

#include <memory>
#include <initializer_list>

#include "dclist_base.h"
#include "dclist_node.h"

// double chain list
template <typename T>
struct DCList : public DCList_base {
};

// 遍历list所有结点, Function处理data
template <typename T, typename Function>
void list_for_each(DCList<T> *list, Function fn)
{
    list_for_each(list_node<T>(list_head(list)), list_node<T>(list_nil(list)), fn);
}

// 查找list中data等于指定值的结点
template <typename T>
DCList_node<T> *list_search(DCList<T> *list, const T &val)
{
    return list_search(list_node<T>(list_head(list)), list_node<T>(list_nil(list)), val);
}

template <typename T, typename Predicate>
DCList_node<T> *list_search_if(DCList<T> *list, Predicate pred)
{
    return list_search_if(list_node<T>(list_head(list)), list_node<T>(list_nil(list)), pred);
}

// 删除list中值为val的所有的结点
template <typename T, typename Deleter = std::default_delete<DCList_node<T>>>
void list_remove(DCList<T> *list, const T &val, Deleter del = Deleter())
{
    DCList_node<T> *nil = list_node<T>(list_nil(list));
    DCList_node<T> *x = list_search(list_node<T>(list_head(list)), nil, val);
    while (x != nil) {
        DCList_node<T> *y = list_next(x);   // y是下一次search的起点

        list_delete(x);
        del(x);

        x = list_search(y, nil, val);
    }
}

template <typename T, typename Predicate, typename Deleter = std::default_delete<DCList_node<T>>>
void list_remove_if(DCList<T> *list, Predicate pred, Deleter del = Deleter())
{
    DCList_node<T> *nil = list_node<T>(list_nil(list));
    DCList_node<T> *x = list_search_if(list_node<T>(list_head(list)), nil, pred);
    while (x != nil) {
        DCList_node<T> *y = list_next(x);   // y是下一次search的起点

        list_delete(x);
        del(x);

        x = list_search_if(y, nil, pred);
    }
}

// 销毁list
template <typename T, typename Deleter = std::default_delete<DCList_node<T>>>
void list_destroy(DCList<T> *list, Deleter del = Deleter())
{
    while (!list_is_empty(list)) {
        del(list_node<T>(list_delete_head(list)));
    }
}

// 清空list
template <typename T, typename Deleter = std::default_delete<DCList_node<T>>>
void list_clear(DCList<T> *list, Deleter del = Deleter())
{
    list_destroy(list, del);
    list_init(list);
}

// 选择排序list
template <typename T, typename Compare = std::less<T>>
void list_selection(DCList<T> *list, Compare comp = Compare())
{
    list_selection(list_node<T>(list_head(list)), list_node<T>(list_nil(list)), comp);
}

template <typename T, typename Compare = std::less<T>>
void list_sort(DCList<T> *list, Compare comp = Compare())
{
    list_selection(list, comp);
}

// 合并list1和list2, 并且将结果放到list1中
template <typename T, typename Compare = std::less<T>>
void list_merge(DCList<T> *list1, DCList<T> *list2, Compare comp = Compare())
{
    list_merge(list_node<T>(list_head(list1)), list_node<T>(list_nil(list1)), 
            list_node<T>(list_head(list2)), list_node<T>(list_nil(list2)), comp);
}

// 去除链表中的重复元素
template <typename T, typename Compare = std::equal_to<T>, typename Deleter = std::default_delete<DCList_node<T>>>
void list_unique(DCList<T> *list, Compare comp = Compare(), Deleter del = Deleter())
{
    list_unique(list_node<T>(list_head(list)), list_node<T>(list_nil(list)), comp, del);
}

#endif
