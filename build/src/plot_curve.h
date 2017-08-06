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

#ifndef PLOT_CURVE_H
#define PLOT_CURVE_H

#include <vector>
#include <memory>

#include <QPen>
#include <QString>

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_symbol.h>

#include "stl_typedefs.h"


class PlotCurve: public QwtPlotCurve {

/*
	Class for plot curves in Scope2D. In the constructor, if raw is true,
	then the data passed is not copied but used directly from the memory.
	Even though the data are passed by reference, raw=false will make a deep
	copy and copy the data.
*/

public:
	PlotCurve(const vector_double& x, const vector_double& y,
		QString t = "", bool raw = true);
	PlotCurve(const double* x, const double* y, size_t size,
		QString t = "", bool raw = true);

	void set_data(const vector_double& x, const vector_double& y, 
		bool raw = true);
	void set_data(const double* x, const double* y, size_t size,
		bool raw = true);

	void setPen(QPen pen);
	void setSymbol(QwtSymbol* symbol);

	virtual ~PlotCurve() { this->detach(); }

private:

};

typedef std::unique_ptr<PlotCurve> PlotCurve_uptr;
typedef std::vector<PlotCurve> vector_PlotCurve;
typedef std::vector<PlotCurve*> vector_PlotCurve_ptr;

#endif // !PLOT_CURVE_H
