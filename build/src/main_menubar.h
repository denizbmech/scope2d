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

#ifndef MAIN_MENUBAR_H
#define MAIN_MENUBAR_H

#include <QWidget>
#include <QMenuBar>
#include <QAction>
#include <QMenu>
#include <QIcon>
#include <QColorDialog>
#include <QActionGroup>
#include <QFontDialog>
#include <QFont>
#include <QMessageBox>
#include <QInputDialog>


class MainMenuBar: public QMenuBar {

/*
	Main menubar object that's placed on the main window of the program.
*/

public:
	MainMenuBar(QWidget* parent);

	void set_toggle_charter1_menu_state(bool state);
	void set_toggle_charter2_menu_state(bool state);
	void set_toggle_charter3_menu_state(bool state);

	void set_active_charter_menu_state_charter1();
	void set_active_charter_menu_state_charter2();
	void set_active_charter_menu_state_charter3();

	void set_h_grid_menu_state(bool state);
	void set_hmin_grid_menu_state(bool state);
	void set_v_grid_menu_state(bool state);
	void set_vmin_grid_menu_state(bool state);

	virtual ~MainMenuBar() {}

private:
	Q_OBJECT

	QMenu* m_fileMenu;
	QMenu* m_fileMenuImport;

	QMenu* m_plotMenu;
	QMenu* m_plotMenuGrid;
	QMenu* m_plotMenuScale;

	QMenu* m_modifyMenu;

	QMenu* m_chartersMenu;
	QMenu* m_showHideCharters;
	QMenu* m_setActiveCharter;

	QMenu* m_markersMenu;

	QMenu* m_styleMenu;
	QMenu* m_styleMenuCurves;
	QMenu* m_styleMenuCanvas;
	QMenu* m_styleMenuGrid;
	QMenu* m_styleMenuFonts;

	QMenu* m_infoMenu;

	QAction* m_newCSVInstanceRequest;
	QAction* m_newUFF58InstanceRequest;

	QAction* m_modifyTitleRequest;
	QAction* m_modifyHAxisLabelRequest;
	QAction* m_modifyVAxisLabelRequest;

	QAction* m_toggleHGridRequest;
	QAction* m_toggleVGridRequest;
	QAction* m_toggleHMinGridRequest;
	QAction* m_toggleVMinGridRequest;

	QAction* m_toggleCharter1Request;
	QAction* m_toggleCharter2Request;
	QAction* m_toggleCharter3Request;

	QAction* m_setActiveCharter1Request;
	QAction* m_setActiveCharter2Request;
	QAction* m_setActiveCharter3Request;
	QActionGroup* m_setActiveCharterRequest;

	QAction* m_logScaleRequest;
	QAction* m_loglogScaleRequest;
	QAction* m_linScaleRequest;
	QAction* m_normalizedScaleRequest;

	QAction* m_clearActiveCharterRequest;

	QAction* m_addMarkerRequest;
	QAction* m_setPickerSearchWidthRequest;

	QAction* m_modifyCanvasColorRequest;
	QAction* m_modifyGridColorRequest;
	QAction* m_modifyGridStyleRequest;

	QAction* m_modifyAxisTickMarksFontRequest;
	QAction* m_modifyPlotTitleFontRequest;
	QAction* m_modifyHAxisLabelFontRequest;
	QAction* m_modifyVAxisLabelFontRequest;

	QAction* m_makeAboutWindow;
	QAction* m_makeAboutQtWindow;
	QAction* m_makeAboutIconsWindow;

	void m_create_actions();
	void m_create_actions_file();
	void m_create_actions_plot();
	void m_create_actions_modify();
	void m_create_actions_charters();
	void m_create_actions_markers();
	void m_create_actions_style();
	void m_create_actions_info();

	void m_create_menus();
	void m_create_menus_file();
	void m_create_menus_plot();
	void m_create_menus_modify();
	void m_create_menus_charters();
	void m_create_menus_markers();
	void m_create_menus_style();
	void m_create_menus_info();

public slots:
	void request_new_csv_instance();
	void request_new_uff58_instance();

	void make_modify_title_window();
	void make_modify_haxis_label_window();
	void make_modify_vaxis_label_window();

	void request_toggle_h_grid(bool checked);
	void request_toggle_v_grid(bool checked);
	void request_toggle_hmin_grid(bool checked);
	void request_toggle_vmin_grid(bool checked);

	void request_toggle_charter1(bool checked);
	void request_toggle_charter2(bool checked);
	void request_toggle_charter3(bool checked);

	void request_setActive_charter1();
	void request_setActive_charter2();
	void request_setActive_charter3();

	void request_set_log_scale();
	void request_set_log_log_scale();
	void request_set_lin_scale();
	void request_set_normalized_scale();
	void request_clear_active_charter();

	void request_modify_canvas_color();

	void request_modify_grid_color();
	void make_modify_grid_style_window();

	void request_modify_axis_tick_marks_font();
	void request_modify_plot_title_font();
	void request_modify_haxis_label_font();
	void request_modify_vaxis_label_font();

	void request_add_marker();
	void make_set_picker_search_width_window();

	void make_about_window();
	void make_about_qt_window();
	void make_about_icons_window();

signals:
	void newCSVInstanceRequested();
	void newUFF58InstanceRequested();

	void modifyTitleRequested(QString);
	void modifyHAxisRequested(QString);
	void modifyVAxisRequested(QString);

	void toggleHGridRequested(bool);
	void toggleVGridRequested(bool);
	void toggleHMinGridRequested(bool);
	void toggleVMinGridRequested(bool);

	void toggleCharter1Requested(bool);
	void toggleCharter2Requested(bool);
	void toggleCharter3Requested(bool);

	void setActiveCharter1Requested();
	void setActiveCharter2Requested();
	void setActiveCharter3Requested();

	void setLogScaleRequested();
	void setLogLogScaleRequested();
	void setLinScaleRequested();
	void setNormalizedScaleRequested(int, double);

	void clearActiveCharterRequested();

	void modifyCanvasColorRequested(QColor);
	void modifyAxisTickMarksFontRequested(QFont);
	void modifyPlotTitleFontRequested(QFont);
	void modifyHAxisLabelFontRequested(QFont);
	void modifyVAxisLabelFontRequested(QFont);

	void modifyGridColorRequested(QColor);
	void modifyGridStyleRequested(int);

	void addMarkerRequested();
	void setPickerSearchWidthRequested(double);

};

#endif // !MAIN_MENUBAR_H
