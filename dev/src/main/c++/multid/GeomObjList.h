#ifndef _GeomObjList_h
#define _GeomObjList_h
#ifdef __GNUC__
#pragma interface
#endif

#include <GeomObj.h>
#include <Pix.h>

// NOTE:  This list class is adapted from the one described by
// Lippman in his second edition of the C++Primer.  The handling
// of references is adapted from List.{h,cc}P in the GNU C++ library.

class GeomObjListNode
{
private:
	GeomObjListNode(const GeomObj &geom_obj);
	GeomObjListNode(const GeomObj &geom_obj, GeomObjListNode *next_,
			GeomObjListNode *prev_);
	GeomObjListNode(const GeomObjListNode &); // Do not define.
	GeomObjListNode &operator=(const GeomObjListNode &); // Do not define.

	static void reference(GeomObjListNode *node);
	static void dereference(GeomObjListNode *node);

	const GeomObj obj;
	GeomObjListNode *next;
	GeomObjListNode *prev;
	short ref;

	friend class GeomObjList;
};

inline
GeomObjListNode::GeomObjListNode(const GeomObj &geom_obj)
	: obj(geom_obj),
	  next(0),
	  prev(0),
	  ref(1)
{
}

inline
GeomObjListNode::GeomObjListNode(const GeomObj &geom_obj,
		GeomObjListNode *next_, GeomObjListNode *prev_)
	: obj(geom_obj),
	  next(next_),
	  prev(prev_),
	  ref(1)
{
}

inline void
GeomObjListNode::reference(GeomObjListNode *node)
{
	if (node != 0)
		++node->ref;
}

class GeomObjList
{
public:
	GeomObjList(void);
	GeomObjList(const GeomObj &obj);
	GeomObjList(const GeomObjList &list);
	~GeomObjList(void);
	GeomObjList &operator=(const GeomObjList &list);

	int null(void) const;

	void empty(void);
	void append(const GeomObj &obj);
	void append(const GeomObjList &list);
	void prepend(const GeomObj &obj);
	void prepend(const GeomObjList &list);
	void del(const GeomObj &obj); // delete all nodes with obj
	void del_last(const GeomObj &obj); // delete the last node with obj

	Pix first(void) const;
	Pix last(void) const;
	void next(Pix &p) const;
	void prev(Pix &p) const;
	const GeomObj &operator()(Pix p) const;

	int n_geom_objs(void) const;
	const GeomObj &operator[](int i) const;

	class RangeViolation
		: public std::exception { };

private:
	GeomObjListNode *head;
	GeomObjListNode *tail;
	int n_members;
	GeomObjListNode *current;
	int current_index;
};

inline
GeomObjList::GeomObjList(void)
	: head(0),
	  tail(0),
	  n_members(0),
	  current(0),
	  current_index(0)
{
}

inline
GeomObjList::GeomObjList(const GeomObj &obj)
	: head(new GeomObjListNode(obj, 0, 0)),
	  tail(head),
	  n_members(1),
	  current(head),
	  current_index(0)
{
}

inline
GeomObjList::GeomObjList(const GeomObjList &list)
	: head(list.head),
	  tail(list.tail),
	  n_members(list.n_members),
	  current(list.current),
	  current_index(list.current_index)
{
	GeomObjListNode::reference(list.head);
}

inline
GeomObjList::~GeomObjList(void)
{
	GeomObjListNode::dereference(head);
}

inline GeomObjList &
GeomObjList::operator=(const GeomObjList &list)
{
	if (this != &list) {
		GeomObjListNode::dereference(head);
		GeomObjListNode::reference(list.head);
		head = list.head;
		tail = list.tail;
		n_members = list.n_members;
		current = list.current;
		current_index = list.current_index;
	}
	return *this;
}

inline int
GeomObjList::null(void) const
{
	return head == 0;
}

inline void
GeomObjList::empty(void)
{
	GeomObjListNode::dereference(head);
	head = 0;
	tail = 0;
	n_members = 0;
	current = 0;
	current_index = 0;
}

inline void
GeomObjList::prepend(const GeomObj &obj)
{
	GeomObjListNode *node = head;
	head = new GeomObjListNode(obj, node, 0);
	if (node == 0)
		current = tail = head;
	else
		node->prev = head;
	n_members++;
	current_index++;
}

inline Pix
GeomObjList::first(void) const
{
	return Pix(head);
}

inline Pix
GeomObjList::last(void) const
{
	return Pix(tail);
}

inline const GeomObj &
GeomObjList::operator()(Pix p) const
{
	return reinterpret_cast<GeomObjListNode *>(p)->obj;
}

inline void
GeomObjList::next(Pix &p) const
{
	if (p != 0)
		p = Pix(reinterpret_cast<GeomObjListNode *>(p)->next);
}

inline void
GeomObjList::prev(Pix &p) const
{
	if (p != 0)
		p = Pix(reinterpret_cast<GeomObjListNode *>(p)->prev);
}

inline int
GeomObjList::n_geom_objs(void) const
{
	return n_members;
}

#endif
