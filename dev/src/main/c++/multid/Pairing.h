#ifndef _Pairing_h
#define _Pairing_h
#ifdef __GNUC__
#pragma interface
#endif

#include <exception>
#include <Pix.h>
#include <GeomObj.h>

class Scene;

// NOTE:  This list class is adapted from the one described by
// Lippman in his second edition of the C++Primer.  The handling
// of references is adapted from DL.{h,cc}P in the GNU C++ library.

class PairingNode
{
private:
	PairingNode(const GeomObj &preimage_, const GeomObj &image_);
	PairingNode(const GeomObj &preimage_, const GeomObj &image_,
			PairingNode *next_, PairingNode *prev_);
	PairingNode(const PairingNode &); // Do not define.
	~PairingNode(void);
	PairingNode &operator=(const PairingNode &); // Do not define.

	static void reference(PairingNode *node);
	static void dereference(PairingNode *node);

	GeomObj preimage;
	GeomObj image;
	PairingNode *next;
	PairingNode *prev;
	short ref;

	friend class Pairing;
};

inline
PairingNode::PairingNode(const GeomObj &preimage_, const GeomObj &image_)
	: preimage(preimage_),
	  image(image_),
	  next(0),
	  prev(0),
	  ref(1)
{
}

inline
PairingNode::PairingNode(const GeomObj &preimage_, const GeomObj &image_,
		PairingNode *next_, PairingNode *prev_)
	: preimage(preimage_),
	  image(image_),
	  next(next_),
	  prev(prev_),
	  ref(1)
{
}

inline void
PairingNode::reference(PairingNode *node)
{
	if (node != 0)
		++node->ref;
}

class Pairing
{
public:
	Pairing(void);
	~Pairing(void);

	void empty(void);
	// NOTE:  The join routine assumes that the GeomObjs on the
	// preimage and image Scenes are in one-to-one correspondence.
	void join(const Scene &preimage, const Scene &image);
	void add(const GeomObj &preimage, const GeomObj &image);
	void del(const GeomObj &preimage);
	GeomObj del_last(const GeomObj &preimage); // returns the image
	GeomObj image(const GeomObj &preimage);
	GeomObj preimage(const GeomObj &image);

	class ImageNotFound
		: public std::exception { };
	class PreimageNotFound
		: public std::exception { };
	class EmptyList
		: public std::exception { };

private:
	Pairing(const GeomObj &preimage, const GeomObj &image);
	Pairing(const Pairing &list);
	Pairing &operator=(const Pairing &list);

	int null(void) const;

	void append(const GeomObj &preimage, const GeomObj &image);
	void append(const Pairing &list);
	void prepend(const GeomObj &preimage, const GeomObj &image);
	void prepend(const Pairing &list);

	Pix first(void) const;
	Pix last(void) const;
	void next(Pix &p) const;
	void prev(Pix &p) const;

	PairingNode *head;
	PairingNode *tail;
};

inline
Pairing::Pairing(void)
	: head(0),
	  tail(0)
{
}

inline
Pairing::Pairing(const GeomObj &preimage_, const GeomObj &image_)
	: head(new PairingNode(preimage_, image_, 0, 0)),
	  tail(head)
{
}

inline
Pairing::Pairing(const Pairing &list)
	: head(list.head),
	  tail(list.tail)
{
	PairingNode::reference(list.head);
}

inline
Pairing::~Pairing(void)
{
	PairingNode::dereference(head);
}

inline int
Pairing::null(void) const
{
	return head == 0;
}

inline void
Pairing::empty(void)
{
	PairingNode::dereference(head);
	head = 0;
	tail = 0;
}

inline void
Pairing::append(const GeomObj &preimage_, const GeomObj &image_)
{
	PairingNode *node = tail;
	tail = new PairingNode(preimage_, image_, 0, node);
	if (node == 0)
		head = tail;
	else
		node->next = tail;
}

inline void
Pairing::prepend(const GeomObj &preimage_, const GeomObj &image_)
{
	PairingNode *node = head;
	head = new PairingNode(preimage_, image_, node, 0);
	if (node == 0)
		tail = head;
	else
		node->prev = head;
}

inline Pix
Pairing::first(void) const
{
	return Pix(head);
}

inline Pix
Pairing::last(void) const
{
	return Pix(tail);
}

inline void
Pairing::next(Pix &p) const
{
	if (p != 0)
		p = Pix(reinterpret_cast<PairingNode *>(p)->next);
}

inline void
Pairing::prev(Pix &p) const
{
	if (p != 0)
		p = Pix(reinterpret_cast<PairingNode *>(p)->prev);
}

inline void
Pairing::add(const GeomObj &preimage_, const GeomObj &image_)
{
	append(preimage_, image_);
}

inline GeomObj
Pairing::image(const GeomObj &preimage_)
{
	for (PairingNode *p = tail; p != 0; p = p->prev)
		if (p->preimage == preimage_)
			return p->image;
	throw ImageNotFound();
}

inline GeomObj
Pairing::preimage(const GeomObj &image_)
{
	for (PairingNode *p = tail; p != 0; p = p->prev)
		if (p->image == image_)
			return p->preimage;
	throw ImageNotFound();
}

#endif
