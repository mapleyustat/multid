#ifdef __GNUC__
#pragma implementation
#endif
#include <GeomObjList.h>

void
GeomObjListNode::dereference(GeomObjListNode *node)
{
	while (node != 0 && --node->ref == 0) {
		GeomObjListNode *n = node->next;
		if (n != 0)
			n->prev = node->prev;
		delete node;
		node = n;
	}
}

void
GeomObjList::append(const GeomObj &obj)
{
	GeomObjListNode *node = tail;
	tail = new GeomObjListNode(obj, 0, node);
	if (node == 0)
		current = head = tail;
	else
		node->next = tail;
	n_members++;
}

void
GeomObjList::append(const GeomObjList &list)
{
	GeomObjListNode::reference(list.head);
	if (head == 0)
		current = head = list.head;
	else {
		tail->next = list.head;
		if (list.head != 0)
			list.head->prev = tail;
	}
	tail = list.tail;
	n_members += list.n_members;
}

void
GeomObjList::prepend(const GeomObjList &list)
{
	GeomObjListNode *h = list.head;
	if (h != 0) {
		GeomObjListNode *node = new GeomObjListNode(h->obj);
		node->prev = 0;
		GeomObjListNode *trailer = node;
		for (h = h->next; h != 0; h = h->next) {
			GeomObjListNode *n = new GeomObjListNode(h->obj);
			trailer->next = n;
			n->prev = trailer;
			trailer = n;
		}
		trailer->next = head;
		if (head != 0) {
			head->prev = trailer;
			n_members += list.n_members;
			current_index += list.n_members;
		}
		else {
			current = node;
			current_index = 0;
		}
		head = node;
	}
}

void
GeomObjList::del(const GeomObj &obj)
{
	GeomObjListNode *h = head;

	for ( ; ; ) {
		if (h == 0) {
			tail = head = h;
			return;
		}
		else if (h->obj == obj) {
			GeomObjListNode *n = h->next;
			if (n != 0)
				n->prev = 0;
			if (--h->ref == 0)
				delete h;
			h = n;
			n_members--;
		}
		else
			break;
	}

	GeomObjListNode *new_tail = h;
	GeomObjListNode *node = h->next;
	while (node != 0) {
		if (node->obj == obj) {
			GeomObjListNode *n = node->next;
			if (n != 0)
				n->prev = node->prev;
			if (--node->ref == 0)
				delete node;
			new_tail->next = n;
			node = n;
			n_members--;
		}
		else {
			new_tail = node;
			node = node->next;
		}
	}
	head = h;
	tail = new_tail;
	current = head;
	current_index = 0;
}

void
GeomObjList::del_last(const GeomObj &obj)
{
	GeomObjListNode *t = tail;

	if (t == 0)
		return;

	if (t->obj == obj) {
		GeomObjListNode *p = t->prev;
		if (p != 0)
			p->next = 0;
		else
			head = 0;
		tail = p;
		if (--t->ref == 0)
			delete t;
		n_members--;
		current = head;
		current_index = 0;
		return;
	}

	GeomObjListNode *new_head = t;
	GeomObjListNode *node = t->prev;
	while (node != 0) {
		if (node->obj == obj) {
			GeomObjListNode *p = node->prev;
			if (p != 0)
				p->next = node->next;
			else
				head = new_head;
			new_head->prev = p;
			if (--node->ref == 0)
				delete node;
			n_members--;
			current = head;
			current_index = 0;
			return;
		}
		else {
			new_head = node;
			node = node->prev;
		}
	}
}

const GeomObj &
GeomObjList::operator[](int i) const
{
#ifdef ERROR_CHECKING
	if (head == 0 || i < 0 || i > n_members - 1)
		throw RangeViolation();
#endif

	if (i >= current_index) {
		while (current_index < i) {
			const_cast<GeomObjList *>(this)->current
					= current->next;
			const_cast<GeomObjList *>(this)->current_index++;
		}
		return current->obj;
	}
	else {
		while (current_index > i) {
			const_cast<GeomObjList *>(this)->current
					= current->prev;
			const_cast<GeomObjList *>(this)->current_index--;
		}
		return current->obj;
	}
}
