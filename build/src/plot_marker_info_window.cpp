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

#include "plot_marker_info_window.h"

PlotMarkerInfoWindow::PlotMarkerInfoWindow(QWidget* parent, 
	const AbstractPlotMarker* marker): QDialog(parent) {

	this->setWindowTitle("Marker details");
	this->setAttribute(Qt::WA_DeleteOnClose);

	QLabel* l1 = new QLabel("Marker Label: ", this);
	QLabel* l2 = new QLabel("Marker Type: ", this);
	QLabel* l3 = new QLabel("Fundamental Value X: ", this);
	QLabel* l4 = new QLabel("Fundamental Value Y: ", this);
	QLabel* l5 = new QLabel("Number of Harmonics: ", this);
	QLabel* l6 = new QLabel("Number of Side Bands: ", this);
	QLabel* l7 = new QLabel("Side Band Gap: ", this);

	m_markerLabel = new QLabel(this);
	m_markerType = new QLabel(this);
	m_markerCoordinatesX = new QLabel(this);
	m_markerCoordinatesY = new QLabel(this);
	m_markerNumberOfHarmonics = new QLabel(this);
	m_markerNumberOfSideBands = new QLabel(this);
	m_markerSideBandGap = new QLabel(this);

	m_okayButton = new QPushButton("Okay", this);
	m_okayButton->setMaximumWidth(60);

	connect(m_okayButton, SIGNAL(clicked(bool)), this, SLOT(close()));

	m_gridLayout = new QGridLayout(this);
	m_gridLayout->setSizeConstraint(QLayout::SetFixedSize);
	m_gridLayout->addWidget(l1, 0, 0);
	m_gridLayout->addWidget(m_markerLabel, 0, 1);
	m_gridLayout->addWidget(l2, 1, 0);
	m_gridLayout->addWidget(m_markerType, 1, 1);
	m_gridLayout->addWidget(l3, 2, 0);
	m_gridLayout->addWidget(m_markerCoordinatesX, 2, 1);
	m_gridLayout->addWidget(l4, 3, 0);
	m_gridLayout->addWidget(m_markerCoordinatesY, 3, 1);
	m_gridLayout->addWidget(l5, 4, 0);
	m_gridLayout->addWidget(m_markerNumberOfHarmonics, 4, 1);
	m_gridLayout->addWidget(l6, 5, 0);
	m_gridLayout->addWidget(m_markerNumberOfSideBands, 5, 1);
	m_gridLayout->addWidget(l7, 6, 0);
	m_gridLayout->addWidget(m_markerSideBandGap, 6, 1);
	m_gridLayout->addWidget(m_okayButton, 7, 2, Qt::AlignRight);

	QString markerLabel = marker->label().text();

	QString markerType;
	switch(marker->lineStyle()) {
		case QwtPlotMarker::VLine:
			markerType = "Vertical";
			break;
		case QwtPlotMarker::HLine:
			markerType = "Horizontal";
			break;
		case QwtPlotMarker::Cross:
			markerType = "Cross";
			break;
		case QwtPlotMarker::NoLine:
			markerType = "Point";
			break;
		default:
			markerType = "Unknown";
			break;
	}

	QString markerCoordinatesX = QString::number(marker->value().x(), 'f', 15);
	QString markerCoordinatesY = QString::number(marker->value().y(), 'f', 15);

	// messy... but I couldn't come up with a better solution. only vertical
	// markers have harmonics and side bands
	QString markerNumberOfHarmonics("0");
	QString markerNumberOfSideBands("0");
	QString markerSideBandGap("0.0");
	if(markerType == "Vertical") {
		const VerticalPlotMarker* vMarker = 
			static_cast<const VerticalPlotMarker*>(marker);

		markerNumberOfHarmonics = 
			QString::number(vMarker->number_of_harmonics());
		markerNumberOfSideBands =
			QString::number(vMarker->number_of_side_bands());
		markerSideBandGap =
			QString::number(vMarker->side_band_gap());
	}

	m_markerLabel->setText(markerLabel);
	m_markerType->setText(markerType);
	m_markerCoordinatesX->setText(markerCoordinatesX);
	m_markerCoordinatesY->setText(markerCoordinatesY);
	m_markerNumberOfHarmonics->setText(markerNumberOfHarmonics);
	m_markerNumberOfSideBands->setText(markerNumberOfSideBands);
	m_markerSideBandGap->setText(markerSideBandGap);

}