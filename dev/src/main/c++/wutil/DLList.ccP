#include <<T>DLList.h>

void
<T>DLList::append(const <T>DLList & list)
{
	<T>DLListNode::reference(list.head);
	if (head == 0)
		head = list.head;
	else {
		tail->next = list.head;
		if (list.head != 0)
			list.head->prev = tail;
	}
	tail = list.tail;
}

void
<T>DLList::prepend(const <T>DLList & list)
{
	<T>DLListNode *h = list.head;
	if (h != 0) {
		<T>DLListNode *node = new <T>DLListNode(h->obj);
		node->prev = 0;
		<T>DLListNode *trailer = node;
		for (h = h->next; h != 0; h = h->next) {
			<T>DLListNode *n = new <T>DLListNode(h->obj);
			trailer->next = n;
			n->prev = trailer;
			trailer = n;
		}
		trailer->next = head;
		if (head != 0)
			head->prev = trailer;
		head = node;
	}
}

void
<T>DLList::del(const <T> & obj)
{
	<T>DLListNode *h = head;

	for ( ; ; ) {
		if (h == 0) {
			tail = head = h;
			return;
		}
		else if (&h->obj == &obj) {
			<T>DLListNode *n = h->next;
			if (n != 0)
				n->prev = 0;
			if (--h->ref == 0)
				delete h;
			h = n;
		}
		else
			break;
	}

	<T>DLListNode *prev = h;
	<T>DLListNode *node = h->next;
	while (node != 0) {
		if (&node->obj == &obj) {
			<T>DLListNode *n = node->next;
			if (n != 0)
				n->prev = node->prev;
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

void
<T>DLList::del_last(const <T> & obj)
{
	<T>DLListNode *t = tail;

	if (t == 0)
		return;

	if (&t->obj == &obj) {
		<T>DLListNode *p = t->prev;
		if (p != 0)
			p->next = 0;
		else
			head = 0;
		tail = p;
		if (--t->ref == 0)
			delete t;
		return;
	}

	<T>DLListNode *next = t;
	<T>DLListNode *node = t->prev;
	while (node != 0) {
		if (&node->obj == &obj) {
			<T>DLListNode *p = node->prev;
			if (p != 0)
				p->next = node->next;
			else
				head = next;
			next->prev = p;
			if (--node->ref == 0)
				delete node;
			return;
		}
		else {
			next = node;
			node = node->prev;
		}
	}
}
