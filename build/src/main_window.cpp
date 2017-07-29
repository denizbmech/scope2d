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

#include "main_window.h"

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent) {

	this->setAttribute(Qt::WA_DeleteOnClose);
	this->setWindowTitle("scope2d: 2-D Data Visualization & Analysis");
	this->setGeometry(100, 100, 1200, 576);
	this->setContextMenuPolicy(Qt::NoContextMenu); // might wanna change later

	m_centralWidget = new QWidget(this);
	this->setCentralWidget(m_centralWidget);

	// must create in order: charters > main menubar > main toolbar
	m_create_charters();
	m_create_main_menubar();
	m_create_main_toolbar();
	m_create_instance_tree();
	m_create_marker_tree();

	m_splitterLv1 = new QSplitter(this);
	m_splitterLv1->setChildrenCollapsible(false);
	m_splitterLv1->setOpaqueResize(false);

	m_splitterLv2 = new QSplitter(this);
	m_splitterLv2->setChildrenCollapsible(false);
	m_splitterLv2->setOpaqueResize(false);

	m_splitterLv2->addWidget(m_instanceTree);
	m_splitterLv2->addWidget(m_markerTree);
	m_splitterLv2->setOrientation(Qt::Vertical);

	m_splitterLv1->addWidget(m_splitterLv2);
	m_splitterLv1->addWidget(m_charterAreaWidget);
	m_splitterLv1->setSizes(QList<int>() << 224 << 800);

	m_gridLayout = new QGridLayout(m_centralWidget);
	m_gridLayout->addWidget(m_splitterLv1, 0, 0);

}

MainWindow::~MainWindow() {

	// m_instanceTree needs to be deleted before the charters.
	delete m_instanceTree;

	// m_markerTree needs to be deleted before the charters.
	delete m_markerTree;

	delete m_charter1;
	delete m_charter2;
	delete m_charter3;

}

void MainWindow::toggle_charter1(bool status) {

	m_charter1->setVisible(status);
	m_mainMenuBar->set_toggle_charter1_menu_state(status);
	m_mainToolBar->set_toggle_charter1_button_state(status);
	
}

void MainWindow::toggle_charter2(bool status) {

	m_charter2->setVisible(status);
	m_mainMenuBar->set_toggle_charter2_menu_state(status);
	m_mainToolBar->set_toggle_charter2_button_state(status);

}

void MainWindow::toggle_charter3(bool status) {

	m_charter3->setVisible(status);
	m_mainMenuBar->set_toggle_charter3_menu_state(status);
	m_mainToolBar->set_toggle_charter3_button_state(status);

}

void MainWindow::set_active_charter1() {

	m_activeCharter = m_charter1->plot();
	if(m_charter1->isHidden()) toggle_charter1(true);

	m_mainMenuBar->set_active_charter_menu_state_charter1();
	m_mainToolBar->set_active_charter_button_state_charter1();

}

void MainWindow::set_active_charter2() {

	m_activeCharter = m_charter2->plot();
	if(m_charter2->isHidden()) toggle_charter2(true);

	m_mainMenuBar->set_active_charter_menu_state_charter2();
	m_mainToolBar->set_active_charter_button_state_charter2();

}

void MainWindow::set_active_charter3() {

	m_activeCharter = m_charter3->plot();
	if(m_charter3->isHidden()) toggle_charter3(true);

	m_mainMenuBar->set_active_charter_menu_state_charter3();
	m_mainToolBar->set_active_charter_button_state_charter3();

}

void MainWindow::save_plots() {

	QString fileAddress;

	fileAddress = QFileDialog::getSaveFileName(this,
		"Select save location", "C:/",
		"Windows Bitmap (*.bmp);;"
		"Portable Network Graphics (*.png);;"
		"Joint Photographic Experts Group (*.jpg);;"
		"Joint Photographic Experts Group (*.jpeg)");

	m_charterAreaWidget->grab().save(fileAddress);

}

void MainWindow::sync_zoom_charters(Charter* charter, const QRectF& rect) {

	if(charter == m_charter1->plot()) {
		m_charter2->plot()->zoom_to_rect(rect);
		m_charter3->plot()->zoom_to_rect(rect);
	}
	else if(charter == m_charter2->plot()) {
		m_charter1->plot()->zoom_to_rect(rect);
		m_charter3->plot()->zoom_to_rect(rect);
	}
	else if(charter == m_charter3->plot()) {
		m_charter1->plot()->zoom_to_rect(rect);
		m_charter2->plot()->zoom_to_rect(rect);
	}

}

void MainWindow::set_log_scale() {

	m_activeCharter->use_log_scale();

}

void MainWindow::set_log_log_scale() {

	m_activeCharter->use_log_log_scale();

}

void MainWindow::set_lin_scale() {

	m_activeCharter->use_linear_scale();

}

void MainWindow::clear_active_charter() {

	QMessageBox confirmClearActiveCharterWindow;
	confirmClearActiveCharterWindow.setWindowTitle("Clear Active Charter");

	QString charterLabel;

	if(m_activeCharter == m_charter1->plot())
		charterLabel = "Charter 1";
	else if(m_activeCharter == m_charter2->plot())
		charterLabel = "Charter 2";
	else if(m_activeCharter == m_charter3->plot())
		charterLabel = "Charter 3";

	QString confirmationText = "Do you want to clear " + charterLabel + "?";
	confirmClearActiveCharterWindow.setText(confirmationText);

	confirmClearActiveCharterWindow.setStandardButtons(
		QMessageBox::No | QMessageBox::Yes
	);

	confirmClearActiveCharterWindow.setIcon(QMessageBox::Question);

	confirmClearActiveCharterWindow.setDefaultButton(QMessageBox::No);
	int selectedButton = confirmClearActiveCharterWindow.exec();

	if(selectedButton == QMessageBox::Yes) m_activeCharter->clear();

}

void MainWindow::m_create_instance_tree() {

	m_instanceTree = new InstanceTree(this);

	connect(m_instanceTree, SIGNAL(drawCurveRequested(PlotCurve*)),
		this, SLOT(draw_plot(PlotCurve*)));

}

void MainWindow::m_create_marker_tree() {

	m_markerTree = new MarkerTree(this);

	connect(m_markerTree, SIGNAL(drawMarkerRequested(PlotMarkerInstance*)),
		this, SLOT(draw_marker(PlotMarkerInstance*)));

}

void MainWindow::m_create_main_menubar() {

	m_mainMenuBar = new MainMenuBar(this);

	// File menu connections
	connect(m_mainMenuBar, SIGNAL(newCSVInstanceRequested()),
		this, SLOT(make_new_csv_instance_window()));
	connect(m_mainMenuBar, SIGNAL(newUFF58InstanceRequested()),
		this, SLOT(make_new_uff58_instance_window()));

	// Plot menu connections
	connect(m_mainMenuBar,
		SIGNAL(modifyTitleRequested(QString)),
		this, SLOT(set_plot_title(QString)));
	connect(m_mainMenuBar,
		SIGNAL(modifyHAxisRequested(QString)),
		this, SLOT(set_haxis_label(QString)));
	connect(m_mainMenuBar,
		SIGNAL(modifyVAxisRequested(QString)),
		this, SLOT(set_vaxis_label(QString)));

	connect(m_mainMenuBar,
		SIGNAL(toggleHGridRequested(bool)),
		this, SLOT(toggle_h_grid(bool)));
	connect(m_mainMenuBar,
		SIGNAL(toggleVGridRequested(bool)),
		this, SLOT(toggle_v_grid(bool)));
	connect(m_mainMenuBar,
		SIGNAL(toggleHMinGridRequested(bool)),
		this, SLOT(toggle_hmin_grid(bool)));
	connect(m_mainMenuBar,
		SIGNAL(toggleVMinGridRequested(bool)),
		this, SLOT(toggle_vmin_grid(bool)));

	connect(m_mainMenuBar,
		SIGNAL(toggleCharter1Requested(bool)),
		this, SLOT(toggle_charter1(bool)));
	connect(m_mainMenuBar,
		SIGNAL(toggleCharter2Requested(bool)),
		this, SLOT(toggle_charter2(bool)));
	connect(m_mainMenuBar,
		SIGNAL(toggleCharter3Requested(bool)),
		this, SLOT(toggle_charter3(bool)));

	connect(m_mainMenuBar,
		SIGNAL(setActiveCharter1Requested()),
		this, SLOT(set_active_charter1()));
	connect(m_mainMenuBar,
		SIGNAL(setActiveCharter2Requested()),
		this, SLOT(set_active_charter2()));
	connect(m_mainMenuBar,
		SIGNAL(setActiveCharter3Requested()),
		this, SLOT(set_active_charter3()));

	connect(m_mainMenuBar,
		SIGNAL(setLogScaleRequested()),
		this, SLOT(set_log_scale()));
	connect(m_mainMenuBar,
		SIGNAL(setLogLogScaleRequested()),
		this, SLOT(set_log_log_scale()));
	connect(m_mainMenuBar,
		SIGNAL(setLinScaleRequested()),
		this, SLOT(set_lin_scale()));

	connect(m_mainMenuBar,
		SIGNAL(clearActiveCharterRequested()),
		this,
		SLOT(clear_active_charter()));

	// Markers menu connections
	connect(m_mainMenuBar, SIGNAL(addMarkerRequested()),
		this, SLOT(make_new_marker_window()));
	connect(m_mainMenuBar, SIGNAL(setPickerSearchWidthRequested(double)),
		this, SLOT(set_charter_data_picker_search_width(double)));

	// Style menu connections
	connect(m_mainMenuBar,
		SIGNAL(modifyCanvasColorRequested(QColor)),
		this, SLOT(set_canvas_color(QColor)));

	connect(m_mainMenuBar,
		SIGNAL(modifyGridColorRequested(QColor)),
		this, SLOT(set_grid_color(QColor)));
	connect(m_mainMenuBar,
		SIGNAL(modifyGridStyleRequested(int)),
		this, SLOT(set_grid_style(int)));

	connect(m_mainMenuBar,
		SIGNAL(modifyAxisTickMarksFontRequested(QFont)),
		this, SLOT(set_axis_tick_marks_font(QFont)));
	connect(m_mainMenuBar,
		SIGNAL(modifyPlotTitleFontRequested(QFont)),
		this, SLOT(set_plot_title_font(QFont)));
	connect(m_mainMenuBar,
		SIGNAL(modifyHAxisLabelFontRequested(QFont)),
		this, SLOT(set_haxis_label_font(QFont)));
	connect(m_mainMenuBar,
		SIGNAL(modifyVAxisLabelFontRequested(QFont)),
		this, SLOT(set_vaxis_label_font(QFont)));

	this->setMenuBar(m_mainMenuBar);

}

void MainWindow::m_create_main_toolbar() {

	m_mainToolBar = new MainToolBar(this);

	connect(m_mainToolBar, SIGNAL(newCSVInstanceRequested()),
		this, SLOT(make_new_csv_instance_window()));
	connect(m_mainToolBar, SIGNAL(newUFF58InstanceRequested()),
		this, SLOT(make_new_uff58_instance_window()));

	connect(m_mainToolBar, SIGNAL(toggleCharter1Requested(bool)),
		this, SLOT(toggle_charter1(bool)));
	connect(m_mainToolBar, SIGNAL(toggleCharter2Requested(bool)),
		this, SLOT(toggle_charter2(bool)));
	connect(m_mainToolBar, SIGNAL(toggleCharter3Requested(bool)),
		this, SLOT(toggle_charter3(bool)));

	connect(m_mainToolBar, SIGNAL(setActiveCharter1Requested()),
		this, SLOT(set_active_charter1()));
	connect(m_mainToolBar, SIGNAL(setActiveCharter2Requested()),
		this, SLOT(set_active_charter2()));
	connect(m_mainToolBar, SIGNAL(setActiveCharter3Requested()),
		this, SLOT(set_active_charter3()));

	connect(m_mainToolBar, SIGNAL(savePlotsRequested()),
		this, SLOT(save_plots()));

	connect(m_mainToolBar, SIGNAL(clearActiveCharterRequested()),
		this, SLOT(clear_active_charter()));

	connect(m_mainToolBar, SIGNAL(toggleHGridRequested(bool)),
		this, SLOT(toggle_h_grid(bool)));
	connect(m_mainToolBar, SIGNAL(toggleVGridRequested(bool)),
		this, SLOT(toggle_v_grid(bool)));
	connect(m_mainToolBar, SIGNAL(toggleHMinGridRequested(bool)),
		this, SLOT(toggle_hmin_grid(bool)));
	connect(m_mainToolBar, SIGNAL(toggleVMinGridRequested(bool)),
		this, SLOT(toggle_vmin_grid(bool)));

	this->addToolBar(Qt::TopToolBarArea, m_mainToolBar);

}

void MainWindow::m_create_charters() {

	m_charter1 = new CharterWithLegend(this);
	m_charter2 = new CharterWithLegend(this);
	m_charter3 = new CharterWithLegend(this);

	connect(m_charter1->plot(), SIGNAL(markerAttached(AbstractPlotMarker*)),
		this, SLOT(make_marker_instance(AbstractPlotMarker*)));
	connect(m_charter2->plot(), SIGNAL(markerAttached(AbstractPlotMarker*)),
		this, SLOT(make_marker_instance(AbstractPlotMarker*)));
	connect(m_charter3->plot(), SIGNAL(markerAttached(AbstractPlotMarker*)),
		this, SLOT(make_marker_instance(AbstractPlotMarker*)));

	connect(
		m_charter1->plot(),
		SIGNAL(synchronizedZoomUsed(Charter*, const QRectF&)),
		this, 
		SLOT(sync_zoom_charters(Charter*, const QRectF&))
	);
	connect(
		m_charter2->plot(),
		SIGNAL(synchronizedZoomUsed(Charter*, const QRectF&)),
		this, 
		SLOT(sync_zoom_charters(Charter*, const QRectF&))
	);
	connect(
		m_charter3->plot(),
		SIGNAL(synchronizedZoomUsed(Charter*, const QRectF&)),
		this, 
		SLOT(sync_zoom_charters(Charter*, const QRectF&))
	);

	m_activeCharter = m_charter1->plot();

	m_charterAreaWidget = new QWidget(this);
	m_charterAreaWidget->setMaximumHeight(940);
	m_charterAreaLayout = new QVBoxLayout(m_charterAreaWidget);

	m_charterAreaLayout->addWidget(m_charter1);
	m_charterAreaLayout->addWidget(m_charter2);
	m_charterAreaLayout->addWidget(m_charter3);

	m_charter2->hide();
	m_charter3->hide();

}

void MainWindow::set_plot_title(QString value) {

	m_activeCharter->set_plot_title(value);

	if(m_activeCharter == m_charter1->plot())
		m_charter1->align_charter_and_legend();
	else if(m_activeCharter == m_charter2->plot())
		m_charter2->align_charter_and_legend();
	else if(m_activeCharter == m_charter3->plot())
		m_charter3->align_charter_and_legend();

}

void MainWindow::set_haxis_label(QString value) {

	m_activeCharter->set_haxis_label(value);

	if(m_activeCharter == m_charter1->plot())
		m_charter1->align_charter_and_legend();
	else if(m_activeCharter == m_charter2->plot())
		m_charter2->align_charter_and_legend();
	else if(m_activeCharter == m_charter3->plot())
		m_charter3->align_charter_and_legend();

}

void MainWindow::set_vaxis_label(QString value) {

	m_activeCharter->set_vaxis_label(value);

}

void MainWindow::set_canvas_color(QColor pickedColor) {

	m_activeCharter->set_canvas_color(pickedColor);

}

void MainWindow::set_axis_tick_marks_font(QFont font) {

	m_charter1->plot()->setAxisFont(QwtPlot::xBottom, font);
	m_charter1->plot()->setAxisFont(QwtPlot::yLeft, font);
	m_charter2->plot()->setAxisFont(QwtPlot::xBottom, font);
	m_charter2->plot()->setAxisFont(QwtPlot::yLeft, font);
	m_charter3->plot()->setAxisFont(QwtPlot::xBottom, font);
	m_charter3->plot()->setAxisFont(QwtPlot::yLeft, font);

}

void MainWindow::set_plot_title_font(QFont font) {

	QwtText currentTitle1 = m_charter1->plot()->title();
	currentTitle1.setFont(font);
	m_charter1->plot()->setTitle(currentTitle1);

	QwtText currentTitle2 = m_charter2->plot()->title();
	currentTitle2.setFont(font);
	m_charter2->plot()->setTitle(currentTitle2);

	QwtText currentTitle3 = m_charter3->plot()->title();
	currentTitle3.setFont(font);
	m_charter3->plot()->setTitle(currentTitle3);

}

void MainWindow::set_haxis_label_font(QFont font) {

	
	QwtText currentLabelxBottom1 = 
		m_charter1->plot()->axisTitle(QwtPlot::xBottom);
	currentLabelxBottom1.setFont(font);
	m_charter1->plot()->setAxisTitle(QwtPlot::xBottom,
		currentLabelxBottom1);

	QwtText currentLabelxBottom2 = 
		m_charter2->plot()->axisTitle(QwtPlot::xBottom);
	currentLabelxBottom2.setFont(font);
	m_charter2->plot()->setAxisTitle(QwtPlot::xBottom,
		currentLabelxBottom2);

	QwtText currentLabelxBottom3 = 
		m_charter3->plot()->axisTitle(QwtPlot::xBottom);
	currentLabelxBottom3.setFont(font);
	m_charter3->plot()->setAxisTitle(QwtPlot::xBottom,
		currentLabelxBottom3);

}

void MainWindow::set_vaxis_label_font(QFont font) {

	QwtText currentLabelyLeft1 = 
		m_charter1->plot()->axisTitle(QwtPlot::yLeft);
	currentLabelyLeft1.setFont(font);
	m_charter1->plot()->setAxisTitle(QwtPlot::yLeft, currentLabelyLeft1);

	QwtText currentLabelyLeft2 = 
		m_charter2->plot()->axisTitle(QwtPlot::yLeft);
	currentLabelyLeft2.setFont(font);
	m_charter2->plot()->setAxisTitle(QwtPlot::yLeft, currentLabelyLeft2);

	QwtText currentLabelyLeft3 = 
		m_charter3->plot()->axisTitle(QwtPlot::yLeft);
	currentLabelyLeft3.setFont(font);
	m_charter3->plot()->setAxisTitle(QwtPlot::yLeft, currentLabelyLeft3);

}

void MainWindow::set_grid_color(QColor pickedColor) {
	
	m_activeCharter->set_grid_color(pickedColor);

}

void MainWindow::set_grid_style(int styleIndex) {

	m_activeCharter->set_grid_style(styleIndex);

}

void MainWindow::toggle_h_grid(bool checked) {

	m_charter1->plot()->toggle_h_grid(checked);
	m_charter2->plot()->toggle_h_grid(checked);
	m_charter3->plot()->toggle_h_grid(checked);

	m_mainMenuBar->set_h_grid_menu_state(checked);
	m_mainToolBar->set_h_grid_button_state(checked);

}

void MainWindow::toggle_v_grid(bool checked) {

	m_charter1->plot()->toggle_v_grid(checked);
	m_charter2->plot()->toggle_v_grid(checked);
	m_charter3->plot()->toggle_v_grid(checked);

	m_mainMenuBar->set_v_grid_menu_state(checked);
	m_mainToolBar->set_v_grid_button_state(checked);

}

void MainWindow::toggle_hmin_grid(bool checked) {

	m_charter1->plot()->toggle_hmin_grid(checked);
	m_charter2->plot()->toggle_hmin_grid(checked);
	m_charter3->plot()->toggle_hmin_grid(checked);

	m_mainMenuBar->set_hmin_grid_menu_state(checked);
	m_mainToolBar->set_hmin_grid_button_state(checked);

}

void MainWindow::toggle_vmin_grid(bool checked) {

	m_charter1->plot()->toggle_vmin_grid(checked);
	m_charter2->plot()->toggle_vmin_grid(checked);
	m_charter3->plot()->toggle_vmin_grid(checked);

	m_mainMenuBar->set_vmin_grid_menu_state(checked);
	m_mainToolBar->set_vmin_grid_button_state(checked);

}

void MainWindow::make_new_csv_instance_window() {

	NewCSVInstanceWindow* newWindow = new NewCSVInstanceWindow(this);

	connect(newWindow, SIGNAL(instanceReady(ParentInstance*, QString)),
			this, SLOT(make_instance_csv(ParentInstance*, QString)));

	newWindow->exec();

}

void MainWindow::make_instance_csv(ParentInstance* instance, 
	QString fileName) {

	m_instanceTree->append_instance(instance, "CSV", fileName);

}

void MainWindow::make_new_uff58_instance_window() {

	NewUFF58InstanceWindow* newWindow = new NewUFF58InstanceWindow(this);

	connect(newWindow, SIGNAL(instanceReady(ParentInstance*, QString)),
		this, SLOT(make_instance_uff58(ParentInstance*, QString)));

	newWindow->exec();

}

void MainWindow::make_instance_uff58(ParentInstance* instance, 
	QString fileName) {

	m_instanceTree->append_instance(instance, "UFF", fileName);

}

void MainWindow::draw_plot(PlotCurve* curve) {
	
	curve->attach(m_activeCharter);

}

void MainWindow::draw_marker(PlotMarkerInstance* instance) {

	instance->data()->attach(m_activeCharter);

}

void MainWindow::make_new_marker_window() {

	NewMarkerWindow* newMarkerWin = new NewMarkerWindow(this);

	connect(newMarkerWin, SIGNAL(createMarkerRequested(AbstractPlotMarker*)),
			this, SLOT(make_marker_instance(AbstractPlotMarker*)));

	newMarkerWin->exec();

}

void MainWindow::make_marker_instance(AbstractPlotMarker* marker) {

	// below if enables the use of this function even when marker already is
	// attached to a plot. if it is not, it will be attached to the active
	// charter
	if(!marker->plot())
		marker->attach(m_activeCharter);

	PlotMarkerInstance* instance = new PlotMarkerInstance(marker);
	QString charterLabel;

	if(marker->plot() == m_charter1->plot())
		charterLabel = "Charter 1";
	else if(marker->plot() == m_charter2->plot())
		charterLabel = "Charter 2";
	else if(marker->plot() == m_charter3->plot())
		charterLabel = "Charter 3";

	m_markerTree->append_marker(instance, charterLabel);

}

void MainWindow::set_charter_data_picker_search_width(double searchWidth) {

	m_charter1->plot()->set_picker_width(searchWidth);
	m_charter2->plot()->set_picker_width(searchWidth);
	m_charter3->plot()->set_picker_width(searchWidth);

}
