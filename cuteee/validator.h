#pragma once
#include "produs.h"

class vali {
private:
	string message;
public:
	vali() = default;

	string validate(produs p) {
		if (p.get_nume() == "") {
			message += "nume invalid\n";
		}
		if (p.get_pret() < 1 || p.get_pret() > 100) {
			message += "pret invalid";
		}
		return message;
	}
};