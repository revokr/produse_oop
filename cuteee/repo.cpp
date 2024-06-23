#include "repo.h"
#include <fstream>

void repo::clear() {
	lst.clear();
}

void repo::load_from_file() {
	clear();
	std::ifstream fin(file_path);

	string line;

	while (std::getline(fin, line)) {
		string id;
		string nume, tip;
		string pret;

		int nr = 0;

		for (auto c : line) {
			if (c == ',') {
				nr++;
			}

			if (nr == 0 && c != ',') {
				id += c;
			}
			if (nr == 1 && c != ',') {
				nume += c;
			}
			if (nr == 2 && c != ',') {
				tip += c;
			}
			if (nr == 3 && c != ',') {
				pret += c;
			}
		}

		int id1 = stoi(id);
		double pret1 = stof(pret);
		produs p{ id1, nume, tip, pret1 };
		repo::add(p);
	}
}

void repo::write_to_file() {
	std::ofstream out(file_path);

	for (auto p : get_all()) {
		out << p.get_id() << ",";
		out << p.get_nume() << ",";
		out << p.get_tip() << ",";
		out << p.get_pret() << '\n';
	}
}
