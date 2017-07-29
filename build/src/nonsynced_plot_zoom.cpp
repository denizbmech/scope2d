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

#include "nonsynced_plot_zoomer.h"

NonsyncedPlotZoomer::NonsyncedPlotZoomer(QwtPlot* plot)
	: QwtPlotZoomer(plot->canvas()) {

	this->setMousePattern(QwtEventPattern::MouseSelect1, Qt::LeftButton);

}

void NonsyncedPlotZoomer::set_unit_zoom(const QRectF& rect) {

	QRectF zoomerZoomBase = this->zoomBase();
	double baseBottomLeftX = zoomerZoomBase.x();
	double baseBottomLeftY = zoomerZoomBase.y();
	double baseBoxWidth = zoomerZoomBase.width();
	double baseBoxHeight = zoomerZoomBase.height();

	double bottomLeftX = baseBottomLeftX + rect.x() * baseBoxWidth;
	double bottomLeftY = baseBottomLeftY + rect.y() * baseBoxHeight;
	double boxWidth = rect.width() * baseBoxWidth;
	double boxHeight = rect.height() * baseBoxHeight;

	QRectF newZoom(bottomLeftX, bottomLeftY, boxWidth, boxHeight);
	
	this->zoom(newZoom);

}
