#include <unordered_map>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <cctype>
#include <string>
#include <vector>
#include <tuple>

#include "browser.h"
#include "logging.h"

using namespace std;

void browser::add_file(string filename) {
	if (this->data.count(filename) == 1) {
		// file already in the map
		return;
	}

	fstream file(filename.c_str());

	if (!file) {
		cerr << "Error: opening file `" << filename << "` failed." << endl;
		// there's no real way to continue.
		exit(2);
	}

	stringstream contents;
	unsigned int idx = 0;
	unsigned int numlinks = 0;
	fileinfo info;

	// parse the file
	while (!file.eof()) {
		char c = file.get();

		// skip all whitespace
		if (isspace(c)) {
			continue;
		} else if (c == -1) {
			// FIXME: for some reason, EOF is not triggered above. It can be
			// caught here, but figure out why .eof() isn't working.
			std::get<0>(info) = contents.str();
			this->data[filename] = info;
			return;
		} else {
			file.unget();
		}

		// if we see a <, it's either the start of a link
		if ('<' == c) {
			// parse a link
			file.ignore(); // don't actually want to unget the <, since it's useless.
			auto l = parse_link(file);
			if (l.is_some()) {
				// make word from the link and push it to the fileinfo
				word x;
				link ln = l.unwrap();
				x.index = idx;
				x.length = ln.text.length();
				x.is_link = true;
				x.linkidx = numlinks;

				contents << ln.text;
				std::get<2>(info).push_back(ln.destination);
				idx += x.length;
				numlinks++;
			} else {
				cerr << "Error: parsing `" << filename << "`, expected link after `<`" << endl;
				exit(3);
			}
		} else {
			word x = parse_word(file, contents);
			x.index = idx;
			idx += x.length;
			std::get<1>(info).push_back(x);
		}
	}

	std::get<0>(info) = contents.str();
	this->data[filename] = info;
}

static option<link> parse_link(std::istream& file) {
	char c;
	file.exceptions(ifstream::failbit | ifstream::badbit | ifstream::eofbit);

	c = file.get();

	if (c != 'a') {
		return option<link>();
	}

	string dest, text;
	file >> dest >> text;

	if (text[text.length() - 1] == '>') {
		text = text.erase(text.length() - 1);
	} else {
		return option<link>();
	}
	file.exceptions(ifstream::goodbit);

	return option<link>({dest, text});
}

static word parse_word(std::istream& file, std::ostream& content) {
	string t;
	file >> t;
	content << t;
	word x;
	x.length = t.length();
	x.is_link = false;
	return x;
}
