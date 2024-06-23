#include "cuteee.h"
#include <QHBoxLayout>
#include <QFormLayout>
#include <qlineedit.h>
#include <warning.h>
#include <QMessageBox>

void GUI::init() {
	QHBoxLayout* ly_main = new QHBoxLayout;

	this->setLayout(ly_main);
	
	// FUNCTIONALITATI
	QWidget* left = new QWidget;
	QFormLayout* ly_lft = new QFormLayout;
	left->setLayout(ly_lft);

	lbl_id = new QLabel{ "ID:" };
	lbl_nume = new QLabel{ "NUME:" };
	lbl_tip = new QLabel{ "TIP:" };
	lbl_pret = new QLabel{ "PRET:" };

	edit_id = new QLineEdit;
	edit_nume = new QLineEdit;
	edit_tip = new QLineEdit;
	edit_pret = new QLineEdit;

	ly_lft->addRow(lbl_id, edit_id);
	ly_lft->addRow(lbl_nume, edit_nume);
	ly_lft->addRow(lbl_tip, edit_tip);
	ly_lft->addRow(lbl_pret, edit_pret);

	add = new QPushButton{ "adauga" };
	ly_lft->addRow(add);

	lbl_slider = new QLabel{ "0" };
	slider = new QSlider{ Qt::Horizontal };
	slider->setMinimum(0);
	slider->setMaximum(100);
	
	ly_lft->addRow(slider, lbl_slider);

	flt = new QPushButton{ "filtreaza" };
	ly_lft->addWidget(flt);

	// TABEL
	QWidget* right = new QWidget;
	QVBoxLayout* ly_tb = new QVBoxLayout;
	right->setLayout(ly_tb);

	ly_tb->addWidget(vw);

	ly_main->addWidget(left);
	ly_main->addWidget(right);
}

void GUI::reload(vector<produs> vec ,int nr) {
	std::sort(vec.begin(), vec.end(), [](produs a, produs b)
		{return a.get_pret() < b.get_pret(); });
	table->set_produse(vec, nr);
}

void GUI::connect() {
	QObject::connect(add, &QPushButton::clicked, [&] {
		int id = stoi(edit_id->text().toStdString());
		string nume = edit_nume->text().toStdString();
		string tip = edit_tip->text().toStdString();
		double pret = stof(edit_pret->text().toStdString());
		try {
			srv.add_srv(id, nume, tip, pret);
		}
		catch (std::exception& ex) {
			QMessageBox::warning(this, "EXCEPTION",
				QString::fromStdString(ex.what()));
		}
		catch (string s) {
			QMessageBox::warning(this, "EXCEPTION",
				QString::fromStdString(s));
		}
		reload(srv.sort_pret(), slider->value());
	});

	QObject::connect(slider, &QSlider::valueChanged, [&](int n) {
		lbl_slider->setText(QString::number(n));
		reload(srv.sort_pret(), slider->value());
	});

	QObject::connect(flt, &QPushButton::clicked, [&] {
		double nr = slider->value();
		reload(srv.flt_pret(nr), slider->value());
	});
}
