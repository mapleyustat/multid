#ifdef __GNUC__
#pragma implementation
#endif
#include "TextButton.h"

TextButton::TextButton(const Panel& parent__)
	: PanelButton(parent__),
	  window_(0)
{
	display_label("Text...");
}

TextButton::~TextButton()
{
	delete window_;
}

void
TextButton::proc()
{
	if (!window_) {
		window_ = new TextWin(parent().parent());
		window_->load("../gui.txt");
	}
	window_->show();
}
