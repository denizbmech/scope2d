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

#include "charter.h"

Charter::Charter(QWidget* parent): QwtPlot(parent) {

	this->setAttribute(Qt::WA_DeleteOnClose);

	set_canvas_color(Qt::white);
	m_init_plot_grid();

	m_nonsyncedZoomer = new NonsyncedPlotZoomer(this);
	m_syncedZoomer = new SyncedPlotZoomer(this);

	m_markerMaker = new CharterMarkerMaker(this);
	m_tooltipMaker = new CharterTooltipMaker(this);

	connect(this, SIGNAL(itemAttached(QwtPlotItem*, bool)),
		this, SLOT(refresh_charter(QwtPlotItem*)));
	connect(m_markerMaker, SIGNAL(verticalMarkerMade(AbstractPlotMarker*)),
		this, SLOT(emit_markerAttached(AbstractPlotMarker*)));
	connect(m_tooltipMaker, SIGNAL(pointMarkerMade(AbstractPlotMarker*)),
		this, SLOT(emit_markerAttached(AbstractPlotMarker*)));
	connect(m_syncedZoomer, SIGNAL(syncZoomed(const QRectF&)),
		this, SLOT(sync_zoom(const QRectF&)));

	this->show();

}

Charter::~Charter() {

	delete m_markerMaker;
	delete m_nonsyncedZoomer;
	delete m_syncedZoomer;

}

void Charter::m_init_plot_grid() {

	QPen pen(Qt::DotLine);
	pen.setColor(Qt::black);

	m_plotGrid = new QwtPlotGrid();
	m_plotGrid->setMajorPen(pen);
	m_plotGrid->setMinorPen(pen);

	m_plotGrid->attach(this);
	m_plotGrid->enableX(false);
	m_plotGrid->enableY(false);
	m_plotGrid->enableXMin(false);
	m_plotGrid->enableYMin(false);

}

void Charter::set_canvas_color(QColor color) {

	QBrush brush(color);
	this->setCanvasBackground(brush);
	this->replot();

}

void Charter::set_grid_color(QColor color) {

	QPen pen = m_plotGrid->majorPen();

	pen.setColor(color);
	m_plotGrid->setMajorPen(pen);
	m_plotGrid->setMinorPen(pen);
	this->replot();

}

void Charter::set_grid_style(int style) {

	QPen pen = m_plotGrid->majorPen();
	
	switch(style) {
		case 0:
			pen.setStyle(Qt::SolidLine);
			break;
		case 1:
			pen.setStyle(Qt::DashLine);
			break;
		case 2:
			pen.setStyle(Qt::DotLine);
			break;
		case 3:
			pen.setStyle(Qt::DashDotLine);
			break;
		case 4:
			pen.setStyle(Qt::DashDotDotLine);
			break;
		default:
			pen.setStyle(Qt::SolidLine);
			break;
	}

	m_plotGrid->setMajorPen(pen);
	m_plotGrid->setMinorPen(pen);
	this->replot();

}

void Charter::rescale_axes() {
	
	if(m_is_any_negative_x())
		this->setAxisScaleEngine(QwtPlot::xBottom, new QwtLinearScaleEngine);
	if(m_is_any_negative_y())
		this->setAxisScaleEngine(QwtPlot::yLeft, new QwtLinearScaleEngine);

	this->setAxisAutoScale(QwtPlot::xBottom);
	this->setAxisAutoScale(QwtPlot::yLeft);

	m_nonsyncedZoomer->setZoomBase();
	m_syncedZoomer->setZoomBase(m_nonsyncedZoomer->zoomBase());

	this->replot();

}

void Charter::toggle_h_grid(bool checked) {
	
	m_plotGrid->enableY(checked);
	this->replot();

}

void Charter::toggle_v_grid(bool checked) {
	
	m_plotGrid->enableX(checked);
	this->replot();

}

void Charter::toggle_hmin_grid(bool checked) {
	
	m_plotGrid->enableYMin(checked);
	this->replot();

}

void Charter::toggle_vmin_grid(bool checked) {
	
	m_plotGrid->enableXMin(checked);
	this->replot();

}

void Charter::set_plot_title(QString value) {

	this->setTitle(value);

}

void Charter::set_haxis_label(QString value) {

	this->setAxisTitle(QwtPlot::xBottom, value);

}

void Charter::set_vaxis_label(QString value) {

	this->setAxisTitle(QwtPlot::yLeft, value);

}

void Charter::use_log_scale() {

	if(!m_is_any_negative_y()) {
		this->setAxisScaleEngine(QwtPlot::xBottom, new QwtLinearScaleEngine);
		this->setAxisScaleEngine(QwtPlot::yLeft, new QwtLogScaleEngine);
		this->rescale_axes();
	}
	
}

void Charter::use_log_log_scale() {

	if(!m_is_any_negative_y() && !m_is_any_negative_x()) {
		this->setAxisScaleEngine(QwtPlot::xBottom, new QwtLogScaleEngine);
		this->setAxisScaleEngine(QwtPlot::yLeft, new QwtLogScaleEngine);
		this->rescale_axes();
	}

}

void Charter::use_linear_scale() {

	this->setAxisScaleEngine(QwtPlot::xBottom, new QwtLinearScaleEngine);
	this->setAxisScaleEngine(QwtPlot::yLeft, new QwtLinearScaleEngine);
	this->rescale_axes();

}

void Charter::use_normalized_scale(QwtPlot::Axis axisId, double reference) {

	NormalizedScaleDraw* normalizedTicks = new NormalizedScaleDraw(reference);
	this->setAxisScaleDraw(axisId, normalizedTicks);
	this->rescale_axes();

}

void Charter::clear() {

	QwtPlotItemList curves = this->itemList(QwtPlotItem::Rtti_PlotCurve);

	for(auto& curve: curves) curve->detach();

}

void Charter::set_picker_width(double width) {

	m_markerMaker->set_search_width(width);
	m_tooltipMaker->set_search_width(width);

}

bool Charter::m_is_any_negative_x() {
	// check all vertical sides of the bounding rectangle and if any of the 
	// sides is less than or equal to zero, return true. 
	// Otherwise, return false.

	QwtPlotItemList itemList = this->itemList(QwtPlotItem::Rtti_PlotCurve);
	for(auto plotItem: itemList) {
		QRectF boundingRectangle = plotItem->boundingRect();
		double bottom = boundingRectangle.bottom();
		double top = boundingRectangle.top();

		if(top <= 0 || bottom <= 0) return true;
	}

	return false;

}

bool Charter::m_is_any_negative_y() {
	// check all horizontal sides of the bounding rectangle and if any of the 
	// sides is less than or equal to zero, return true. 
	// Otherwise, return false.

	QwtPlotItemList itemList = this->itemList(QwtPlotItem::Rtti_PlotCurve);
	for(auto plotItem: itemList) {
		QRectF boundingRectangle = plotItem->boundingRect();
		double bottom = boundingRectangle.bottom();
		double top = boundingRectangle.top();

		if(top <= 0 || bottom <= 0) return true;
	}

	return false;

}

void Charter::refresh_charter(QwtPlotItem* attachedItem) {

	// below if() is to prevent markers from rescaling the axes
	if(attachedItem->rtti() != QwtPlotItem::Rtti_PlotMarker)
		rescale_axes();

	this->replot();

}

void Charter::sync_zoom(const QRectF& rect) {
	
	emit synchronizedZoomUsed(this, rect);

}

void Charter::zoom_to_rect(const QRectF& rect) {

	m_nonsyncedZoomer->set_unit_zoom(rect);
	this->replot();

}

void Charter::emit_markerAttached(AbstractPlotMarker* marker) {

	if(marker) emit markerAttached(marker);

}

double Charter::minimum_haxis_step() const {

	double minimumStep = 0.0;

	QwtPlotItemList itemList = this->itemList(QwtPlotItem::Rtti_PlotCurve);

	for(auto plotItem: itemList) {
		QwtPlotCurve* nextCurve = static_cast<QwtPlotCurve*>(plotItem);

		if(nextCurve->dataSize() > 1) { // make sure there are at least 2 points
			QPointF sample0 = nextCurve->sample(0);
			QPointF sample1 = nextCurve->sample(1);

			double hAxisStep = sample1.x() - sample0.x();

			if(hAxisStep < minimumStep || minimumStep == 0.0) 
				minimumStep = hAxisStep;
		}
	}

	return minimumStep;

}