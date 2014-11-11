#ifndef _TextButton_h
#define _TextButton_h
#ifdef __GNUC__
#pragma interface
#endif

#include <PanelButton.h>
#include <TextWin.h>

class TextButton
	: public PanelButton
{
public:
	TextButton(const Panel& parent__);
	~TextButton(void);

	void proc(void);

private:
	TextButton(const TextButton &); // Do not define.
	TextButton &operator=(const TextButton &); // Do not define.

	TextWin *window_;
};

#endif /* _TextButton_h */
