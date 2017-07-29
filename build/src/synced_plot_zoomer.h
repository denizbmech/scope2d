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

#ifndef SYNCED_PLOT_ZOOMER_H
#define SYNCED_PLOT_ZOOMER_H

#include <QRectF>

#include <qwt_plot.h>
#include <qwt_plot_zoomer.h>


class SyncedPlotZoomer: public QwtPlotZoomer {

/*
	Synchronized plot zoomer. Creates a unit-zoom zoom box and sends it to
	non-synchronized plot zoomers so that they can use the unit-zoom zoom box
	in order to provide zoom with the same ratio as SyncedPlotZoomer, even
	though the scales may be different.

	For example, imagine two plots; one has X limits [0 10] and Y limits [0 15]
	and another one has X Limits [5 25] and Y limits [0 30]. Now imagine the
	synchronized zoomer is used on the first plot to zoom between X: 2 - 5 and
	Y: 5 - 10. This means that the unit-zoom zoom box will be a
	QRect(0.2, 0.5, 0.33, 0.66) because X: 2 - 5 corresponds to 20% and 50% of
	X's current limit (10). Similarly, Y: 5 - 10 corresponds to 33% and 66% of
	Y's current limit (15). Therefore, The non-synchronized plot zoomer objects
	will receive this unit-zoom zoom box and scale it to their own XY limits.
*/

public:
	SyncedPlotZoomer(QwtPlot* plot);
	
	QRectF make_unit_zoom(const QRectF& rect);

private:
	Q_OBJECT

public slots:
	void emit_unit_zoom(const QRectF& rect);

signals:
	void syncZoomed(const QRectF&);

};

#endif // SYNCED_PLOT_ZOOMER_H
