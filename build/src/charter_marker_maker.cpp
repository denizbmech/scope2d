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

#include "charter_marker_maker.h"

CharterMarkerMaker::CharterMarkerMaker(QwtPlot* plot, double searchWidth)
	: CharterDataPicker(plot, searchWidth) {

	this->setStateMachine(new QwtPickerClickPointMachine);
	this->setMousePattern(QwtEventPattern::MouseSelect1, Qt::LeftButton,
		Qt::ShiftModifier);

	connect(this, SIGNAL(closestXYPicked(QPointF)),
		this, SLOT(make_vertical_marker(QPointF)));

}

void CharterMarkerMaker::make_vertical_marker(QPointF point) {

	QString markerString = "Marker at: " + QString::number(point.x()) + ", " +
		QString::number(point.y());
	QwtText markerLabel(markerString);

	AbstractPlotMarker* marker = new VerticalPlotMarker(markerLabel, point);
	if(this->plot()) marker->attach(this->plot());

	emit verticalMarkerMade(marker);

}
