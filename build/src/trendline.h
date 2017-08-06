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

#ifndef TRENDLINE_H
#define TRENDLINE_H

#include <cmath>

#include <QStandardItem>

#include "child_instance.h"


enum FIT_TYPE {
	LINEAR,
	EXPONENTIAL,
	LOGARITHMIC,
	POWER,
	POLYNOMIAL
};

class Trendline: public QStandardItem {

/*
	Trendline object contains the plot curve and the fitted data for fitted
	curves.
*/

public:
	Trendline(ChildInstance* parentData, FIT_TYPE type, vector_double coeffs);

	int type() const { return m_type; }
	double rSquared() const { return m_rSquared; }
	vector_double coeffs() const { return m_coeffs; }

	ColVector data_column() const;
	PlotCurve* plot_curve() const { return m_curve; }

	void update_title();

	virtual ~Trendline() { delete m_curve; }

private:
	ChildInstance* m_parent;
	PlotCurve* m_curve;
	vector_double m_coeffs;
	vector_double m_fittedYData;
	double m_rSquared;
	int m_type;

	double m_average(const double* firstElement, const size_t size) const;
	void m_make_linear_curve(double a0, double a1, size_t numDataPoints);
	void m_make_exponential_curve(double a0, double a1, size_t numDataPoints);
	void m_make_logarithmic_curve(double a0, double a1, size_t numDataPoints);
	void m_make_power_curve(double a0, double a1, size_t numDataPoints);
	void m_make_polynomial_curve(vector_double coeffs, size_t numDataPoints);
	void m_calculate_rSquared_linear();
	void m_calculate_rSquared_exponential();
	void m_calculate_rSquared_logarithmic();
	void m_calculate_rSquared_power();
	void m_calculate_rSquared_polynomial();
	double m_calculate_rSquared(const double* regressionData, 
		const double* originalData, const size_t size) const;

};

#endif // !TRENDLINE_H
