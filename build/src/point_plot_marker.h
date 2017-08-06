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

#ifndef POINT_PLOT_MARKER_H
#define POINT_PLOT_MARKER_H

#include <QColor>

#include <qwt_symbol.h>

#include "abstract_plot_marker.h"


class PointPlotMarker: public AbstractPlotMarker {

/*
	Class for point plot marker objects. Ideal for marking a single data point
	on a plot.
*/

public:
	PointPlotMarker(QwtText markerLabel = QString("New Marker"),
		QPointF point = QPointF(0, 0));

	void set_color(QColor color);
	void set_label(QwtText label);
	void set_label_font(QFont font);
	void move(QPointF moveTo);

	virtual ~PointPlotMarker() { this->detach(); }

};

#endif // !POINT_PLOT_MARKER_H
