#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <tuple>

#include "option.h"

struct word {
	unsigned int index, length;
	bool is_link;
	unsigned int linkidx;
};

struct link {
	std::string destination;
	std::string text;
};

// the contents of the file, the offsets of words in the file, and the links
// in the file.
//
// this is kept around to make reflow fast.
typedef std::tuple<std::string, std::vector<word>, std::vector<std::string> > fileinfo;

option<link> parse_link(std::istream&);
word parse_word(std::istream&, std::ostream&);

std::string eat_word(std::istream&);

class browser {
	// Store a mapping from filename to its offset information.
	std::unordered_map<std::string, fileinfo> data;

	public:

	void add_file(std::string);
};
