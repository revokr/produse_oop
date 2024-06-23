#pragma once
#include <vector>
#include "produs.h"
#include <QAbstractTableModel>



class TableModel : public QAbstractTableModel {
private:
	std::vector<produs> lst;
	int nr;
	
public:
	TableModel(std::vector<produs> p, int nr) : lst{ p }, nr{ nr } {}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override{
		return lst.size();
	}

	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 5;
	}

	QVariant data(const QModelIndex& ind, int role = Qt::DisplayRole) const override {
		if (role == Qt::BackgroundRole) {
			auto p = lst[ind.row()];
			double pret = p.get_pret();
			if ((int)pret <= nr) {
				QBrush bg(Qt::darkRed);
				return bg;
			}
		}
		if (role == Qt::DisplayRole && ind.row() < lst.size()) {
			produs p = lst[ind.row()];
			int cnt = 0;
			for (auto c : p.get_nume()) {
				if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
					cnt++;
				}
			}
			if (ind.column() == 0) {
				return QString::fromStdString(std::to_string(p.get_id()));
			}
			if (ind.column() == 1) {
				return QString::fromStdString(p.get_nume());
			}
			if (ind.column() == 2) {
				return QString::fromStdString(p.get_tip());
			}
			if (ind.column() == 3) {
				return QString::fromStdString(std::to_string(p.get_pret()));
			}
			if (ind.column() == 4) {
				return QString::fromStdString(std::to_string(cnt));
			}
		}

		return QVariant{};
	}

	void set_produse(std::vector<produs> ofrt ,int nr) {
		this->lst = ofrt;
		this->nr = nr;
		auto top_lft = createIndex(0, 0);
		auto bot_r = createIndex(rowCount(), columnCount());
		emit dataChanged(top_lft, bot_r);
		emit layoutChanged();
	}
};