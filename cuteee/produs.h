#pragma once
#include <string>

using std::string;


class produs {
private:
	int id;
	string nume;
	string tip;
	double pret;
public:
	produs(int i, string n, string t, double p) : id{ i },
		nume{ n }, tip{ t }, pret{ p } {}

	int get_id() {
		return id;
	}

	string get_nume() {
		return nume;
	}

	string get_tip() {
		return tip;
	}

	double get_pret() {
		return pret;
	}

	bool operator==(const produs& p) {
		return id == p.id;
	}
};
