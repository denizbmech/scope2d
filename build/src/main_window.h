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

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <string>

#include <QGridLayout>
#include <QVBoxLayout>
#include <QMainWindow>
#include <QWidget>
#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QColor>
#include <QBrush>
#include <QPen>
#include <QStringList>
#include <QSplitter>
#include <QList>
#include <QIcon>
#include <QColorDialog>
#include <QToolBar>
#include <QLayout>
#include <QSizePolicy>
#include <QRectF>
#include <QFileDialog>
#include <QRect>
#include <QMessageBox>

#include "charter_with_legend.h"
#include "main_menubar.h"
#include "main_toolbar.h"
#include "instance_tree.h"
#include "marker_tree.h"
#include "plot_curve.h"
#include "abstract_plot_marker.h"
#include "new_csv_instance_window.h"
#include "new_uff58_instance_window.h"
#include "new_marker_window.h"
#include "parent_instance.h"


class MainWindow: public QMainWindow {

/*
	Main window object of the program. Acts as a user/arranger of all processes
	created by other classes.
*/

public:
	MainWindow(QWidget* parent = 0);

	virtual ~MainWindow();

private:
	Q_OBJECT

	CharterWithLegend* m_charter1;
	CharterWithLegend* m_charter2;
	CharterWithLegend* m_charter3;
	Charter* m_activeCharter;
	QWidget* m_charterAreaWidget;
	QVBoxLayout* m_charterAreaLayout;
	
	QGridLayout* m_gridLayout;
	QWidget* m_centralWidget;
	QSplitter* m_splitterLv1;
	QSplitter* m_splitterLv2;

	MainMenuBar* m_mainMenuBar;
	MainToolBar* m_mainToolBar;
	InstanceTree* m_instanceTree;
	MarkerTree* m_markerTree;

	void m_create_main_menubar();
	void m_create_main_toolbar();
	void m_create_charters();
	void m_create_instance_tree();
	void m_create_marker_tree();

public slots:
	void toggle_charter1(bool status);
	void toggle_charter2(bool status);
	void toggle_charter3(bool status);

	void set_active_charter1();
	void set_active_charter2();
	void set_active_charter3();

	void save_plots();
	
	void sync_zoom_charters(Charter* charter, const QRectF& rect);

	void set_log_scale();
	void set_log_log_scale();
	void set_lin_scale();
	void set_normalized_scale(int axisId, double reference);

	void clear_active_charter();

	void make_new_csv_instance_window();
	void make_instance_csv(ParentInstance* instance, QString fileName);

	void make_new_uff58_instance_window();
	void make_instance_uff58(ParentInstance* instance, QString fileName);

	void draw_plot(PlotCurve* curve);
	void draw_marker(PlotMarkerInstance* marker);
	void add_dynamic_side_bands(QwtPlot* plot, int numOfTicks, int bandCount);

	void toggle_h_grid(bool checked);
	void toggle_v_grid(bool checked);
	void toggle_hmin_grid(bool checked);
	void toggle_vmin_grid(bool checked);

	void set_canvas_color(QColor pickedColor);
	void set_grid_color(QColor pickedColor);
	void set_grid_style(int styleIndex);

	void set_axis_tick_marks_font(QFont font);
	void set_plot_title_font(QFont font);
	void set_haxis_label_font(QFont font);
	void set_vaxis_label_font(QFont font);

	void set_plot_title(QString value);
	void set_haxis_label(QString value);
	void set_vaxis_label(QString value);

	void make_new_marker_window();
	void make_marker_instance(AbstractPlotMarker* marker);

	void set_charter_data_picker_search_width(double searchWidth);

};

#endif // !MAIN_WINDOW_H
