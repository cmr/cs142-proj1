#include <iostream>
#include <string>

#include "loader.h"
#include "browser.h"
#include "prompt.h"

using namespace std;

int main(int argc, char *argv[]) {
	// if given an arg, load that file, otherwise prompt
	string filename;

	if (argc == 1) {
		filename = prompt<string>("Load file");
	} else if (argc == 2) {
		filename = string(argv[1]);
	} else {
		cerr << "Error: too many arguments" << endl;
		cerr << "Usage: " << argv[0] << " [file]" << endl;
		return 1;
	}

	browser b;
	b.add_file(filename);
}
