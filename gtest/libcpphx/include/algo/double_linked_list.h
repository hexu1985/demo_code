// -*- C++ -*-
// HeXu's
// 2015 Apr

#ifndef __double_linked_list_h
#define __double_linked_list_h

#include <cstddef>

namespace Hx {
namespace Double_linked {

// 双向循环链表节点, 不包含数据
typedef struct list_node_t {
	struct list_node_t *next;
	struct list_node_t *prev;
} list_node_t;

// 带哨兵节点的双向循环链表
typedef struct list_t {
	list_node_t nil;	// 哨兵
} list_t;

// 初始化链表
void list_init(list_t *list);

// 获取链表头节点的地址
list_node_t *list_head(const list_t *list);

// 获取链表尾节点的地址
list_node_t *list_tail(const list_t *list);

// 获取链表逾尾节点的地址
list_node_t *list_past_tail(const list_t *list);

// 在链表的x节点前插入y节点
void list_insert(list_node_t *x, list_node_t *y);

// 将[a, b]区间所包含节点插入链表的x节点前,
// 区间至少包含一个节点
void list_insert(list_node_t *x, list_node_t *a, list_node_t *b);

// 从链表上删除x节点
void list_remove(list_node_t *x);

// 从链表中将[a, b]区间所包含节点删除,
// 区间至少包含一个节点
void list_remove(list_node_t *a, list_node_t *b);

// 将另外一个链表的[a, b]区间所包含节点插入到
// 当前链表的x节点前,
// 并且还要保持另外一个链表为有效链表,
// 区间至少包含一个节点
void list_transfer(list_node_t *x, list_node_t *a, list_node_t *b);

// 判断list是否为空, 
// 如果为空返回true,
// 否则返回false
bool list_empty(const list_t *list);

// 反转链表中区间[a, b]包含节点的顺序,
// 区间至少包含一个节点
void list_reverse(list_node_t *a, list_node_t *b);

// 将整个链表逆序
void list_reverse(list_t *list);

// 获取链表中[a, b]区间包含节点的个数,
// 区间至少包含一个节点
size_t list_size(const list_node_t *a, const list_node_t *b);

// 获取链表中节点的个数
size_t list_size(const list_t *list);

// 交换两个链表中所有的节点,
// 保持节点间原有的顺序
void list_swap(list_t *x, list_t *y);

} // namespace Double_linked
} // namespace Hx

#endif // __double_linked_list_h

