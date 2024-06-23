#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_cuteee.h"
#include "service.h"
#include "observer.h"
#include <QTableView>
#include "table_model.h"
#include <QPushButton>
#include <QLabel>
#include <qboxlayout.h>
#include <qboxlayout.h>
#include <qboxlayout.h>
#include <qboxlayout.h>
#include <qboxlayout.h>
#include <qboxlayout.h>

class new_window : public Observer {
private:
	service& srv;
	int nr;
	string tip;
	QLabel* waw;
	QWidget* wdg;
	QHBoxLayout* ly;

	void init() {
		waw = new QLabel;
		wdg = new QWidget;
		ly = new QHBoxLayout;
		this->srv.add_obs(this);
		auto txt = std::to_string(nr);
		waw->setText(QString::fromStdString(txt));
		wdg->setWindowTitle(QString::fromStdString(tip));
		wdg->setLayout(ly);
		ly->addWidget(waw);
	}
public:
	new_window(service& sr, string t, int n)
		: nr{ n }, tip{ t }, srv{ sr } {
		init();
	}

	~new_window() {
		this->srv.remove_obs(this);
	}

	void update() override{
		int nr = this->srv.nr_tip(tip);
		string txt = std::to_string(nr);
		waw->setText(QString::fromStdString(txt));
	}

	void run() {
		wdg->show();
	}
};


class GUI : public QWidget {
private:
	service& srv;

	TableModel* table;
	QTableView* vw = new QTableView;

	QPushButton* add;
	QLabel* lbl_id;
	QLabel* lbl_nume;
	QLabel* lbl_tip;
	QLabel* lbl_pret;
	QLineEdit* edit_id;
	QLineEdit* edit_nume;
	QLineEdit* edit_tip;
	QLineEdit* edit_pret;

	QLabel* lbl_slider;
	QSlider* slider;

	QPushButton* flt;


	void init();
	void reload(vector<produs> ofrt, int nr);
	void connect();
public:
	GUI(service& sfd) : srv{ sfd } {
		init();
		table = new TableModel{ srv.sort_pret(), slider->value()};
		vw->setModel(table);
		connect();
		reload(srv.get_all_srv(), slider->value());

		auto cate = srv.get_tipuri();
		for (auto& f : cate) {
			auto wndw = new new_window(srv, f.first, f.second);
			wndw->run();
		}
	}
};
