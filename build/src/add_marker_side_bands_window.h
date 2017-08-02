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

#ifndef ADD_MARKER_SIDE_BANDS_WINDOW_H
#define ADD_MARKER_SIDE_BANDS_WINDOW_H

#include <QDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QSpinBox>
#include <QCheckBox>
#include <QLineEdit>
#include <QLabel>


class AddMarkerSideBandsWindow: public QDialog {

public:
	AddMarkerSideBandsWindow(QWidget* parent);

	virtual ~AddMarkerSideBandsWindow() { this->clearFocus(); } // just in case?

private:
	Q_OBJECT

	QGridLayout* m_grid;
	QPushButton* m_submitButton;
	QLineEdit* m_entryBoxBandGap;
	QSpinBox* m_spinBoxBandCount;
	QSpinBox* m_spinBoxBandTicks;
	QCheckBox* m_checkBoxIsDynamic;
	QLabel* m_bandGapLabel;
	QLabel* m_bandTicksLabel;

public slots:
	void submit_static_values();
	void manage_spin_box_value_changed();
	void toggle_dynamic_mode(int dynBoxState);

signals:
	void sideBandsRequested(double, int);
	void sideBandTicksRequested(int, int);

};

#endif // !ADD_MARKER_SIDE_BANDS_WINDOW_H
