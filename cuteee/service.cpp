#include "service.h"

void service::add_srv(int id, string nume, string tip, double pret) {
	vector<produs> list = rep.get_all();
	produs nou{ id, nume, tip, pret };
	if (std::find_if(list.begin(), list.end(),
		[&](produs o) {return o.get_id() == id; }) != list.end()) {
		throw std::exception("Produs existent!!");
	}
	string msg = val.validate(nou);
	if (msg.empty()) {
		rep.add(nou);
		notify();
	}
	else {
		throw msg;
	}
}

void service::erase_srv(int id) {
	vector<produs> list = rep.get_all();
	auto it = std::find_if(list.begin(), list.end(),
		[&](produs o) {return o.get_id() == id; });
	if (it == list.end()) {
		//throw std::exception("Produs inexistent!!");
	}
	rep.erase(*it);
}

vector<produs> service::sort_pret() {
	vector<produs> vec = get_all_srv();
	std::sort(vec.begin(), vec.end(), [](produs a, produs b)
		{return a.get_pret() < b.get_pret(); });
	return vec;
}

int service::nr_tip(string t) {
	int cnt = 0;
	for (auto c : get_all_srv()) {
		if (c.get_tip() == t) {
			cnt++;
		}
	}
	return cnt;
}

std::map<string, int> service::get_tipuri()
{
	std::map<string, int> mp;
	for (auto c : get_all_srv()) {
		mp[c.get_tip()]++;
	}
	return mp;
}
