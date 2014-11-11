#ifdef __GNUC__
#pragma implementation
#endif
#include <Pairing.h>
#include <Scene.h>

PairingNode::~PairingNode(void)
{
}

void
PairingNode::dereference(PairingNode *node)
{
	while (node != 0 && --node->ref == 0) {
		PairingNode *n = node->next;
		if (n != 0)
			n->prev = node->prev;
		delete node;
		node = n;
	}
}

Pairing &
Pairing::operator=(const Pairing &list)
{
	if (this != &list) {
		PairingNode::dereference(head);
		PairingNode::reference(list.head);
		head = list.head;
		tail = list.tail;
	}
	return *this;
}

void
Pairing::append(const Pairing &list)
{
	PairingNode::reference(list.head);
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
Pairing::prepend(const Pairing &list)
{
	PairingNode *h = list.head;
	if (h != 0) {
		PairingNode *node = new PairingNode(h->preimage, h->image);
		node->prev = 0;
		PairingNode *trailer = node;
		for (h = h->next; h != 0; h = h->next) {
			PairingNode *n
				= new PairingNode(h->preimage, h->image);
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
Pairing::join(const Scene &preimage_, const Scene &image_)
{
	// NOTE:  The join routine assumes that the GeomObjs on the
	// preimage and image Scenes are in one-to-one correspondence.
	for (int i = 0; i < preimage_.n_geom_objs(); ++i)
		add(preimage_[i], image_[i]);
}

void
Pairing::del(const GeomObj &preimage_)
{
	PairingNode *h = head;

	for ( ; ; ) {
		if (h == 0) {
			tail = head = h;
			return;
		}
		else if (h->preimage == preimage_) {
			PairingNode *n = h->next;
			if (n != 0)
				n->prev = 0;
			if (--h->ref == 0)
				delete h;
			h = n;
		}
		else
			break;
	}

	PairingNode *p = h;
	PairingNode *node = h->next;
	while (node != 0) {
		if (node->preimage == preimage_) {
			PairingNode *n = node->next;
			if (n != 0)
				n->prev = node->prev;
			if (--node->ref == 0)
				delete node;
			p->next = n;
			node = n;
		}
		else {
			p = node;
			node = node->next;
		}
	}
	head = h;
	tail = p;
}

GeomObj
Pairing::del_last(const GeomObj &preimage_)
{
	PairingNode *t = tail;

	if (t == 0)
		throw EmptyList();

	if (t->preimage == preimage_) {
		GeomObj image_ = t->image;
		PairingNode *p = t->prev;
		if (p != 0)
			p->next = 0;
		else
			head = 0;
		tail = p;
		if (--t->ref == 0)
			delete t;
		return image_;
	}

	PairingNode *n = t;
	PairingNode *node = t->prev;
	while (node != 0) {
		if (node->preimage == preimage_) {
			GeomObj image_ = node->image;
			PairingNode *p = node->prev;
			if (p != 0)
				p->next = node->next;
			else
				head = n;
			n->prev = p;
			if (--node->ref == 0)
				delete node;
			return image_;
		}
		else {
			n = node;
			node = node->prev;
		}
	}

	throw PreimageNotFound();
}
