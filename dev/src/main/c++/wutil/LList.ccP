#include <<T>LList.h>

void
<T>LList::append(const <T>LList & list)
{
	<T>LListNode::reference(list.head);
	if (head == 0)
		head = list.head;
	else
		tail->next = list.head;
	tail = list.tail;
}

void
<T>LList::prepend(const <T>LList & list)
{
	<T>LListNode *h = list.head;
	if (h != 0) {
		<T>LListNode *node = new <T>LListNode(h->obj);
		<T>LListNode *trailer = node;
		for (h = h->next; h != 0; h = h->next) {
			<T>LListNode *n = new <T>LListNode(h->obj);
			trailer->next = n;
			trailer = n;
		}
		trailer->next = head;
		head = node;
	}
}

void
<T>LList::del(const <T> & obj)
{
	<T>LListNode *h = head;

	for ( ; ; ) {
		if (h == 0) {
			tail = head = h;
			return;
		}
		else if (&h->obj == &obj) {
			<T>LListNode *n = h->next;
			if (--h->ref == 0)
				delete h;
			h = n;
		}
		else
			break;
	}

	<T>LListNode *prev = h;
	<T>LListNode *node = h->next;
	while (node != 0) {
		if (&node->obj == &obj) {
			<T>LListNode *n = node->next;
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
