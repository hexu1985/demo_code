// -*- C++ -*-
// HeXu's
// 2015 Apr

#include "algo/double_linked_list.h"

namespace Hx {
namespace Double_linked {

/**
 * 初始化链表
 *         ____
 *        |    |
 *        V    |
 *   .--[nil]--'
 *   |    A    
 *   |____|     
 */
void list_init(list_t *list)
{
	list->nil.next = &list->nil;
	list->nil.prev = &list->nil;
}

/**
 * 获取链表头节点的地址
 *        __________________________________________________
 *       |                                                  |
 *       V                                                  |
 *   .--[N4] <=> [N5] <=> [nil] <=> [N1] <=> [N2] <=> [N3]--'
 *   |                               ^-head            A
 *   |_________________________________________________|
 */
list_node_t *list_head(const list_t *list)
{
	return (list_node_t *) list->nil.next;
}

/**
 * 获取链表尾节点的地址
 *        __________________________________________________
 *       |                                                  |
 *       V                                                  |
 *   .--[N4] <=> [N5] <=> [nil] <=> [N1] <=> [N2] <=> [N3]--'
 *   |            ^-tail                               A
 *   |_________________________________________________|
 */
list_node_t *list_tail(const list_t *list)
{
	return (list_node_t *) list->nil.prev;
}

/**
 * 获取链表逾尾节点的地址
 *        __________________________________________________
 *       |                                                  |
 *       V                                                  |
 *   .--[N4] <=> [N5] <=> [nil] <=> [N1] <=> [N2] <=> [N3]--'
 *   |                      ^-past_tail                A
 *   |_________________________________________________|
 */
list_node_t *list_past_tail(const list_t *list)
{
	return (list_node_t *) &list->nil;
}

/**
 * 在链表的x节点前插入y节点
 *            ___                ___
 *           |   |------------->|   |------>
 *    <------|___|<-------------|___|
 *                                ^-x
 *                  ___        
 *                 |   |------>
 *            <----|___|       
 *                   ^-y       
 * =========================================
 *            ___                ___
 *           |   |------------->|   |------>
 *    <------|___|<-------------|___|
 *             A                 A ^-x
 *             |    ___          |
 *             |   |   |---------'
 *             '---|___|       
 *                   ^-y       
 * =========================================
 *            ___                ___
 *           |   |--.     .---->|   |------>
 *    <------|___|  |     |  .--|___|
 *             A    |     |  |    ^-x
 *             |    V__   |  |
 *             |   |   |--'  |
 *             '---|___|<----'
 *                   ^-y
 */
void list_insert(list_node_t *x, list_node_t *y)
{
	y->prev = x->prev;
	y->next = x;
	x->prev->next = y;
	x->prev = y;
}

// 将[a, b]区间所包含节点插入链表的x节点前,
// 区间至少包含一个节点
void list_insert(list_node_t *x, list_node_t *a, list_node_t *b)
{
	a->prev = x->prev;
	b->next = x;
	x->prev->next = a;
	x->prev = b;
}

/**
 * 从链表上删除x节点
 *            ___           ___           ___ 
 *           |   |-------->|   |-------->|   |------>
 *    <------|___|<--------|___|<--------|___|
 *                           ^-x       
 * ==================================================
 *                     ____________________
 *                    |                    |
 *            ___     |     ___           _V_ 
 *           |   |----'    |   |-------->|   |------>
 *    <------|___|<--------|___|    .----|___|
 *             A             ^-x    |   
 *             |____________________|                    
 */
void list_remove(list_node_t *x)
{
	x->prev->next = x->next;
	x->next->prev = x->prev;
}

// 从链表中将[a, b]区间所包含节点删除,
// 区间至少包含一个节点
void list_remove(list_node_t *a, list_node_t *b)
{
	a->prev->next = b->next;
	b->next->prev = a->prev;
}

// 将另外一个链表的[a, b]区间所包含节点插入到
// 当前链表的x节点前,
// 并且还要保持另外一个链表为有效链表,
// 区间至少包含一个节点
void list_transfer(list_node_t *x, list_node_t *a, list_node_t *b)
{
	list_remove(a, b);
	list_insert(x, a, b);
}

// 判断list是否为空, 
// 如果为空返回true,
// 否则返回false
bool list_empty(const list_t *list)
{
	return (list->nil.next == &list->nil);
}

// 反转链表中区间[a, b]包含节点的顺序,
// 区间至少包含一个节点
void list_reverse(list_node_t *a, list_node_t *b)
{
	if (a == b)	// 区间只包含一个节点, 不需要排序
		return;

	// b节点开始, 到a节点结束(不包括a节点),
	// 将依次遍历的节点插入到a节点前
	b = b->next;
	for (list_node_t *c = b->prev; c != a; c = b->prev) {
		list_remove(c);
		list_insert(a, c);
	}
}

// 将整个链表逆序
void list_reverse(list_t *list)
{
	list_reverse(list->nil.next, list->nil.prev);
}

// 获取链表中[a, b]区间包含节点的个数,
// 区间至少包含一个节点
size_t list_size(const list_node_t *a, const list_node_t *b)
{
	size_t n = 1;
	while (a != b) {
		a = a->next;
		n++;
	}
	return n;
}

// 获取链表中节点的个数
size_t list_size(const list_t *list)
{
	if (list_empty(list))
		return 0;

	return list_size(list_head(list), list_tail(list));
}

// 交换两个链表中所有的节点,
// 保持节点间原有的顺序
void list_swap(list_t *x, list_t *y)
{
	bool x_empty = list_empty(x);
	bool y_empty = list_empty(y);

	if (x_empty && y_empty) {
		return;
	} else if (x_empty) {
		list_transfer(list_head(x), list_head(y), list_tail(y));
	} else if (y_empty) {
		list_transfer(list_head(y), list_head(x), list_tail(x));
	} else {
		list_t list;
		list_t *z = &list;
		list_init(z);
		list_transfer(list_head(z), list_head(x), list_tail(x));
		list_transfer(list_head(x), list_head(y), list_tail(y));
		list_transfer(list_head(y), list_head(z), list_tail(z));
	}
}

} // namespace Double_linked
} // namespace Hx

