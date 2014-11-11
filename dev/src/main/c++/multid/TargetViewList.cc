#ifdef __GNUC__
#pragma implementation
#endif
#include <TargetViewList.h>
#include <TargetView.h>

TargetViewList &
TargetViewList::operator=(const TargetViewList &list)
{
	if (this != &list) {
		TargetViewListNode::dereference(head);
		TargetViewListNode::reference(list.head);
		head = list.head;
		tail = list.tail;
	}
	return *this;
}

void
TargetViewList::append(const TargetViewList &list)
{
	TargetViewListNode::reference(list.head);
	if (head == 0)
		head = list.head;
	else
		tail->next = list.head;
	tail = list.tail;
}

void
TargetViewList::prepend(const TargetViewList &list)
{
	TargetViewListNode *h = list.head;
	if (h != 0) {
		TargetViewListNode *node = new TargetViewListNode(h->obj);
		TargetViewListNode *trailer = node;
		for (h = h->next; h != 0; h = h->next) {
			TargetViewListNode *n = new TargetViewListNode(h->obj);
			trailer->next = n;
			trailer = n;
		}
		trailer->next = head;
		head = node;
	}
}

void
TargetViewList::del(const TargetView &obj)
{
	TargetViewListNode *h = head;

	for ( ; ; ) {
		if (h == 0) {
			tail = head = h;
			return;
		}
		else if (&h->obj == &obj) {
			TargetViewListNode *n = h->next;
			if (--h->ref == 0)
				delete h;
			h = n;
		}
		else
			break;
	}

	TargetViewListNode *prev = h;
	TargetViewListNode *node = h->next;
	while (node != 0) {
		if (&node->obj == &obj) {
			TargetViewListNode *n = node->next;
			if (--node->ref == 0)
				delete node;
			prev->next = n;
			node = n;
		}
		else {
			prev = node;
			node = node->next;
		}
	}
	head = h;
	tail = prev;
}
