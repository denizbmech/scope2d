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
	m_entryBoxBandGap = new QLineEdit(this);
	m_entryBoxBandCount = new QLineEdit(this);

	QLabel* l1 = new QLabel("Enter band gap: ", this);
	QLabel* l2 = new QLabel("Enter band count: ", this);

	m_submitButton->setText("Submit");

	m_entryBoxBandGap->setPlaceholderText("Enter new value...");
	m_entryBoxBandGap->setMaxLength(50);
	m_entryBoxBandCount->setPlaceholderText("Enter new value...");
	m_entryBoxBandCount->setMaxLength(50);

	m_grid = new QGridLayout(this);
	m_grid->setSizeConstraint(QLayout::SetFixedSize);
	m_grid->addWidget(l1, 0, 0);
	m_grid->addWidget(m_entryBoxBandGap, 0, 1);
	m_grid->addWidget(l2, 1, 0);
	m_grid->addWidget(m_entryBoxBandCount, 1, 1);
	m_grid->addWidget(m_submitButton, 2, 2);

	connect(m_submitButton, SIGNAL(clicked(bool)), this, SLOT(emit_value()));

}

void AddMarkerSideBandsWindow::emit_value() {

	QString bandGapString = m_entryBoxBandGap->text();
	QString bandCountString = m_entryBoxBandCount->text();

	double bandGap = bandGapString.toDouble();
	int bandCount = bandCountString.toInt();

	emit submitButtonClicked(bandGap, bandCount);

	this->close();
	
}
