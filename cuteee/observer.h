#pragma once
#include <vector>

using std::vector;
class Observer {
public:
	virtual void update() = 0;
};

class Observable : public Observer {
private:
	vector<Observer*> lst;
public:
	void add_obs(Observer* obs) {
		lst.push_back(obs);
	}
	void remove_obs(Observer* obs) {
		auto it = std::find(lst.begin(), lst.end(), obs);
		lst.erase(it, lst.end());
	}
protected:
	void notify() {
		for (auto obs : lst) {
			obs->update();
		}
	}
};