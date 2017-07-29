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

#ifndef ABSTRACT_PLOT_MARKER_H
#define ABSTRACT_PLOT_MARKER_H

#include <QString>
#include <QPointF>
#include <QColor>
#include <QFont>
#include <QPen>

#include <qwt_plot.h>
#include <qwt_plot_marker.h>
#include <qwt_text.h>


class AbstractPlotMarker: public QwtPlotMarker {

/*
	Abstract base class for all plot markers. All plot marker classes must
	inherit from AbstractPlotMarker.
*/

public:
	AbstractPlotMarker(QwtText markerLabel, QPointF point, 
		QwtPlotMarker::LineStyle style);
	AbstractPlotMarker(const AbstractPlotMarker&) = delete;
	AbstractPlotMarker& operator=(const AbstractPlotMarker&) = delete;

	virtual void set_label(QwtText label) = 0;
	virtual void set_label_font(QFont font) = 0;
	virtual void set_color(QColor color) = 0;
	virtual void move(QPointF moveTo) = 0;

	virtual ~AbstractPlotMarker() { this->detach(); }

};

#endif // !ABSTRACT_PLOT_MARKER_H
