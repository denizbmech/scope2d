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

#ifndef CHARTER_DATA_PICKER_H
#define CHARTER_DATA_PICKER_H

#include <vector>

#include <QPointF>
#include <QRectF>

#include <qwt_plot.h>
#include <qwt_plot_picker.h>
#include <qwt_plot_item.h>
#include <qwt_series_data.h>
#include <qwt_plot_curve.h>

#include "qt_typedefs.h"
#include "stl_typedefs.h"


class CharterDataPicker: public QwtPlotPicker {

/*
	Plot picker object for charters. Upon mouse click on plot's canvas(),
	selected() is emitted with the coordinates of the point clicked. selected()
	is connected to request_pick_closest_xy(), which finds the closest data 
	point (in pixel coordinates) to the clicked point and emits the coordinates 
	of that data point (in plot coordinates).

	searchWidth determines the number of data points around the point clicked
	which will be tested to search the closest point. searchWidth is in
	percents; namely, it indicates the percentage of the data that will be
	tested around the clicked point. For example, if the data has 1600 points 
	and searchWidth is 1, then 1600 * 1 / 100 = 16 points will be tested; 8 of 
	which is to the rightand the remaining 8 is to the left of the clicked 
	point.
*/

public:
	CharterDataPicker(QwtPlot* plot, double searchWidth = 10);

	double search_width() const { return m_searchWidth; }
	void set_search_width(double searchWidth) { m_searchWidth = searchWidth; }

	virtual ~CharterDataPicker() {}

private:
	Q_OBJECT

	double m_searchWidth;

	vector_QPointF m_canvas_slicer(QPointF pos) const;
	QPointF m_closest_xy(const QPointF& point0, 
		const vector_QPointF& points) const;

public slots :
	void request_pick_closest_xy(const QPointF& pos);

signals:
	void closestXYPicked(QPointF);

};

#endif // !CHARTER_DATA_PICKER_H
