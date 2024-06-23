#pragma once

#include "validator.h"
#include <vector>

using std::vector;


class repo {
private:
	string file_path;
	vector<produs> lst;

	void load_from_file();
	void write_to_file();

	void clear();
public:
	repo(string path) : file_path{ path } {
		load_from_file();
	}

	vector<produs> get_all() {
		return lst;
	}

	void add(produs p) {
		lst.push_back(p);
		write_to_file();
	}

	void erase(produs p) {
		auto itt = std::find(lst.begin(), lst.end(), p);
		if (itt != lst.end()) {
			lst.erase(itt);
		}
		write_to_file();
	}
};