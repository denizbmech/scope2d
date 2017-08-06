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

#include "trendline.h"

Trendline::Trendline(ChildInstance* parentData, FIT_TYPE type, 
	vector_double coeffs): m_parent(parentData), m_coeffs(coeffs), m_type(type) {

	this->setEditable(false);

	QString parentDataName = parentData->text();
	QString trendlineName;

	size_t numDataPoints = parentData->plot_curve()->dataSize();

	switch(type) {
		case LINEAR:
			trendlineName = "Linear Fit: " + parentDataName;
			m_make_linear_curve(coeffs[0], coeffs[1], numDataPoints);
			break;
		case EXPONENTIAL:
			trendlineName = "Exponential Fit: " + parentDataName;
			m_make_exponential_curve(coeffs[0], coeffs[1], numDataPoints);
			break;
		case LOGARITHMIC:
			trendlineName = "Logarithmic Fit: " + parentDataName;
			m_make_logarithmic_curve(coeffs[0], coeffs[1], numDataPoints);
			break;
		case POWER:
			trendlineName = "Power Fit: " + parentDataName;
			m_make_power_curve(coeffs[0], coeffs[1], numDataPoints);
			break;
		case POLYNOMIAL:
			trendlineName = "Polynomial Fit: " + parentDataName;
			m_make_polynomial_curve(coeffs, numDataPoints);
			break;
		default:
			break;
	}

	this->setText(trendlineName);

	m_curve = new PlotCurve(m_parent->x_vector()->core.data(), 
		m_fittedYData.data(), numDataPoints, this->text());

	m_parent->appendRow(this);

	m_curve->attach(m_parent->plot_curve()->plot());

}

void Trendline::m_make_linear_curve(double a0, double a1, 
	size_t numDataPoints) {

	m_fittedYData.clear();

	for(size_t i = 0; i < numDataPoints; i++) {
		double fittedData = a0 + a1 * m_parent->x_vector()->core[i];
		m_fittedYData.push_back(fittedData);
	}

	m_calculate_rSquared_linear();

}

void Trendline::m_make_exponential_curve(double a0, double a1,
	size_t numDataPoints) {

	m_fittedYData.clear();

	for(size_t i = 0; i < numDataPoints; i++) {
		double fittedData = a0 * std::exp(a1 * m_parent->x_vector()->core[i]);
		m_fittedYData.push_back(fittedData);
	}

	m_calculate_rSquared_exponential();

}

void Trendline::m_make_logarithmic_curve(double a0, double a1,
	size_t numDataPoints) {

	m_fittedYData.clear();

	for(size_t i = 0; i < numDataPoints; i++) {
		double fittedData = a0 + a1 * std::log(m_parent->x_vector()->core[i]);
		m_fittedYData.push_back(fittedData);
	}

	m_calculate_rSquared_logarithmic();

}

void Trendline::m_make_power_curve(double a0, double a1,
	size_t numDataPoints) {

	m_fittedYData.clear();

	for(size_t i = 0; i < numDataPoints; i++) {
		double fittedData = a0 * std::pow(m_parent->x_vector()->core[i], a1);
		m_fittedYData.push_back(fittedData);
	}

	m_calculate_rSquared_power();

}

void Trendline::m_make_polynomial_curve(vector_double coeffs, 
	size_t numDataPoints) {

	m_fittedYData.clear();

	size_t order = coeffs.size();

	for(size_t i = 0; i < numDataPoints; i++) {
		double fittedData = 0;

		for(size_t j = 0; j < order; j++) {
			fittedData += coeffs[j]*std::pow(m_parent->x_vector()->core[i], j);
		}

		m_fittedYData.push_back(fittedData);
	}

	m_calculate_rSquared_polynomial();

}

double Trendline::m_average(const double* firstElement, 
	const size_t size) const {

	double dataAvg = 0.0;

	for(size_t i = 0; i < size; i++) {
		double delta = *(firstElement + i) - dataAvg;
		dataAvg += delta/(i+1);
	}
	
	return dataAvg;

}

double Trendline::m_calculate_rSquared(const double* regressionData, 
	const double* originalData, const size_t size) const {

	double originalDataAverage = m_average(originalData, size);

	double rSq = 0;

	double SSE = 0; // residual (error) sum of squares
	double SSTO = 0; // total sum of squares

	for(size_t i = 0; i < m_fittedYData.size(); i++) {
		SSE +=
			(*(regressionData + i) - *(originalData + i)) *
			(*(regressionData + i) - *(originalData + i));
		SSTO +=
			(*(originalData + i) - originalDataAverage) *
			(*(originalData + i) - originalDataAverage);
	}

	rSq = 1 - SSE/SSTO;

	return rSq;

}

void Trendline::m_calculate_rSquared_linear() {

	size_t numDataPoints = m_parent->plot_curve()->dataSize();

	double rSq = 
		m_calculate_rSquared(m_fittedYData.data(),
			m_parent->y_vector()->core.data(), numDataPoints);

	m_rSquared = rSq;

}

void Trendline::m_calculate_rSquared_exponential() {

	size_t numDataPoints = m_parent->plot_curve()->dataSize();

	vector_double logOriginalY;
	vector_double logFittedY;

	for(size_t i = 0; i < numDataPoints; i++) {
		double logOrgY = std::log(m_parent->y_vector()->core[i]);
		double logFitY = std::log(m_fittedYData[i]);

		logOriginalY.push_back(logOrgY);
		logFittedY.push_back(logFitY);
	}

	double rSq = 
		m_calculate_rSquared(logFittedY.data(), logOriginalY.data(), 
			numDataPoints);

	m_rSquared = rSq;

}

void Trendline::m_calculate_rSquared_logarithmic() {

	m_calculate_rSquared_linear();

}

void Trendline::m_calculate_rSquared_power() {

	m_calculate_rSquared_exponential();

}

void Trendline::m_calculate_rSquared_polynomial() {

	m_calculate_rSquared_linear();

}

void Trendline::update_title() {

	QString newTitle;
	QString parentDataTitle = m_parent->text();

	switch(m_type) {
		case LINEAR:
			newTitle = "Linear Fit: " + parentDataTitle;
			break;
		case EXPONENTIAL:
			newTitle = "Exponential Fit: " + parentDataTitle;
			break;
		case LOGARITHMIC:
			newTitle = "Logarithmic Fit: " + parentDataTitle;
			break;
		case POWER:
			newTitle = "Power Fit: " + parentDataTitle;
			break;
		case POLYNOMIAL:
			newTitle = "Polynomial Fit: " + parentDataTitle;
			break;
		default:
			break;
	}

	m_curve->setTitle(newTitle);

	this->setText(newTitle);

}

ColVector Trendline::data_column() const {

	vector_double vectorData(m_fittedYData);
	ColVector vect(this->text().toStdString(), vectorData);

	return vect;

}