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

#ifndef CHILD_INSTANCE_H
#define CHILD_INSTANCE_H

#include <vector>

#include <QStandardItem>

#include "plot_curve.h"
#include "col_vector.h"


class ChildInstance;

typedef std::vector<ChildInstance> vector_ChildInstance;
typedef std::vector<ChildInstance*> vector_ChildInstance_ptr;

class ChildInstance: public QStandardItem {

/*
	Level 1 element of the instance tree. Responsible for containing PlotCurve
	objects.

	QwtPlotCurve does not provide a way of retrieving pointers to underlying
	vector objects. So, for later comparisons, I am keeping the pointers m_xData
	and m_yData in the class.
*/

public:
	ChildInstance(PlotCurve* curve, 
		const ColVector* xData, const ColVector* yData)
		: m_curve(curve), m_xVector(xData), m_yVector(yData) {
		if(curve)
			this->setText(curve->title().text());
	}

	PlotCurve* plot_curve() const { return m_curve; }

	const ColVector* x_vector() const { return m_xVector; }
	const ColVector* y_vector() const { return m_yVector; }

	void set_plot_curve(PlotCurve* curve) { m_curve = curve; }

	~ChildInstance() { delete m_curve; }

private:
	PlotCurve* m_curve;
	const ColVector* m_xVector;
	const ColVector* m_yVector;

};

#endif // !CHILD_INSTANCE_H
