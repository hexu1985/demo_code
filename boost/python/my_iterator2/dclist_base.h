#ifndef __dclist_base_h
#define __dclist_base_h

#include <cassert>
#include "dclist_node_base.h"

/**
 * 带哨兵节点的双向循环链表
 *
 * ... <=> [Nt] <=> [nil] <=> [N1] <=> [N2] <=> [N3] <=> ...
 *           ^tail              ^head
 */
struct DCList_base {
	DCList_node_base nil;	// 哨兵节点
};

/**
 * 初始化链表
 *         ____
 *        |    |
 *        V    |
 *   .--[nil]--'
 *   |    A    
 *   |____|     
 */
inline 
void list_init(DCList_base *list)
{
    list_nil_init(&list->nil);
}

// 判断list是否为空, 
inline
bool list_is_empty(DCList_base *list)
{
	return (list->nil.next == &list->nil);
}

// 返回nil地址
inline
DCList_link list_nil(DCList_base *list)
{
    return &list->nil;
}

// 返回链表的头结点地址
inline
DCList_link list_head(DCList_base *list)
{
    return list->nil.next;
}

// 返回链表的尾结点地址
inline
DCList_link list_tail(DCList_base *list)
{
    return list->nil.prev;
}

// 在链表头插入节点
inline
void list_insert_head(DCList_base *list, DCList_link x)
{
    list_insert(list_head(list), x);
}

// 在链表尾插入节点
inline
void list_insert_tail(DCList_base *list, DCList_link x)
{
    list_insert(list_nil(list), x);
}

// 在链表头删除节点
inline
DCList_link list_delete_head(DCList_base *list)
{
    assert(!list_is_empty(list));
    auto x= list_head(list);
    list_delete(x);
    return x;
}

// 在链表尾删除节点
inline
DCList_link list_delete_tail(DCList_base *list)
{
    assert(!list_is_empty(list));
    auto x = list_tail(list);
    list_delete(x);
    return x;
}

// 返回链表中元素个数
inline
int list_size(DCList_base *list)
{
    int n = 0;
    auto x = list_head(list);
    auto nil = list_nil(list);
    while (x != nil) {
        x = x->next;
        n++;
    }
    return n;
}

/**
 * 交换两个链表的所有节点(除了nil节点)
 */
inline
void list_swap(DCList_base *list1, DCList_base *list2)
{
    DCList_base temp;
    list_init(&temp);

    if (!list_is_empty(list1)) // temp = list1
        list_transfer(list_nil(&temp), list_head(list1), list_tail(list1));
    if (!list_is_empty(list2)) // list1 = list2
        list_transfer(list_nil(list1), list_head(list2), list_tail(list2));
    if (!list_is_empty(&temp))  // list2 = temp
        list_transfer(list_nil(list2), list_head(&temp), list_tail(&temp));
}

// 将链表结点逆序排列
inline
void list_reverse(DCList_base *list)
{
    list_reverse(list_head(list), list_nil(list));
}

#endif

