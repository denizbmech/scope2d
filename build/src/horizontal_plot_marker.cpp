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

#include "horizontal_plot_marker.h"

HorizontalPlotMarker::HorizontalPlotMarker(QwtText markerLabel, QPointF point)
	: AbstractPlotMarker(markerLabel, point, QwtPlotMarker::HLine) {

	this->setLabelAlignment(Qt::AlignRight | Qt::AlignTop);
	this->setLabelOrientation(Qt::Horizontal);

}

void HorizontalPlotMarker::set_color(QColor color) {

	QPen markerPen = this->linePen();
	markerPen.setColor(color);
	this->setLinePen(markerPen);
	this->plot()->replot();

}

void HorizontalPlotMarker::set_label(QwtText label) {

	this->setLabel(label);
	this->plot()->replot();

}

void HorizontalPlotMarker::set_label_font(QFont font) {

	QwtText currentLabel = this->label();
	currentLabel.setFont(font);
	this->setLabel(currentLabel);
	this->plot()->replot();

}

void HorizontalPlotMarker::move(QPointF moveTo) {

	this->setValue(moveTo);
	if(this->plot()) this->plot()->replot();

}