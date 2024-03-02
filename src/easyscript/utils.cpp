#include "utils.h"

bool Utils::ReadLine(std::istream& is, std::string& line_out) {
	std::istream::sentry se(is, true);
	std::streambuf* sb = is.rdbuf();

	if (!is) {
		return false;
	}

	line_out.clear();

	for(;;) {
		int c = sb->sbumpc();
		switch (c) {
		case '\n':
			return true;
		case '\r':
			if (sb->sgetc() == '\n') {
				sb->sbumpc();
			}
			return true;
		case EOF:
			// Also handle the case when the last line has no line ending
			if (line_out.empty()) {
				is.setstate(std::ios::eofbit);
				return false;
			}
			return true;
		default:
			line_out += (char)c;
		}
	}
}
