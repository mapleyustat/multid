#include <iomanip>
#include "label.h"

int label_debugging_level = 0;

static int
find_char(std::istream &is, char sought)
{
#ifndef label_NO_DEBUG
	if (label_debugging_level >= 3)
		std::cerr << "label(): find_char('" << sought << "'):\n";
#endif
	if (!is)
		return 0;

	char c;
	while (is.get(c) && !is.eof()) {
#ifndef label_NO_DEBUG
		if (label_debugging_level >= 3)
			std::cerr << "c = " << static_cast<int>(c)
				<< " = '" << c << "'\n";
#endif
		if (c == sought) {
			is.putback(c);
#ifndef label_NO_DEBUG
			if (label_debugging_level >= 3)
				std::cerr << "found '" << c << "'\n";
#endif
			return 1;
		}
	}
#ifndef label_NO_DEBUG
	if (label_debugging_level >= 3)
		std::cerr << "failed to find '" << sought << "'\n";
#endif
	return 0;
}

static std::istream &
find_label(std::istream &is, const std::string &label)
{
        static const unsigned int MAX_LENGTH = 1023;
	static char buffer[MAX_LENGTH + 1];

	if (!is)
		return is;

#ifndef label_NO_DEBUG
	if (label_debugging_level >= 1)
		std::cerr << "label(): searching for '" << label << "'\n";
#endif

	std::string::size_type len = label.length();
	if (len == 0)
		return is;
	if (len > MAX_LENGTH) {
#ifndef label_NO_DEBUG
		if (label_debugging_level >= 1)
			std::cerr << "label(): label.length() = " << len
				<< " > MAX_LENGTH = " << MAX_LENGTH << "\n";
#endif
		is.clear(std::ios::failbit|is.rdstate());
		return is;
	}

	std::streampos current_position = is.tellg();

	// first pass through std::istream,
	// from current position to the end

	while (find_char(is, label[0])) {
		if (!is.read(buffer, len))
			break;
		buffer[len] = '\0';
#ifndef label_NO_DEBUG
		if (label_debugging_level >= 2)
			std::cerr << "label(): first read: '"
				<< buffer << "'\n";
#endif
		if (buffer == label) {
#ifndef label_NO_DEBUG
			if (label_debugging_level >= 1)
				std::cerr << "label(): found it\n";
#endif
			return is;
		}
#ifndef label_NO_DEBUG
		if (label_debugging_level >= 2)
			std::cerr << "label(): not a match\n";
#endif
		std::streamoff offset = - static_cast<int>(len) + 1;
		if (!is.seekg(offset, std::ios::cur))
			return is;
	}

	// second pass through std::istream,
	// from beginning to the end

#ifndef label_NO_DEBUG
	if (label_debugging_level >= 1)
		std::cerr << "label(): second pass through file\n";
	if (label_debugging_level >= 2) {
		std::cerr << "label(): after first pass: ";
		std::cerr << "is.rdstate() = "
			<< static_cast<int>(is.rdstate()) << "\n";
	}
#endif
	is.clear(~(std::ios::eofbit|std::ios::failbit)&is.rdstate());
#ifndef label_NO_DEBUG
	if (label_debugging_level >= 2) {
		std::cerr << "label(): after clearing eofbit and failbit: ";
		std::cerr << "is.rdstate() = "
			<< static_cast<int>(is.rdstate()) << "\n";
	}
#endif
	if (!is.seekg(0, std::ios::beg))
		return is;
#ifndef label_NO_DEBUG
	if (label_debugging_level >= 2) {
		std::cerr << "label(): after seekg() to beginning: ";
		std::cerr << "is.rdstate() = "
			<< static_cast<int>(is.rdstate()) << "\n";
	}
#endif
	while (find_char(is, label[0])) {
		if (!is.read(buffer, len))
			break;
		buffer[len] = '\0';
#ifndef label_NO_DEBUG
		if (label_debugging_level >= 2)
			std::cerr << "label(): second read: '"
				<< buffer << "'\n";
#endif
		if (buffer == label) {
#ifndef label_NO_DEBUG
			if (label_debugging_level >= 1)
				std::cerr << "label(): found it\n";
#endif
			return is;
		}
		std::streamoff offset = - static_cast<int>(len) + 1;
		if (!is.seekg(offset, std::ios::cur))
			return is;
	}

#ifndef label_NO_DEBUG
	if (label_debugging_level >= 2) {
		std::cerr << "label(): after second pass: ";
		std::cerr << "is.rdstate() = "
			<< static_cast<int>(is.rdstate()) << "\n";
	}
#endif
	is.clear(~(std::ios::eofbit|std::ios::failbit)&is.rdstate());
#ifndef label_NO_DEBUG
	if (label_debugging_level >= 2) {
		std::cerr << "label(): after clearing eofbit and failbit: ";
		std::cerr << "is.rdstate() = "
			<< static_cast<int>(is.rdstate()) << "\n";
	}
#endif
	if (!is.seekg(current_position))
		return is;
#ifndef label_NO_DEBUG
	if (label_debugging_level >= 2) {
		std::cerr << "label(): after seekg() to current position: ";
		std::cerr << "is.rdstate() = "
			<< static_cast<int>(is.rdstate()) << "\n";
	}
#endif
	is.clear(std::ios::failbit|is.rdstate());
#ifndef label_NO_DEBUG
	if (label_debugging_level >= 1)
		std::cerr << "label(): failed to find '" << label << "'\n";
#endif

	return is;
}

label_IMANIP(_RCS)
label(_RCS lab)
{
	return label_IMANIP(_RCS)(find_label, lab);
}

static std::istream &
expect_label(std::istream &is, const std::string &lab)
{
	// TODO: don't use label(); rather, check that next string is correct
	if (!(is >> label(lab)))
		is.clear(std::ios::badbit|is.rdstate());
	return is;
}

label_IMANIP(_RCS)
expect(_RCS lab)
{
	return label_IMANIP(_RCS)(expect_label, lab);
}
