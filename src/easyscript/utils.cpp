/*
 * This file is part of EasyScript.
 *
 * EasyScript is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EasyScript is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with EasyScript. If not, see <http://www.gnu.org/licenses/>.
 */

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
