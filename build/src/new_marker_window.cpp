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

#include "new_marker_window.h"

NewMarkerWindow::NewMarkerWindow(QWidget* parent): QDialog(parent) {

	this->setAttribute(Qt::WA_DeleteOnClose);
	this->setWindowTitle("Add plot markers");

	QLabel* m_markerNameLabel = new QLabel("Marker Name: ", this);
	QLabel* m_markerXValueLabel = new QLabel("X Value: ", this);
	QLabel* m_markerYValueLabel = new QLabel("Y Value: ", this);
	QLabel* m_markerTypeLabel = new QLabel("Marker Type: ", this);

	m_markerName = new QLineEdit(this);
	m_markerXValue = new QLineEdit(this);
	m_markerYValue = new QLineEdit(this);
	m_markerXValue->setText("0.0");
	m_markerYValue->setText("0.0");

	m_markerType = new QComboBox(this);
	m_markerType->addItems(QStringList() << "Vertical" << "Horizontal" 
		<< "Cross" << "Point");

	m_markerName->setMaxLength(50);
	m_markerXValue->setMaxLength(20);
	m_markerYValue->setMaxLength(20);

	m_createButton = new QPushButton("Create", this);
	m_createButton->setFixedWidth(60);

	m_gridLayout = new QGridLayout(this);
	m_gridLayout->setSizeConstraint(QLayout::SetFixedSize);
	m_gridLayout->addWidget(m_markerNameLabel, 0, 0);
	m_gridLayout->addWidget(m_markerName, 0, 1);
	m_gridLayout->addWidget(m_markerXValueLabel, 1, 0);
	m_gridLayout->addWidget(m_markerXValue, 1, 1);
	m_gridLayout->addWidget(m_markerYValueLabel, 2, 0);
	m_gridLayout->addWidget(m_markerYValue, 2, 1);
	m_gridLayout->addWidget(m_markerTypeLabel, 3, 0);
	m_gridLayout->addWidget(m_markerType, 3, 1);
	m_gridLayout->addWidget(m_createButton, 4, 1, Qt::AlignRight);

	connect(m_createButton, SIGNAL(clicked(bool)),
		this, SLOT(request_create_marker()));

}

void NewMarkerWindow::request_create_marker() {

	QString markerString = m_markerName->text();
	QwtText markerLabel(markerString);

	bool isValueXGood;
	double mAtValueX = m_markerXValue->text().toDouble(&isValueXGood);

	bool isValueYGood;
	double mAtValueY = m_markerYValue->text().toDouble(&isValueYGood);

	if(!isValueXGood || !isValueYGood) {
		QString errMsg = "X and Y can only be decimal.";

		QMessageBox errWin;
		errWin.setWindowTitle("An error occured!");
		errWin.setText("Error occured during marker creation!");
		errWin.setInformativeText(errMsg);
		errWin.setStandardButtons(QMessageBox::Ok);
		errWin.setIcon(QMessageBox::Warning);
		errWin.exec();
	}
	else {
		QPointF markerAt(mAtValueX, mAtValueY);

		AbstractPlotMarker* marker;

		switch(m_markerType->currentIndex()) {
			case 0:
				marker = new VerticalPlotMarker(markerLabel, markerAt);
				break;
			case 1:
				marker = new HorizontalPlotMarker(markerLabel, markerAt);
				break;
			case 2:
				marker = new CrossPlotMarker(markerLabel, markerAt);
				break;
			case 3:
				marker = new PointPlotMarker(markerLabel, markerAt);
				break;
			default:
				marker = new VerticalPlotMarker(markerLabel, markerAt);
				break;
		}

		emit createMarkerRequested(marker);

		this->close();
	}

}