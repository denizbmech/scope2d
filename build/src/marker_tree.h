/*
This file is part of scope2d.

scope2d: Data Visualization and Analysis Software
Copyright (C) 2017  Deniz Bilgili

scope2d is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

scope2d is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with scope2d.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MARKER_TREE_H
#define MARKER_TREE_H

#include <exception>

#include <QWidget>
#include <QTreeView>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QStringList>
#include <QModelIndex>
#include <QPoint>
#include <QMenu>
#include <QAction>
#include <QColor>
#include <QFont>
#include <QColorDialog>
#include <QFontDialog>
#include <QMessageBox>
#include <QInputDialog>

#include "plot_marker_instance.h"
#include "add_marker_side_bands_window.h"
#include "move_marker_window.h"
#include "plot_marker_info_window.h"


class MarkerTree: public QTreeView {

/*
	Main marker tree object. Deals with most marker operations. For operations
	which require connection to other main modules (e.g. Charters), marker tree
	signals marker objects out to connect to other main modules.
*/

public:
	MarkerTree(QWidget* parent);

	void append_marker(PlotMarkerInstance* marker, QString charterLabel);

	virtual ~MarkerTree() {}

private:
	Q_OBJECT

	QStandardItemModel* m_itemModel;
	QPoint m_currentPos;
	QStandardItem* m_currentItem;
	QModelIndex m_currentIndex;

	void m_init_item_model();
	
public slots:
	void make_context_menu(const QPoint& pos);
	void make_add_harmonics_window();
	void delete_harmonics();
	void make_add_side_bands_window();
	void add_side_bands(double sideBandGap, int bandCount);
	void delete_side_bands();
	void request_draw_marker();
	void toggle_marker();
	void delete_marker();
	void make_move_marker_window();
	void move_marker(QPointF moveTo);
	void set_marker_color();
	void set_marker_font();
	void rotate_marker_label();
	void make_marker_info_window();

	void manage_marker_name_changed(QStandardItem* marker);

signals:
	void drawMarkerRequested(PlotMarkerInstance*);

};

#endif // !MARKER_TREE_H
