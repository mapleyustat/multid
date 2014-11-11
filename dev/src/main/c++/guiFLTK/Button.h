#ifndef _Button_h
#define _Button_h

typedef long Button;

// NOTE: the following must be compatible with xview/win_input.h

#define BUTTON_PRESS	0x0400
#define BUTTON_RELEASE	0x0800
#define BUTTON_DRAG	0x1000
#define BUTTON_ACTION_MASK	(BUTTON_PRESS | BUTTON_RELEASE | BUTTON_DRAG)

#define BUTTON_SELECT	0x0080	// MS_LEFT_MASK
#define BUTTON_ADJUST	0x0100	// MS_MIDDLE_MASK
#define BUTTON_MENU	0x0200	// MS_RIGHT_MASK
#define BUTTON_TYPE_MASK	(BUTTON_SELECT | BUTTON_ADJUST | BUTTON_MENU)

#define BUTTON_NO_MODIFIER	0x0001
#define BUTTON_SHIFT	0x000E	// SHIFTMASK
#define BUTTON_CTRL	0x0030	// CTRLMASK
#define BUTTON_META	0x0040	// META_SHIFT_MASK
#define BUTTON_MODIFIER_MASK	(  BUTTON_NO_MODIFIER | BUTTON_SHIFT \
				 | BUTTON_CTRL | BUTTON_META)

#endif