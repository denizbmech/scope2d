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

#include "main_toolbar.h"

MainToolBar::MainToolBar(QWidget* parent): QToolBar(parent) {

	this->setAttribute(Qt::WA_DeleteOnClose);

	this->setMovable(false);
	this->setFloatable(false);

	m_create_csvActions();
	m_create_uff58Actions();
	this->addSeparator();
	m_create_toggleCharterActions();
	this->addSeparator();
	m_create_activeCharterActions();
	this->addSeparator();
	m_create_toggleGridActions();
	this->addSeparator();
	m_create_savePlotsAction();
	m_create_clearActiveCharterAction();

}

void MainToolBar::set_toggle_charter1_button_state(bool state) {

	QIcon icon;

	if(state)
		icon = QIcon(":/toolbar_charters/c1_shown.png");
	else
		icon = QIcon(":/toolbar_charters/c1_hidden.png");

	m_toggleCharter1Request->setIcon(icon);

	m_isCharter1Shown = state;

}

void MainToolBar::set_toggle_charter2_button_state(bool state) {

	QIcon icon;

	if(state)
		icon = QIcon(":/toolbar_charters/c2_shown.png");
	else
		icon = QIcon(":/toolbar_charters/c2_hidden.png");

	m_toggleCharter2Request->setIcon(icon);

	m_isCharter2Shown = state;

}

void MainToolBar::set_toggle_charter3_button_state(bool state) {

	QIcon icon;

	if(state)
		icon = QIcon(":/toolbar_charters/c3_shown.png");
	else
		icon = QIcon(":/toolbar_charters/c3_hidden.png");

	m_toggleCharter3Request->setIcon(icon);

	m_isCharter3Shown = state;

}

void MainToolBar::set_active_charter_button_state_charter1() {

	m_setActiveCharter1Request->setIcon(
		QIcon(":/toolbar_charters/c1_active.png"));
	m_setActiveCharter2Request->setIcon(
		QIcon(":/toolbar_charters/c2_passive.png"));
	m_setActiveCharter3Request->setIcon(
		QIcon(":/toolbar_charters/c3_passive.png"));

}

void MainToolBar::set_active_charter_button_state_charter2() {

	m_setActiveCharter1Request->setIcon(
		QIcon(":/toolbar_charters/c1_passive.png"));
	m_setActiveCharter2Request->setIcon(
		QIcon(":/toolbar_charters/c2_active.png"));
	m_setActiveCharter3Request->setIcon(
		QIcon(":/toolbar_charters/c3_passive.png"));

}

void MainToolBar::set_active_charter_button_state_charter3() {

	m_setActiveCharter1Request->setIcon(
		QIcon(":/toolbar_charters/c1_passive.png"));
	m_setActiveCharter2Request->setIcon(
		QIcon(":/toolbar_charters/c2_passive.png"));
	m_setActiveCharter3Request->setIcon(
		QIcon(":/toolbar_charters/c3_active.png"));

}

void MainToolBar::m_create_csvActions() {

	m_newCSVInstanceRequest = new QAction(
		QIcon(":/file_formats/csv.png"),
		"New instance from CSV file", this);

	connect(m_newCSVInstanceRequest, SIGNAL(triggered(bool)),
		this, SLOT(request_new_csv_instance()));

	this->addAction(m_newCSVInstanceRequest);

}

void MainToolBar::m_create_uff58Actions() {

	m_newUFF58InstanceRequest = new QAction(
		QIcon(":/file_formats/uff.png"),
		"New instance from UFF58 file", this);

	connect(m_newUFF58InstanceRequest, SIGNAL(triggered(bool)),
		this, SLOT(request_new_uff58_instance()));

	this->addAction(m_newUFF58InstanceRequest);

}

void MainToolBar::m_create_toggleCharterActions() {

	m_toggleCharter1Request = new QAction(
		QIcon(":/toolbar_charters/c1_shown.png"),
		"Show/Hide Charter 1", this);
	m_toggleCharter2Request = new QAction(
		QIcon(":/toolbar_charters/c2_hidden.png"),
		"Show/Hide Charter 2", this);
	m_toggleCharter3Request = new QAction(
		QIcon(":/toolbar_charters/c3_hidden.png"),
		"Show/Hide Charter 3", this);

	connect(m_toggleCharter1Request, SIGNAL(triggered(bool)),
		this, SLOT(request_toggle_charter1()));
	connect(m_toggleCharter2Request, SIGNAL(triggered(bool)),
		this, SLOT(request_toggle_charter2()));
	connect(m_toggleCharter3Request, SIGNAL(triggered(bool)),
		this, SLOT(request_toggle_charter3()));

	m_isCharter1Shown = true;
	m_isCharter2Shown = false;
	m_isCharter3Shown = false;

	this->addAction(m_toggleCharter1Request);
	this->addAction(m_toggleCharter2Request);
	this->addAction(m_toggleCharter3Request);

}

void MainToolBar::m_create_activeCharterActions() {

	m_setActiveCharter1Request = new QAction(
		QIcon(":/toolbar_charters/c1_active.png"),
		"Set Charter 1 as the active charter", this);
	m_setActiveCharter2Request = new QAction(
		QIcon(":/toolbar_charters/c2_passive.png"),
		"Set Charter 2 as the active charter", this);
	m_setActiveCharter3Request = new QAction(
		QIcon(":/toolbar_charters/c3_passive.png"),
		"Set Charter 3 as the active charter", this);

	connect(m_setActiveCharter1Request, SIGNAL(triggered(bool)),
		this, SLOT(request_setActive_charter1()));
	connect(m_setActiveCharter2Request, SIGNAL(triggered(bool)),
		this, SLOT(request_setActive_charter2()));
	connect(m_setActiveCharter3Request, SIGNAL(triggered(bool)),
		this, SLOT(request_setActive_charter3()));

	this->addAction(m_setActiveCharter1Request);
	this->addAction(m_setActiveCharter2Request);
	this->addAction(m_setActiveCharter3Request);

}

void MainToolBar::m_create_savePlotsAction() {

	m_savePlots = new QAction(
		QIcon(":/basicset/1484689456_save_16.png"), "Save plots", 
		this);

	connect(m_savePlots, SIGNAL(triggered(bool)),
		this, SLOT(request_save_plots()));

	this->addAction(m_savePlots);

}

void MainToolBar::m_create_clearActiveCharterAction() {

	m_clearActiveCharterRequest = new QAction(
		QIcon(":/clear_charter/clear.png"), "Clear active charter", 
		this);

	connect(m_clearActiveCharterRequest, SIGNAL(triggered(bool)),
		this, SLOT(request_clear_active_charter()));

	this->addAction(m_clearActiveCharterRequest);

}

void MainToolBar::m_create_toggleGridActions() {

	m_toggleHGridRequest = new QAction(
		QIcon(":/toggle_grid/toggle_h_major.png"), "Toggle H grid",
		this);
	m_toggleVGridRequest = new QAction(
		QIcon(":/toggle_grid/toggle_v_major.png"), "Toggle V grid",
		this);
	m_toggleHMinGridRequest = new QAction(
		QIcon(":/toggle_grid/toggle_h_minor.png"), 
		"Toggle H minor grid",
		this);
	m_toggleVMinGridRequest = new QAction(
		QIcon(":/toggle_grid/toggle_v_minor.png"),
		"Toggle V minor grid",
		this);
	m_toggleHGridRequest->setCheckable(true);
	m_toggleVGridRequest->setCheckable(true);
	m_toggleHMinGridRequest->setCheckable(true);
	m_toggleVMinGridRequest->setCheckable(true);

	connect(m_toggleHGridRequest, SIGNAL(triggered(bool)),
		this, SLOT(request_toggle_h_grid(bool)));
	connect(m_toggleVGridRequest, SIGNAL(triggered(bool)),
		this, SLOT(request_toggle_v_grid(bool)));
	connect(m_toggleHMinGridRequest, SIGNAL(triggered(bool)),
		this, SLOT(request_toggle_hmin_grid(bool)));
	connect(m_toggleVMinGridRequest, SIGNAL(triggered(bool)),
		this, SLOT(request_toggle_vmin_grid(bool)));

	this->addAction(m_toggleHGridRequest);
	this->addAction(m_toggleHMinGridRequest);
	this->addAction(m_toggleVGridRequest);
	this->addAction(m_toggleVMinGridRequest);

}

void MainToolBar::request_new_csv_instance() {

	emit newCSVInstanceRequested();

}

void MainToolBar::request_new_uff58_instance() {

	emit newUFF58InstanceRequested();

}

void MainToolBar::request_toggle_charter1() {
	/*
		Manually toggles the charter's status since toolbar buttons to toggle
		charters are set as uncheckable for better view.

		Button status is updated in set_toggle_charter1_button_state(bool),
		so emit toggleCharter1Requested(bool) emits the updated value.
	*/

	set_toggle_charter1_button_state(!m_isCharter1Shown);

	emit toggleCharter1Requested(m_isCharter1Shown);

}

void MainToolBar::request_toggle_charter2() {
	/*
	Manually toggles the charter's status since toolbar buttons to toggle
	charters are set as uncheckable for better view.

	Button status is updated in set_toggle_charter2_button_state(bool),
	so emit toggleCharter2Requested(bool) emits the updated value.
	*/

	set_toggle_charter2_button_state(!m_isCharter2Shown);

	emit toggleCharter2Requested(m_isCharter2Shown);

}

void MainToolBar::request_toggle_charter3() {
	/*
	Manually toggles the charter's status since toolbar buttons to toggle
	charters are set as uncheckable for better view.

	Button status is updated in set_toggle_charter3_button_state(bool),
	so emit toggleCharter3Requested(bool) emits the updated value.
	*/

	set_toggle_charter3_button_state(!m_isCharter3Shown);

	emit toggleCharter3Requested(m_isCharter3Shown);

}

void MainToolBar::request_setActive_charter1() {

	set_active_charter_button_state_charter1();

	emit setActiveCharter1Requested();

}

void MainToolBar::request_setActive_charter2() {

	set_active_charter_button_state_charter2();

	emit setActiveCharter2Requested();

}

void MainToolBar::request_setActive_charter3() {

	set_active_charter_button_state_charter3();

	emit setActiveCharter3Requested();

}

void MainToolBar::request_save_plots() {

	emit savePlotsRequested();

}

void MainToolBar::request_clear_active_charter() {

	emit clearActiveCharterRequested();

}

void MainToolBar::request_toggle_h_grid(bool active) {

	if(!active) request_toggle_hmin_grid(false);
		
	emit toggleHGridRequested(active);

}

void MainToolBar::request_toggle_hmin_grid(bool active) {

	bool hMinGridStatus = active && m_toggleHGridRequest->isChecked();
	m_toggleHMinGridRequest->setChecked(hMinGridStatus);

	emit toggleHMinGridRequested(hMinGridStatus);

}

void MainToolBar::request_toggle_v_grid(bool active) {

	if(!active) request_toggle_vmin_grid(false);

	emit toggleVGridRequested(active);

}

void MainToolBar::request_toggle_vmin_grid(bool active) {

	bool vMinGridStatus = active && m_toggleVGridRequest->isChecked();
	m_toggleVMinGridRequest->setChecked(vMinGridStatus);

	emit toggleVMinGridRequested(vMinGridStatus);

}

void MainToolBar::set_h_grid_button_state(bool state) {
	/*
		Sets the button state to pressed if state is true; released if state is
		false. Controls the horizontal minor grid button state too, since minor
		grids cannot be used without setting major grids on.
	*/

	m_toggleHGridRequest->setChecked(state);

	if(!state) set_hmin_grid_button_state(false);

}

void MainToolBar::set_hmin_grid_button_state(bool state) {
	/*
		Controls the horizontal minor grid button state. Button is set to
		pressed if state is true, released if state is false.
	*/

	m_toggleHMinGridRequest->setChecked(state);

}

void MainToolBar::set_v_grid_button_state(bool state) {
	/*
	Sets the button state to pressed if state is true; released if state is
	false. Controls the vertical minor grid button state too, since minor
	grids cannot be used without setting major grids on.
	*/

	m_toggleVGridRequest->setChecked(state);

	if(!state) set_vmin_grid_button_state(false);

}

void MainToolBar::set_vmin_grid_button_state(bool state) {
	/*
	Controls the vertical minor grid button state. Button is set to
	pressed if state is true, released if state is false.
	*/

	m_toggleVMinGridRequest->setChecked(state);

}