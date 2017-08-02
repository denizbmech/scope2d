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

#include "add_marker_side_bands_window.h"

AddMarkerSideBandsWindow::AddMarkerSideBandsWindow(QWidget* parent)
	: QDialog(parent) {

	this->setAttribute(Qt::WA_DeleteOnClose);
	this->setWindowTitle("Add marker side bands");

	m_submitButton = new QPushButton(this);
	m_submitButton->setText("Submit");

	m_entryBoxBandGap = new QLineEdit(this);
	m_entryBoxBandGap->setMaxLength(30);
	m_entryBoxBandGap->setPlaceholderText("Enter new value...");

	m_spinBoxBandCount = new QSpinBox(this);
	m_spinBoxBandCount->setValue(1);
	m_spinBoxBandCount->setMinimum(0);
	m_spinBoxBandCount->setMaximum(15);
	m_spinBoxBandCount->setSingleStep(1);

	m_spinBoxBandTicks = new QSpinBox(this);
	m_spinBoxBandTicks->setValue(1);
	m_spinBoxBandTicks->setMinimum(1);
	m_spinBoxBandTicks->setSingleStep(1);

	m_checkBoxIsDynamic = new QCheckBox(this);

	connect(m_checkBoxIsDynamic, SIGNAL(stateChanged(int)), 
		this, SLOT(toggle_dynamic_mode(int)));

	connect(m_submitButton, SIGNAL(clicked(bool)),
		this, SLOT(submit_static_values()));

	connect(m_spinBoxBandCount, SIGNAL(valueChanged(int)), 
		this, SLOT(manage_spin_box_value_changed()));
	connect(m_spinBoxBandTicks, SIGNAL(valueChanged(int)), 
		this, SLOT(manage_spin_box_value_changed()));

	QLabel* l1 = new QLabel("Band count: ", this);
	QLabel* l2 = new QLabel("Dynamic", this);

	m_bandGapLabel = new QLabel("Band gap: ", this);
	m_bandTicksLabel = new QLabel("Band ticks: ", this);

	m_grid = new QGridLayout(this);
	m_grid->setSizeConstraint(QLayout::SetFixedSize);
	m_grid->addWidget(l1, 0, 0);
	m_grid->addWidget(m_spinBoxBandCount, 0, 1);
	m_grid->addWidget(m_bandGapLabel, 1, 0);
	m_grid->addWidget(m_entryBoxBandGap, 1, 1);
	m_grid->addWidget(m_bandTicksLabel, 1, 0);
	m_grid->addWidget(m_spinBoxBandTicks, 1, 1);
	m_grid->addWidget(m_checkBoxIsDynamic, 1, 2);
	m_grid->addWidget(l2, 1, 3);
	m_grid->addWidget(m_submitButton, 2, 4);

	m_checkBoxIsDynamic->setChecked(true);

}

void AddMarkerSideBandsWindow::submit_static_values() {

	if(!m_checkBoxIsDynamic->isChecked()) {
		int bandCount = m_spinBoxBandCount->value();

		QString bandGapStr = m_entryBoxBandGap->text();
		double bandGap = bandGapStr.toDouble();

		emit sideBandsRequested(bandGap, bandCount);
	}

	this->close();

}

void AddMarkerSideBandsWindow::manage_spin_box_value_changed() {

	int bandCount = m_spinBoxBandCount->value();
	int bandTicks = m_spinBoxBandTicks->value();

	if(m_checkBoxIsDynamic->isChecked()) 
		emit sideBandTicksRequested(bandTicks, bandCount);

}

void AddMarkerSideBandsWindow::toggle_dynamic_mode(int dynBoxState) {

	if(dynBoxState == Qt::Checked) {
		m_bandGapLabel->hide();
		m_entryBoxBandGap->hide();
		m_bandTicksLabel->show();
		m_spinBoxBandTicks->show();

		m_spinBoxBandTicks->setValue(1);
	}
	else if(dynBoxState == Qt::Unchecked) {
		m_bandGapLabel->show();
		m_entryBoxBandGap->show();
		m_bandTicksLabel->hide();
		m_spinBoxBandTicks->hide();
	}

}
