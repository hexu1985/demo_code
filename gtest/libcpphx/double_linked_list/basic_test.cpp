
#include "test_double_linked_list.h"

TEST(BasicTest, modify_front)
{
	List<int> list;

	EXPECT_TRUE(list.empty());

	for (int i = 1; i <= 10; i++) {
		list.push_front(i);
		EXPECT_EQ(i, list.size());
		EXPECT_EQ(i, list.front());
	}

	EXPECT_FALSE(list.empty());
	EXPECT_EQ(10, list.size());
	EXPECT_EQ(10, list.front());
	EXPECT_EQ(1, list.back());

	list.print("after push_front, list");
	std::cout << std::endl;

	while (!list.empty()) {
		list.pop_front();
	}
	EXPECT_TRUE(list.empty());
	EXPECT_EQ(0, list.size());

	list.print("after pop_front, list");
	std::cout << std::endl;
}

TEST(BasicTest, modify_back)
{
	List<int> list;

	EXPECT_TRUE(list.empty());

	for (int i = 1; i <= 10; i++) {
		list.push_back(i);
		EXPECT_EQ(i, list.size());
		EXPECT_EQ(i, list.back());
	}

	EXPECT_FALSE(list.empty());
	EXPECT_EQ(10, list.size());
	EXPECT_EQ(1, list.front());
	EXPECT_EQ(10, list.back());

	list.print("after push_back, list");
	std::cout << std::endl;

	while (!list.empty()) {
		list.pop_back();
	}
	EXPECT_TRUE(list.empty());
	EXPECT_EQ(0, list.size());

	list.print("after pop_back, list");
	std::cout << std::endl;
}

TEST(BasicTest, splice)
{
	List<int> list1, list2;

	for (int i = 1; i <= 10; i++) {
		list1.push_back(i);
	}

	for (int i = 11; i <= 16; i++) {
		list2.push_back(i);
	}

	EXPECT_EQ(10, list1.size());
	EXPECT_EQ(6, list2.size());

	list1.print("before splice, list1");
	std::cout << std::endl;

	list2.print("before splice, list2");
	std::cout << std::endl;

	list1.splice(list2);

	EXPECT_EQ(16, list1.size());
	EXPECT_EQ(0, list2.size());

	list1.print("after splice, list1");
	std::cout << std::endl;

	list2.print("after splice, list2");
	std::cout << std::endl;
}

TEST(BasicTest, swap)
{
	List<int> list1, list2;

	for (int i = 1; i <= 10; i++) {
		list1.push_back(i);
	}

	for (int i = 11; i <= 16; i++) {
		list2.push_back(i);
	}

	EXPECT_EQ(10, list1.size());
	EXPECT_EQ(6, list2.size());

	list1.print("before swap, list1");
	std::cout << std::endl;

	list2.print("before swap, list2");
	std::cout << std::endl;

	list1.swap(list2);

	EXPECT_EQ(6, list1.size());
	EXPECT_EQ(10, list2.size());

	list1.print("after swap, list1");
	std::cout << std::endl;

	list2.print("after swap, list2");
	std::cout << std::endl;
}

TEST(BasicTest, modify)
{
	List<int> list;

	EXPECT_TRUE(list.empty());

	for (int i = 1; i <= 10; i++) {
		list.push_back(i);
	}

	EXPECT_EQ(10, list.size());

	list.print("list");
	std::cout << std::endl;

	List<int>::node_type *node;
	node = list.find(5);

	EXPECT_NE((List<int>::node_type *) NULL, node);
	EXPECT_EQ(5, node->key);

	list.insert(node, 13);

	EXPECT_EQ(11, list.size());

	list.print("insert 13, list");
	std::cout << std::endl;

	list.erase(node);
	node = list.find(5);

	EXPECT_EQ(NULL, node);
	EXPECT_EQ(10, list.size());

	list.print("insert 13, list");
	std::cout << std::endl;

	list.clear();

	EXPECT_TRUE(list.empty());
	EXPECT_EQ(0, list.size());
}


TEST(BasicTest, reverse)
{
	List<int> list;

	EXPECT_TRUE(list.empty());

	for (int i = 1; i <= 10; i++) {
		list.push_back(i);
	}

	EXPECT_EQ(10, list.size());

	list.print("list");
	std::cout << std::endl;

	list.reverse();

	list.print("after reverse, list");
	std::cout << std::endl;

	for (int i = 10; i >= 1; i--) {
		EXPECT_EQ(i, list.size());
		EXPECT_EQ(i, list.front());
		list.pop_front();
	}
}
