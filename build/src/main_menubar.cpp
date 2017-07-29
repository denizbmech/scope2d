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

#include "main_menubar.h"

MainMenuBar::MainMenuBar(QWidget* parent): QMenuBar(parent) {

	this->setAttribute(Qt::WA_DeleteOnClose);
	this->setNativeMenuBar(false);

	m_create_menus();

}

void MainMenuBar::set_toggle_charter1_menu_state(bool state) {

	m_toggleCharter1Request->setChecked(state);

}

void MainMenuBar::set_toggle_charter2_menu_state(bool state) {

	m_toggleCharter2Request->setChecked(state);

}

void MainMenuBar::set_toggle_charter3_menu_state(bool state) {

	m_toggleCharter3Request->setChecked(state);

}

void MainMenuBar::set_active_charter_menu_state_charter1() {

	m_setActiveCharter1Request->setChecked(true);

}

void MainMenuBar::set_active_charter_menu_state_charter2() {

	m_setActiveCharter2Request->setChecked(true);

}

void MainMenuBar::set_active_charter_menu_state_charter3() {

	m_setActiveCharter3Request->setChecked(true);

}

void MainMenuBar::m_create_actions() {

	m_create_actions_file();
	m_create_actions_plot();
	m_create_actions_markers();
	m_create_actions_style();
	m_create_actions_info();

}

void MainMenuBar::m_create_actions_file() {

	m_newCSVInstanceRequest = new QAction(
		QIcon(":/file_formats/csv.png"),
		"From generic CSV...", this);
	m_newUFF58InstanceRequest = new QAction(
		QIcon(":/file_formats/uff.png"),
		"From UFF58...", this);

	connect(m_newCSVInstanceRequest, SIGNAL(triggered(bool)),
		this, SLOT(request_new_csv_instance()));
	connect(m_newUFF58InstanceRequest, SIGNAL(triggered(bool)),
		this, SLOT(request_new_uff58_instance()));

}

void MainMenuBar::m_create_actions_plot() {

	m_modifyTitleRequest = new QAction("Plot Title...", this);
	m_modifyHAxisLabelRequest = new QAction("H Axis Label...", this);
	m_modifyVAxisLabelRequest = new QAction("V Axis Label...", this);

	m_toggleHGridRequest = new QAction("H Major Grid", this);
	m_toggleVGridRequest = new QAction("V Major Grid", this);
	m_toggleHMinGridRequest = new QAction("H Minor Grid", this);
	m_toggleVMinGridRequest = new QAction("V Minor Grid", this);
	m_toggleHGridRequest->setCheckable(true);
	m_toggleVGridRequest->setCheckable(true);
	m_toggleHMinGridRequest->setCheckable(true);
	m_toggleVMinGridRequest->setCheckable(true);

	m_toggleCharter1Request = new QAction("Charter1", this);
	m_toggleCharter2Request = new QAction("Charter2", this);
	m_toggleCharter3Request = new QAction("Charter3", this);
	m_toggleCharter1Request->setCheckable(true);
	m_toggleCharter2Request->setCheckable(true);
	m_toggleCharter3Request->setCheckable(true);

	m_setActiveCharterRequest = new QActionGroup(this);
	m_setActiveCharter1Request = new QAction("Charter1", 
		m_setActiveCharterRequest);
	m_setActiveCharter2Request = new QAction("Charter2", 
		m_setActiveCharterRequest);
	m_setActiveCharter3Request = new QAction("Charter3", 
		m_setActiveCharterRequest);
	m_setActiveCharter1Request->setCheckable(true);
	m_setActiveCharter2Request->setCheckable(true);
	m_setActiveCharter3Request->setCheckable(true);

	m_logScaleRequest = new QAction("Logarithmic", this);
	m_loglogScaleRequest = new QAction("Log - Log", this);
	m_linScaleRequest = new QAction("Linear", this);

	m_clearActiveCharterRequest = new QAction("Clear active charter", this);

	connect(m_modifyTitleRequest, SIGNAL(triggered(bool)),
		this, SLOT(make_modify_title_window()));
	connect(m_modifyHAxisLabelRequest, SIGNAL(triggered(bool)),
		this, SLOT(make_modify_haxis_label_window()));
	connect(m_modifyVAxisLabelRequest, SIGNAL(triggered(bool)),
		this, SLOT(make_modify_vaxis_label_window()));

	connect(m_toggleHGridRequest, SIGNAL(triggered(bool)),
		this, SLOT(request_toggle_h_grid(bool)));
	connect(m_toggleVGridRequest, SIGNAL(triggered(bool)),
		this, SLOT(request_toggle_v_grid(bool)));
	connect(m_toggleHMinGridRequest, SIGNAL(triggered(bool)),
		this, SLOT(request_toggle_hmin_grid(bool)));
	connect(m_toggleVMinGridRequest, SIGNAL(triggered(bool)),
		this, SLOT(request_toggle_vmin_grid(bool)));

	connect(m_toggleCharter1Request, SIGNAL(triggered(bool)),
		this, SLOT(request_toggle_charter1(bool)));
	connect(m_toggleCharter2Request, SIGNAL(triggered(bool)),
		this, SLOT(request_toggle_charter2(bool)));
	connect(m_toggleCharter3Request, SIGNAL(triggered(bool)),
		this, SLOT(request_toggle_charter3(bool)));

	connect(m_setActiveCharter1Request, SIGNAL(triggered(bool)),
		this, SLOT(request_setActive_charter1()));
	connect(m_setActiveCharter2Request, SIGNAL(triggered(bool)),
		this, SLOT(request_setActive_charter2()));
	connect(m_setActiveCharter3Request, SIGNAL(triggered(bool)),
		this, SLOT(request_setActive_charter3()));

	connect(m_logScaleRequest, SIGNAL(triggered(bool)),
		this, SLOT(request_set_log_scale()));
	connect(m_loglogScaleRequest, SIGNAL(triggered(bool)),
		this, SLOT(request_set_log_log_scale()));
	connect(m_linScaleRequest, SIGNAL(triggered(bool)),
		this, SLOT(request_set_lin_scale()));

	connect(m_clearActiveCharterRequest, SIGNAL(triggered(bool)),
		this, SLOT(request_clear_active_charter()));

	m_toggleCharter1Request->setChecked(true);
	m_setActiveCharter1Request->setChecked(true);

}

void MainMenuBar::m_create_actions_markers() {

	m_addMarkerRequest = new QAction("Add marker...", this);
	m_setPickerSearchWidthRequest = 
		new QAction("Picker search width...", this);

	connect(m_addMarkerRequest, SIGNAL(triggered(bool)),
		this, SLOT(request_add_marker()));
	connect(m_setPickerSearchWidthRequest, SIGNAL(triggered(bool)),
		this, SLOT(make_set_picker_search_width_window()));

}

void MainMenuBar::m_create_actions_style() {

	m_modifyCanvasColorRequest = new QAction("Color...", this);

	m_modifyGridColorRequest = new QAction("Color...", this);
	m_modifyGridStyleRequest = new QAction("Style...", this);

	m_modifyAxisTickMarksFontRequest = new QAction("Axis Tick Marks...", this);
	m_modifyPlotTitleFontRequest = new QAction("Plot Title...", this);
	m_modifyHAxisLabelFontRequest = new QAction("H Axis Label...", this);
	m_modifyVAxisLabelFontRequest = new QAction("V Axis Label...", this);

	connect(m_modifyCanvasColorRequest, SIGNAL(triggered(bool)),
		this, SLOT(request_modify_canvas_color()));

	connect(m_modifyGridColorRequest, SIGNAL(triggered(bool)),
		this, SLOT(request_modify_grid_color()));
	connect(m_modifyGridStyleRequest, SIGNAL(triggered(bool)),
		this, SLOT(make_modify_grid_style_window()));

	connect(m_modifyAxisTickMarksFontRequest, SIGNAL(triggered(bool)),
		this, SLOT(request_modify_axis_tick_marks_font()));
	connect(m_modifyPlotTitleFontRequest, SIGNAL(triggered(bool)),
		this, SLOT(request_modify_plot_title_font()));
	connect(m_modifyHAxisLabelFontRequest, SIGNAL(triggered(bool)),
		this, SLOT(request_modify_haxis_label_font()));
	connect(m_modifyVAxisLabelFontRequest, SIGNAL(triggered(bool)),
		this, SLOT(request_modify_vaxis_label_font()));

}

void MainMenuBar::m_create_actions_info() {

	m_makeAboutWindow = new QAction("About scope2d");
	m_makeAboutQtWindow = new QAction("About Qt");
	m_makeAboutIconsWindow = new QAction("About Icons");

	connect(m_makeAboutWindow, SIGNAL(triggered(bool)),
		this, SLOT(make_about_window()));
	connect(m_makeAboutQtWindow, SIGNAL(triggered(bool)),
		this, SLOT(make_about_qt_window()));
	connect(m_makeAboutIconsWindow, SIGNAL(triggered(bool)),
		this, SLOT(make_about_icons_window()));

}

void MainMenuBar::m_create_menus() {

	m_create_actions();
	m_create_menus_file();
	m_create_menus_plot();
	m_create_menus_markers();
	m_create_menus_style();
	m_create_menus_info();

}

void MainMenuBar::m_create_menus_file() {

	m_fileMenu = this->addMenu("File");
	m_fileMenuImport = m_fileMenu->addMenu("New Instance");
	m_fileMenuImport->addAction(m_newCSVInstanceRequest);
	m_fileMenuImport->addAction(m_newUFF58InstanceRequest);

}

void MainMenuBar::m_create_menus_plot() {

	m_plotMenu = this->addMenu("Plot");

	m_plotMenuModify = m_plotMenu->addMenu("Modify");
	m_plotMenuModify->addAction(m_modifyTitleRequest);
	m_plotMenuModify->addAction(m_modifyHAxisLabelRequest);
	m_plotMenuModify->addAction(m_modifyVAxisLabelRequest);

	m_plotMenuGrid = m_plotMenu->addMenu("Grid");
	m_plotMenuGrid->addAction(m_toggleHGridRequest);
	m_plotMenuGrid->addAction(m_toggleVGridRequest);
	m_plotMenuGrid->addAction(m_toggleHMinGridRequest);
	m_plotMenuGrid->addAction(m_toggleVMinGridRequest);

	m_showHideCharters = m_plotMenu->addMenu("Show/Hide Charters");
	m_showHideCharters->addAction(m_toggleCharter1Request);
	m_showHideCharters->addAction(m_toggleCharter2Request);
	m_showHideCharters->addAction(m_toggleCharter3Request);

	m_setActiveCharter = m_plotMenu->addMenu("Set Active Charter");
	m_setActiveCharter->addAction(m_setActiveCharter1Request);
	m_setActiveCharter->addAction(m_setActiveCharter2Request);
	m_setActiveCharter->addAction(m_setActiveCharter3Request);

	m_plotMenuScale = m_plotMenu->addMenu("Scale");
	m_plotMenuScale->addAction(m_logScaleRequest);
	m_plotMenuScale->addAction(m_loglogScaleRequest);
	m_plotMenuScale->addAction(m_linScaleRequest);

	m_plotMenu->addSeparator();

	m_plotMenu->addAction(m_clearActiveCharterRequest);

}

void MainMenuBar::m_create_menus_markers() {

	m_markersMenu = this->addMenu("Markers");
	m_markersMenu->addAction(m_addMarkerRequest);
	m_markersMenu->addAction(m_setPickerSearchWidthRequest);

}

void MainMenuBar::m_create_menus_style() {

	m_styleMenu = this->addMenu("Style");

	m_styleMenuCanvas = m_styleMenu->addMenu("Canvas");
	m_styleMenuCanvas->addAction(m_modifyCanvasColorRequest);

	m_styleMenuGrid = m_styleMenu->addMenu("Grid");
	m_styleMenuGrid->addAction(m_modifyGridColorRequest);
	m_styleMenuGrid->addAction(m_modifyGridStyleRequest);

	m_styleMenuFonts = m_styleMenu->addMenu("Fonts");
	m_styleMenuFonts->addAction(m_modifyAxisTickMarksFontRequest);
	m_styleMenuFonts->addAction(m_modifyPlotTitleFontRequest);
	m_styleMenuFonts->addAction(m_modifyHAxisLabelFontRequest);
	m_styleMenuFonts->addAction(m_modifyVAxisLabelFontRequest);

}

void MainMenuBar::m_create_menus_info() {

	m_infoMenu = this->addMenu("Info");

	m_infoMenu->addAction(m_makeAboutWindow);
	m_infoMenu->addAction(m_makeAboutQtWindow);
	m_infoMenu->addAction(m_makeAboutIconsWindow);

}

void MainMenuBar::request_new_csv_instance() {

	emit newCSVInstanceRequested();

}

void MainMenuBar::request_new_uff58_instance() {

	emit newUFF58InstanceRequested();

}

void MainMenuBar::make_modify_title_window() {

	QString windowTitle = "Set new plot title";
	QString label("Enter new title: ");
	label.resize(60, ' '); // to set a minimum size for the window since
						   // it isn't possible to set window size with getText

	bool userPressedOk;

	QString newTitle = QInputDialog::getText(this, windowTitle, 
		label, QLineEdit::Normal, QString(), &userPressedOk);

	if(userPressedOk) 
		emit modifyTitleRequested(newTitle);

}

void MainMenuBar::make_modify_haxis_label_window() {

	QString windowTitle = "Set new h axis label";
	QString label("Enter new h axis label: ");
	label.resize(60, ' '); // to set a minimum size for the window since
						   // it isn't possible to set window size with getText

	bool userPressedOk;

	QString newLabel = QInputDialog::getText(this, windowTitle,
		label, QLineEdit::Normal, QString(), 
		&userPressedOk);

	if(userPressedOk) 
		emit modifyHAxisRequested(newLabel);

}

void MainMenuBar::make_modify_vaxis_label_window() {

	QString windowTitle = "Set new v axis label";
	QString label("Enter new v axis label: ");
	label.resize(60, ' '); // to set a minimum size for the window since
						   // it isn't possible to set window size with getText

	bool userPressedOk;

	QString newLabel = QInputDialog::getText(this, windowTitle,
		label, QLineEdit::Normal, QString(),
		&userPressedOk);

	if(userPressedOk) 
		emit modifyVAxisRequested(newLabel);

}

void MainMenuBar::request_toggle_h_grid(bool checked) {

	if(!checked) request_toggle_hmin_grid(false);

	emit toggleHGridRequested(checked);

}

void MainMenuBar::request_toggle_v_grid(bool checked) {

	if(!checked) request_toggle_vmin_grid(false);

	emit toggleVGridRequested(checked);

}

void MainMenuBar::request_toggle_hmin_grid(bool checked) {

	bool hMinGridStatus = checked && m_toggleHGridRequest->isChecked();
	m_toggleHMinGridRequest->setChecked(hMinGridStatus);

	emit toggleHMinGridRequested(hMinGridStatus);

}

void MainMenuBar::request_toggle_vmin_grid(bool checked) {

	bool vMinGridStatus = checked && m_toggleVGridRequest->isChecked();
	m_toggleVMinGridRequest->setChecked(vMinGridStatus);

	emit toggleVMinGridRequested(vMinGridStatus);

}

void MainMenuBar::request_toggle_charter1(bool checked) {

	m_toggleCharter1Request->setChecked(checked);

	emit toggleCharter1Requested(checked);

}

void MainMenuBar::request_toggle_charter2(bool checked) {

	m_toggleCharter2Request->setChecked(checked);

	emit toggleCharter2Requested(checked);

}

void MainMenuBar::request_toggle_charter3(bool checked) {

	m_toggleCharter3Request->setChecked(checked);

	emit toggleCharter3Requested(checked);

}

void MainMenuBar::request_setActive_charter1() {

	m_setActiveCharter1Request->setChecked(true);

	if(!m_toggleCharter1Request->isChecked())
		request_toggle_charter1(true);

	emit setActiveCharter1Requested();

}

void MainMenuBar::request_setActive_charter2() {

	m_setActiveCharter2Request->setChecked(true);

	if(!m_toggleCharter2Request->isChecked())
		request_toggle_charter2(true);

	emit setActiveCharter2Requested();

}

void MainMenuBar::request_setActive_charter3() {

	m_setActiveCharter3Request->setChecked(true);

	if(!m_toggleCharter3Request->isChecked())
		request_toggle_charter3(true);

	emit setActiveCharter3Requested();

}

void MainMenuBar::request_set_log_scale() {

	emit setLogScaleRequested();

}

void MainMenuBar::request_set_log_log_scale() {

	emit setLogLogScaleRequested();

}

void MainMenuBar::request_set_lin_scale() {

	emit setLinScaleRequested();

}

void MainMenuBar::request_clear_active_charter() {

	emit clearActiveCharterRequested();

}

void MainMenuBar::request_modify_canvas_color() {

	QString windowTitle = "Set new canvas color";

	QColorDialog* colorDialog = new QColorDialog(this);
	colorDialog->setAttribute(Qt::WA_DeleteOnClose);

	QColor pickedColor = colorDialog->getColor(Qt::white, this, windowTitle);

	if(pickedColor.isValid())
		emit modifyCanvasColorRequested(pickedColor);

}

void MainMenuBar::request_modify_axis_tick_marks_font() {

	bool isFontGood;

	QFont newAxisFont = QFontDialog::getFont(&isFontGood, 
		QFont("Verdana", 10), this, "Select new axis tick marks font");

	if(isFontGood)
		emit modifyAxisTickMarksFontRequested(newAxisFont);
		
}

void MainMenuBar::request_modify_plot_title_font() {

	bool isFontGood;

	QFont newAxisFont = QFontDialog::getFont(&isFontGood,
		QFont("Verdana", 11), this, "Select new plot title font");

	if(isFontGood)
		emit modifyPlotTitleFontRequested(newAxisFont);

}

void MainMenuBar::request_modify_haxis_label_font() {

	bool isFontGood;

	QFont newAxisFont = QFontDialog::getFont(&isFontGood,
		QFont("Verdana", 10), this, "Select new h axis label font");

	if(isFontGood)
		emit modifyHAxisLabelFontRequested(newAxisFont);

}

void MainMenuBar::request_modify_vaxis_label_font() {

	bool isFontGood;

	QFont newAxisFont = QFontDialog::getFont(&isFontGood,
		QFont("Verdana", 10), this, "Select new v axis label font");

	if(isFontGood)
		emit modifyVAxisLabelFontRequested(newAxisFont);

}

void MainMenuBar::request_modify_grid_color() {

	QString windowTitle = "Set new grid color";

	QColorDialog* colorDialog = new QColorDialog(this);
	colorDialog->setAttribute(Qt::WA_DeleteOnClose);

	QColor pickedColor = colorDialog->getColor(Qt::white, this, windowTitle);

	if(pickedColor.isValid())
		emit modifyGridColorRequested(pickedColor);

}

void MainMenuBar::make_modify_grid_style_window() {

	QString windowTitle = "Set new grid style";
	QString label("Select new grid style: ");
	label.resize(60, ' '); // to set a minimum size for the window since
						   // it isn't possible to set window size with getItem

	QStringList list = (QStringList() << "Solid Line" << "Dash Line"
		<< "Dot Line" << "Dash-Dot Line" << "Dash-Dot-Dot Line");

	bool userPressedOk;

	QString newStyle = QInputDialog::getItem(this, windowTitle,
		label, list, 0, false, &userPressedOk);

	// messy...

	int styleIndex = 0;

	if(newStyle == "Dash Line") styleIndex = 1;
	else if(newStyle == "Dot Line") styleIndex = 2;
	else if(newStyle == "Dash-Dot Line") styleIndex = 3;
	else if(newStyle == "Dash-Dot-Dot Line") styleIndex = 4;

	if(userPressedOk && !newStyle.isEmpty()) 
		emit modifyGridStyleRequested(styleIndex);
		
}

void MainMenuBar::request_add_marker() {

	emit addMarkerRequested();

}

void MainMenuBar::make_set_picker_search_width_window() {

	QString windowTitle = "Set picker search width";
	QString label("Enter new picker search width: ");
	label.resize(60, ' '); // to set a minimum size for the window since
						   // it isn't possible to set window size with getText

	bool userPressedOk;

	QString newWidth = QInputDialog::getText(this, windowTitle,
		label, QLineEdit::Normal, QString(),
		&userPressedOk);

	if(userPressedOk && !newWidth.isEmpty()) {
		bool isSearchWidthGood;
		double searchWidthDouble = newWidth.toDouble(&isSearchWidthGood);

		if(isSearchWidthGood && searchWidthDouble > 0)
			emit setPickerSearchWidthRequested(searchWidthDouble);
	}

}


void MainMenuBar::set_h_grid_menu_state(bool state) {
	/*
	Sets the menu state to checked if state is true; unchecked if state is
	false. Controls the horizontal minor grid menu state too, since minor
	grids cannot be used without setting major grids on.
	*/

	m_toggleHGridRequest->setChecked(state);

	if(!state) set_hmin_grid_menu_state(false);

}

void MainMenuBar::set_hmin_grid_menu_state(bool state) {
	/*
	Controls the horizontal minor grid menu state. Menu is set to
	checked if state is true, unchecked if state is false.
	*/

	m_toggleHMinGridRequest->setChecked(state);

}

void MainMenuBar::set_v_grid_menu_state(bool state) {
	/*
	Sets the menu state to checked if state is true; unchecked if state is
	false. Controls the vertical minor grid menu state too, since minor
	grids cannot be used without setting major grids on.
	*/

	m_toggleVGridRequest->setChecked(state);

	if(!state) set_vmin_grid_menu_state(false);

}

void MainMenuBar::set_vmin_grid_menu_state(bool state) {
	/*
	Controls the vertical minor grid menu state. Menu is set to
	checked if state is true, unchecked if state is false.
	*/

	m_toggleVMinGridRequest->setChecked(state);

}

void MainMenuBar::make_about_window() {

	QString title("About scope2d");
	QString text =
		"<p align='justify'>"
		"scope2d is a general-purpose data visualization and analysis software "
		"developed by Deniz Bilgili. scope2d is distributed as a free, "
		"open-source program which is developed with "
		"<a href='https://www.qt.io/'>Qt</a>"
		", <a href='http://qwt.sourceforge.net/'>Qwt</a>, "
		"<a href='http://eigen.tuxfamily.org'>Eigen</a> and C++ ."
		"</p>"
		"<p align='justify'>"
		"Please visit "
		"<a href='https://bilgilid.github.io/scope2d/website/features.html'>"
		"the features page"
		"</a>"
		" for a detailed guide on scope2d's fundamental visualization and "
		"analysis tools, "
	"<a href='https://bilgilid.github.io/scope2d/website/buildandinstall.html'>"
		"the build and install page"
		"</a>" 
		" for Linux and "
		"Windows installers as well as instructions for building the "
		"application from source code."
		"</p>"
		"<p align='justify'>"
		"Special thanks to Prof. Kenan Yuce Sanliturk of Technical University "
		"of Istanbul for his valuable advices during the development of "
		"scope2d."
		"</p>";
	QMessageBox::about(this, title, text);

}

void MainMenuBar::make_about_qt_window() {

	QString title("About Qt");
	QMessageBox::aboutQt(this, title);

}

void MainMenuBar::make_about_icons_window() {

	QString title("About Icons");
	QString text =
		"Some of the icons in Scope2D are from: "
		"<ul>"
		"<li><a href='https://icons8.com'>Icon pack by Icons8</a></li>"
		"<li>"
		"<a href='https://icons8.com/icon/49752/Grid'>Grid icon credits</a>"
		"</li>"
		"<li>"
		"<a href='https://icons8.com/icon/49751/Grid-2'>Grid 2 icon credits</a>"
		"<li>"
		"<a href='https://www.iconfinder.com/iconsets/basicset'> "
		"Basic set icon credits "
		"</a>"
		"</li>"
		"</li>"
		"<li><a href='http://pixel-mixer.com/'>Pixel Mixer</a></li>"
		"</ul>"
		"scope2d Application icon is from: "
		"<a href='http://www.aha-soft.com/'>Aha-Soft</a> "
		"<a href='https://www.iconfinder.com/aha-soft'>Aha-Soft on iconfinder"
		"</a>";
	QMessageBox::about(this, title, text);

}