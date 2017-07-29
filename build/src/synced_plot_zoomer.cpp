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

#include "synced_plot_zoomer.h"

SyncedPlotZoomer::SyncedPlotZoomer(QwtPlot* plot)
	: QwtPlotZoomer(plot->canvas()) {

	this->setMousePattern(QwtEventPattern::MouseSelect1, Qt::LeftButton,
		Qt::ControlModifier);

	connect(this, SIGNAL(zoomed(const QRectF&)),
		this, SLOT(emit_unit_zoom(const QRectF&)));

}

QRectF SyncedPlotZoomer::make_unit_zoom(const QRectF& rect) {
	
	double zoomBottomLeftX = rect.x();
	double zoomBottomLeftY = rect.y();
	double zoomWidth = rect.width();
	double zoomHeight = rect.height();

	QRectF zoomerZoomBase = this->zoomBase();
	double baseBottomLeftX = zoomerZoomBase.x();
	double baseBottomLeftY = zoomerZoomBase.y();
	double baseBoxWidth = zoomerZoomBase.width();
	double baseBoxHeight = zoomerZoomBase.height();
	
	double unitBottomRightX = (zoomBottomLeftX-baseBottomLeftX)/baseBoxWidth;
	double unitBottomRightY = (zoomBottomLeftY-baseBottomLeftY)/baseBoxHeight;
	double unitWidth = zoomWidth/baseBoxWidth;
	double unitHeight = zoomHeight/baseBoxHeight;

	QRectF unitZoom(unitBottomRightX, unitBottomRightY, unitWidth, 
		unitHeight);

	return unitZoom;

}

void SyncedPlotZoomer::emit_unit_zoom(const QRectF& rect) {
	
	QRectF unitZoom = make_unit_zoom(rect);
	
	emit syncZoomed(unitZoom);

}