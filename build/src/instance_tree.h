/*
This file is part of scope2d.

scope2d: 2-D Data Visualization and Analysis Software
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

#ifndef INSTANCE_TREE_H
#define INSTANCE_TREE_H

#include <string>

#include <QWidget>
#include <QTreeView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QModelIndex>
#include <QDialog>
#include <QString>
#include <QMenu>
#include <QPoint>
#include <QAction>
#include <QHeaderView>
#include <QFileDialog>
#include <QMessageBox>

#include "parent_instance.h"
#include "plot_request_window.h"
#include "plot_curve_style_manager_window.h"
#include "vector_calculator_window.h"
#include "delete_columns_window.h"
#include "curve_fitter_window.h"
#include "trendline_info_window.h"
#include "csv_writer.h"
#include "calculator.h"


class InstanceTree: public QTreeView {

/*
	Instance tree object for the main window. Currently, items are placed onto
	three levels:

	Level0: Parent (main) instance items. These items hold the numeric data
	blocks and share data with their attached child instances, which contain
	plot curve objects.

	Level1: Child instance items. These items hold and manage plot curve
	objects. They acquire the numeric data to plot from their parent instances.

	Level2: /coming soon/ Trendline instance items. They are similar to child
	instance items; but they instead keep the numeric data and the plot curve
	object necessary for each trendline.

	Instance tree deals with most operations (e.g. remove, delete, close,
	manage style) by itself, using helper objects such as PlotRequestWindow and
	PlotCurveStyleManagerWindow. However, when a direct connection to other
	main objects (e.g. Charters) is needed, it signals requests and lets other
	objects complete the task.
*/

public:
	InstanceTree(QWidget* parent = 0);

	void append_instance(ParentInstance* instance, QString typeName, 
		QString fileName);

	virtual ~InstanceTree() {}

private:
	Q_OBJECT

	QStandardItemModel* m_itemModel;
	QPoint m_currentPos;
	QModelIndex m_currentIndex;
	QStandardItem* m_currentItem;

	int m_find_item_level(QModelIndex itemIndex);
	void m_init_item_model();
	void m_make_level0_context_menu(const QPoint& pos);
	void m_make_level1_context_menu(const QPoint& pos);
	void m_make_level2_context_menu(const QPoint& pos);

	void m_show_calculation_result(double result, QString msg) const;

public slots:
	void manage_instance_name_changed(QStandardItem* instance);
	void make_context_menu(const QPoint& pos);
	void make_plot_request_window();
	void make_plot_curve_style_manager_window();
	void make_plots(int indepIndex, QList<int> depIndices);
	void remove_plot();
	void delete_plot();
	void close_instance();
	void make_calculate_instance_window();
	void catch_calculated_vector(ColVector v);
	void make_delete_columns_window();
	void delete_instance_data_columns(QList<int> indexesToDelete);
	void make_curve_fitter_window();
	void make_export_to_csv_window();
	void export_to_csv(ChildInstance* instance, QString exportAddress);
	void request_draw_curve();
	void make_trendline_info_window();
	void show_signal_max() const;
	void show_signal_min() const;
	void show_signal_mean() const;
	void show_signal_mode() const;
	void show_signal_median() const;
	void show_signal_rms() const;
	void show_signal_variance() const;
	void show_signal_std_dev() const;
	void show_signal_area_under_curve() const;

signals:
	void drawCurveRequested(PlotCurve*);
	
};

#endif // !INSTANCE_TREE_H
