#include <UnitTest++/src/UnitTest++.h>
#include "rdestl/intrusive_slist.h"

namespace
{
	struct MyNode : public rdestl::intrusive_slist_node
	{
		explicit MyNode(int i = 0): data(i) {}
		int	data;
	};

	TEST(DefaultCtorConstructsEmptyList)
	{
		rdestl::intrusive_slist<MyNode> l;
		CHECK(l.empty());
		CHECK_EQUAL(0ul, l.size());
	}
	TEST(PushFront)
	{
		rdestl::intrusive_slist<MyNode> l;
		MyNode node;
		node.data = 5;
		l.push_front(&node);
		CHECK_EQUAL(1ul, l.size());
		MyNode node2;
		node2.data = 10;
		l.push_front(&node2);
		CHECK_EQUAL(2ul, l.size());
		CHECK_EQUAL(10, l.front()->data);
	}
	TEST(PopFront)
	{
		rdestl::intrusive_slist<MyNode> l;
		MyNode node;
		node.data = 5;
		l.push_front(&node);
		MyNode node2;
		node2.data = 10;
		l.push_front(&node2);
		MyNode node3;
		node3.data = 15;
		l.push_front(&node3);
		CHECK_EQUAL(3ul, l.size());
		l.pop_front();
		CHECK_EQUAL(2ul, l.size());
		CHECK_EQUAL(10, l.front()->data);
		l.pop_front();
		CHECK_EQUAL(1ul, l.size());
		CHECK_EQUAL(5, l.front()->data);
		l.pop_front();
		CHECK(l.empty());
		CHECK_EQUAL(0ul, l.size());
	}
	TEST(Previous)
	{
		rdestl::intrusive_slist<MyNode> l;
		MyNode node;
		node.data = 5;
		l.push_front(&node);
		MyNode node2;
		node2.data = 10;
		l.push_front(&node2);
		rdestl::intrusive_slist<MyNode>::iterator it = l.begin();
		++it;
		rdestl::intrusive_slist<MyNode>::iterator itPrev = l.previous(it);
		CHECK(itPrev == l.begin());
	}
	TEST(Clear)
	{
		rdestl::intrusive_slist<MyNode> l;
		l.push_front(new MyNode(5));
		l.push_front(new MyNode(6));
		l.push_front(new MyNode(7));
		l.push_front(new MyNode(8));
		CHECK_EQUAL(4ul, l.size());
		l.clear();
		CHECK(l.empty());
		CHECK_EQUAL(0ul, l.size());
	}
	TEST(GetIterator)
	{
		rdestl::intrusive_slist<MyNode> l;
		l.push_front(new MyNode(5));
		l.push_front(new MyNode(6));
		MyNode* n(new MyNode(7));
		l.push_front(n);
		l.push_front(new MyNode(8));
		rdestl::intrusive_slist<MyNode>::iterator it = l.get_iterator(n);
		CHECK_EQUAL(7, it->data);
	}
}

