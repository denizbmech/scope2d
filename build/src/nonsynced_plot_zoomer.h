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

#ifndef NONSYNCED_PLOT_ZOOMER_H
#define NONSYNCED_PLOT_ZOOMER_H

#include <QRectF>

#include <qwt_plot.h>
#include <qwt_plot_zoomer.h>


class NonsyncedPlotZoomer: public QwtPlotZoomer {

/*
	Non-synchronized plot zoomer. Receives a unit-zoom zoom box, QRectF rect,
	and transforms it into a zoom box which is scaled with respect to its base 
	zoom box.
*/

public:
	NonsyncedPlotZoomer(QwtPlot* plot);
	void set_unit_zoom(const QRectF& rect);

private:
	Q_OBJECT

};

#endif // !NONSYNCED_PLOT_ZOOMER_H
