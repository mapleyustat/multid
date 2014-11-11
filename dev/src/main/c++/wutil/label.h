#ifndef _label_h
#define _label_h

#include <string>
#include <iostream>

#define label_IMANIP(typ)	imanip_ ## typ

#define label_IOMANIPdeclare(typ)                                             \
class label_IMANIP(typ) {                                                     \
        std::istream& (*_fn)(std::istream&, typ);                             \
        typ _ag;                                                              \
public:                                                                       \
        label_IMANIP(typ)(std::istream& (*_f)(std::istream&, typ), typ _z ) : \
                _fn(_f), _ag(_z) { }                                          \
        friend std::istream& operator>>(std::istream& _s,                     \
			const label_IMANIP(typ)& _f) {                        \
                return(*_f._fn)(_s, _f._ag); }                                \
        }

typedef const std::string &_RCS;
label_IOMANIPdeclare(_RCS);

label_IMANIP(_RCS) label(_RCS lab);
label_IMANIP(_RCS) expect(_RCS lab);

// Control macros:
//
//	label_NO_DEBUG -- turn off all debugging

extern int label_debugging_level;	// 0, 1, 2, or 3

#endif /* _label_h */
