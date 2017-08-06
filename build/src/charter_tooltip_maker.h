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

#ifndef CHARTER_TOOLTIP_MAKER_H
#define CHARTER_TOOLTIP_MAKER_H

#include <QString>
#include <QPointF>

#include <qwt_plot.h>
#include <qwt_picker_machine.h>
#include <qwt_text.h>

#include "charter_data_picker.h"
#include "point_plot_marker.h"


class CharterTooltipMaker: public CharterDataPicker {

/*
	Point marker maker object. When a charter is clicked with ALT + LMB,
	this object will find the data point closes to the clicked coordinates and
	create a PointPlotMarker object at that point and emit the created
	object.
*/

public:
	CharterTooltipMaker(QwtPlot* plot, double searchWidth = 10);
	CharterTooltipMaker(const CharterTooltipMaker&) = delete;
	CharterTooltipMaker& operator=(const CharterTooltipMaker&) = delete;

	virtual ~CharterTooltipMaker() {}

private:
	Q_OBJECT

public slots :
	void make_point_marker(QPointF point);

signals:
	void pointMarkerMade(AbstractPlotMarker*);

};

#endif // !CHARTER_TOOLTIP_MAKER_H
