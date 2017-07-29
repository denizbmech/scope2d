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

#ifndef MAIN_TOOLBAR_H
#define MAIN_TOOLBAR_H

#include <QWidget>
#include <QToolBar>
#include <QAction>
#include <QIcon>


class MainToolBar: public QToolBar {

/*
	Main toolbar object that's placed on the main window of the program.
*/

public:
	MainToolBar(QWidget* parent);

	void set_toggle_charter1_button_state(bool state);
	void set_toggle_charter2_button_state(bool state);
	void set_toggle_charter3_button_state(bool state);

	void set_active_charter_button_state_charter1();
	void set_active_charter_button_state_charter2();
	void set_active_charter_button_state_charter3();

	void set_h_grid_button_state(bool state);
	void set_hmin_grid_button_state(bool state);
	void set_v_grid_button_state(bool state);
	void set_vmin_grid_button_state(bool state);

	virtual ~MainToolBar() {}

private:
	Q_OBJECT

	QAction* m_newCSVInstanceRequest;
	QAction* m_newUFF58InstanceRequest;

	QAction* m_toggleCharter1Request;
	QAction* m_toggleCharter2Request;
	QAction* m_toggleCharter3Request;

	QAction* m_setActiveCharter1Request;
	QAction* m_setActiveCharter2Request;
	QAction* m_setActiveCharter3Request;

	QAction* m_savePlots;
	QAction* m_clearActiveCharterRequest;

	QAction* m_toggleHGridRequest;
	QAction* m_toggleVGridRequest;
	QAction* m_toggleHMinGridRequest;
	QAction* m_toggleVMinGridRequest;

	bool m_isCharter1Shown;
	bool m_isCharter2Shown;
	bool m_isCharter3Shown;

	void m_create_csvActions();
	void m_create_uff58Actions();
	void m_create_toggleCharterActions();
	void m_create_activeCharterActions();
	void m_create_savePlotsAction();
	void m_create_clearActiveCharterAction();
	void m_create_toggleGridActions();

public slots:
	void request_new_csv_instance();
	void request_new_uff58_instance();

	void request_toggle_charter1();
	void request_toggle_charter2();
	void request_toggle_charter3();

	void request_setActive_charter1();
	void request_setActive_charter2();
	void request_setActive_charter3();

	void request_save_plots();
	void request_clear_active_charter();

	void request_toggle_h_grid(bool active);
	void request_toggle_hmin_grid(bool active);
	void request_toggle_v_grid(bool active);
	void request_toggle_vmin_grid(bool active);

signals:
	void newCSVInstanceRequested();
	void newUFF58InstanceRequested();

	void toggleCharter1Requested(bool);
	void toggleCharter2Requested(bool);
	void toggleCharter3Requested(bool);

	void setActiveCharter1Requested();
	void setActiveCharter2Requested();
	void setActiveCharter3Requested();

	void savePlotsRequested();
	void clearActiveCharterRequested();

	void toggleHGridRequested(bool);
	void toggleVGridRequested(bool);
	void toggleHMinGridRequested(bool);
	void toggleVMinGridRequested(bool);

};

#endif // !MAIN_TOOLBAR_H
