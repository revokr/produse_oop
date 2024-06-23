#pragma once
#include "observer.h"
#include "repo.h"
#include <algorithm>
#include <map>

class service : public Observable {
private:
	repo& rep;
	vali& val;
public:
	service(repo& op, vali& v) : rep{ op }, val{ v } {}

	vector<produs> get_all_srv() {
		return rep.get_all();
	}

	void add_srv(int id, string nume, string tip, double pret);

	void erase_srv(int id);

	vector<produs> sort_pret();

	vector<produs> flt_pret(double pret) {
		vector<produs> res;
		for (auto p : get_all_srv()) {
			if (p.get_pret() <= pret) {
				res.push_back(p);
			}
		}
		return res;
	}

	void update() override {

	}

	int nr_tip(string t);

	std::map<string, int> get_tipuri();
};