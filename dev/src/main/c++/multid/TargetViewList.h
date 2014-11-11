#ifndef _TargetViewList_h
#define _TargetViewList_h
#ifdef __GNUC__
#pragma interface
#endif

#include <Pix.h>

class TargetView;

// NOTE:  This list class is adapted from the one described by
// Lippman in his second edition of the C++Primer.  The handling
// of references is adapted from LList.{h,cc}P in the GNU C++ library.

class TargetViewListNode
{
private:
	TargetViewListNode(TargetView &obj_);
	TargetViewListNode(TargetView &obj_, TargetViewListNode *next_);

	static void reference(TargetViewListNode *node);
	static void dereference(TargetViewListNode *node);

	TargetView &obj;
	TargetViewListNode *next;
	short ref;

	friend class TargetViewList;
};

inline
TargetViewListNode::TargetViewListNode(TargetView &obj_)
	: obj(obj_),
	  next(0),
	  ref(1)
{
}

inline
TargetViewListNode::TargetViewListNode(TargetView &obj_,
		TargetViewListNode *next_)
	: obj(obj_),
	  next(next_),
	  ref(1)
{
}

inline void
TargetViewListNode::reference(TargetViewListNode *node)
{
	if (node != 0)
		++node->ref;
}

inline void
TargetViewListNode::dereference(TargetViewListNode *node)
{
	while (node != 0 && --node->ref == 0) {
		TargetViewListNode *n = node->next;
		delete node;
		node = n;
	}
}

class TargetViewList
{
public:
	TargetViewList(void);
	TargetViewList(TargetView &obj);
	TargetViewList(const TargetViewList &list);
	~TargetViewList(void);
	TargetViewList &operator=(const TargetViewList &list);

	int null(void) const;

	void empty(void);
	void append(TargetView &obj);
	void append(const TargetViewList &list);
	void prepend(TargetView &obj);
	void prepend(const TargetViewList &list);
	void del(const TargetView &obj);

	Pix first(void) const;
	void next(Pix &p) const;
	const TargetView &operator()(Pix p) const;
	TargetView &operator()(Pix p);

private:
	TargetViewListNode *head;
	TargetViewListNode *tail;
};

inline
TargetViewList::TargetViewList(void)
	: head(0),
	  tail(0)
{
}

inline
TargetViewList::TargetViewList(TargetView &obj)
	: head(new TargetViewListNode(obj, 0)),
	  tail(head)
{
}

inline
TargetViewList::TargetViewList(const TargetViewList &list)
	: head(list.head),
	  tail(list.tail)
{
	TargetViewListNode::reference(list.head);
}

inline
TargetViewList::~TargetViewList(void)
{
	TargetViewListNode::dereference(head);
}

inline int
TargetViewList::null(void) const
{
	return head == 0;
}

inline void
TargetViewList::empty(void)
{
	TargetViewListNode::dereference(head);
	head = 0;
	tail = 0;
}

inline void
TargetViewList::append(TargetView &obj)
{
	TargetViewListNode *node = new TargetViewListNode(obj, 0);
	if (head == 0)
		head = node;
	else
		tail->next = node;
	tail = node;
}

inline void
TargetViewList::prepend(TargetView &obj)
{
	TargetViewListNode *node = head;
	head = new TargetViewListNode(obj, node);
	if (node == 0)
		tail = head;
}

inline Pix
TargetViewList::first(void) const
{
	return Pix(head);
}

inline void
TargetViewList::next(Pix &p) const
{
	if (p != 0)
		p = Pix(reinterpret_cast<TargetViewListNode *>(p)->next);
}

inline const TargetView &
TargetViewList::operator()(Pix p) const
{
	return reinterpret_cast<TargetViewListNode *>(p)->obj;
}

inline TargetView &
TargetViewList::operator()(Pix p)
{
	return reinterpret_cast<TargetViewListNode *>(p)->obj;
}

#endif
