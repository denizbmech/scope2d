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

#include "plot_curve.h"

PlotCurve::PlotCurve(const vector_double& x, const vector_double& y,
	QString t, bool raw): QwtPlotCurve(t) {

	this->setRenderHint(QwtPlotItem::RenderAntialiased);
	this->setLegendAttribute(QwtPlotCurve::LegendShowLine);
	this->setLegendAttribute(QwtPlotCurve::LegendShowSymbol);

	set_data(x, y, raw);

	QPen p(QBrush(Qt::blue), 1.3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
	this->setPen(p);
	this->setTitle(QString(t));

	this->setLegendIconSize(QSize(40, 8));

}

PlotCurve::PlotCurve(const double* x, const double* y, 
	size_t size, QString t, bool raw)
	: QwtPlotCurve(t) {

	this->setRenderHint(QwtPlotItem::RenderAntialiased);
	this->setLegendAttribute(QwtPlotCurve::LegendShowLine);
	this->setLegendAttribute(QwtPlotCurve::LegendShowSymbol);

	set_data(x, y, size, raw);

	QPen p(QBrush(Qt::blue), 1.3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
	this->setPen(p);
	this->setTitle(QString(t));

	this->setLegendIconSize(QSize(40, 8));

}

void PlotCurve::set_data(const vector_double& x, const vector_double& y, 
	bool raw) {

	bool xEmpty = x.empty();
	bool yEmpty = y.empty();

	int dataSize;
	if(x.size() <= y.size()) dataSize = x.size();
	else dataSize = y.size();

	if(!xEmpty && !yEmpty) {
		if(raw) this->setRawSamples(x.data(), y.data(), dataSize);
		else this->setSamples(x.data(), y.data(), dataSize);
	}
		
}

void PlotCurve::set_data(const double* x, const double* y, size_t size, 
	bool raw) {

	if(x != nullptr && y != nullptr) {
		if(raw) this->setRawSamples(x, y, size);
		else this->setSamples(x, y, size);
	}

}

void PlotCurve::setPen(QPen pen) {

	QwtPlotCurve::setPen(pen);
	QwtPlot* plot = this->plot();

	if(plot) plot->replot();

}

void PlotCurve::setSymbol(QwtSymbol* symbol) {

	QwtPlotCurve::setSymbol(symbol);
	QwtPlot* plot = this->plot();

	// For some reason, Qwt resets legend icon sizes when the symbol is changed
	// so we're setting it again everytime we change the symbol
	int symbolHeight = this->symbol()->size().height();
	this->setLegendIconSize(QSize(40, symbolHeight));
	
	if(plot) plot->replot();

}